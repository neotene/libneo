#include "neo/term/context.hpp"

#include <curses.h>

#ifdef NEO_SYSTEM_WINDOWS
# include <windows.h>
#else
# include <gainput/GainputInputDeviceKeyboard.h>
# include <gainput/GainputInputMap.h>
# include <gainput/GainputInputMap.h>
# include <gainput/gainput.h>

#endif   // NEO_SYSTEM_WINDOWS

#include <panel.h>

#include <stdexcept>

#include "neo/term/buffer.hpp"
#include "neo/ui/input.hpp"
#include "neo/ui/print.hpp"

namespace neo {
namespace ui {
namespace terminal {

class context::p_impl
{
    WINDOW *win_hdl_;

    WINDOW *init_win_hdl()
    {
        WINDOW *win_hdl = ::initscr();

        if (!win_hdl_)
            throw std::runtime_error("PDCurses init: could not initialize screen");
        if (::noecho() != OK)
            throw std::runtime_error("PDCurses init: could not initialize noecho");
        if (::start_color() != OK)
            throw std::runtime_error("PDCurses init: could not initialize start_color");

        return win_hdl;
    }
#ifdef NEO_SYSTEM_WINDOWS
    HANDLE std_handle_;
#else
    gainput::InputManager input_manager_;
    gainput::InputMap input_map_;

   public:
    gainput::InputManager &input_manager()
    {
        return input_manager_;
    }

    gainput::InputMap &input_map()
    {
        return input_map_;
    }

    p_impl(WINDOW *win_hdl) : win_hdl_(win_hdl), input_map_(input_manager_)
    {
        win_hdl_ = init_win_hdl();

        const gainput::DeviceId keyboardId = input_manager_.CreateDevice<gainput::InputDeviceKeyboard>();

        input_map_.MapBool(input::special_key::backspace, keyboardId, gainput::KeyBackSpace);
        input_map_.MapBool(input::special_key::enter, keyboardId, gainput::KeyKpEnter);
    }
#endif
};

context::context() : p_impl_(std::make_unique<p_impl>())
{
    buffer_.resize(width(), height());

#ifdef NEO_SYSTEM_LINUX
    p_impl_.get()->input_manager().SetDisplaySize(width(), height());
#endif
}

size_t
context::width() const
{
    [[maybe_unused]] int h;
    int w;
    getmaxyx(reinterpret_cast<WINDOW *>(handle_), h, w);
    return w;
}

size_t
context::height() const
{
    int h;
    [[maybe_unused]] int w;
    getmaxyx(reinterpret_cast<WINDOW *>(handle_), h, w);
    return h;
}

#ifdef NEO_SYSTEM_WINDOWS
void
getconchar(KEY_EVENT_RECORD &krec)
{
    DWORD cc;
    INPUT_RECORD irec;
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

    if (h == NULL)
        throw std::runtime_error("GetStdHandle returned NULL");

    for (;;)
    {
        ReadConsoleInput(h, &irec, 1, &cc);
        if (irec.EventType == KEY_EVENT && ((KEY_EVENT_RECORD &) irec.Event).bKeyDown)
        {
            krec = (KEY_EVENT_RECORD &) irec.Event;
            return;
        }
    }
}
#endif

#ifdef NEO_SYSTEM_WINDOWS
input
context::read()
{
    KEY_EVENT_RECORD key;
    getconchar(key);
    input input;
    input.key() = key.uChar.UnicodeChar;
    input.specials()[input::special_key::shift] = (key.dwControlKeyState & SHIFT_PRESSED) == SHIFT_PRESSED;
    input.specials()[input::special_key::tab] = input.key() == 9;
    input.specials()[input::special_key::escape] = input.key() == 27;
    input.specials()[input::special_key::enter] = input.key() == 13;
    input.specials()[input::special_key::backspace] = input.key() == 8;
    return input;
}
#else
input
context::read()
{
    p_impl_.get()->input_manager().Update();

    // May need some platform-specific message handling here

    if (p_impl_.map().GetBoolWasDown(ButtonConfirm))
    {
        // Confirmed!
    }

    input input;
    return input;
}
#endif

void
context::refresh()
{
    buffer_.fill(buffer_type::character_type(' '));

    for (auto &obj : objects_)
    {
        obj->draw();
    }

    buffer_type::size_type y = 0;
    buffer_.for_each([&y](buffer::line_type const &line) {
        int x = 0;
        for (buffer::character_type const &character : line)
            neo::print(x++, y, std::wstring(1, character.ch), {character.ch_color, character.bg_color});
        y++;
    });
    ::refresh();
}

}   // namespace terminal
}   // namespace ui
}   // namespace neo
