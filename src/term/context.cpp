#include <curses.h>

#include "neo/config.hpp"

#ifdef NEO_SYSTEM_WINDOWS
# include <windows.h>
#endif   // NEO_SYSTEM_WINDOWS

#include <panel.h>

// #include <gainput/gainput.h>

#include <stdexcept>

#include "neo/term/buffer.hpp"
#include "neo/term/context.hpp"
#include "neo/ui/handle.hpp"
#include "neo/ui/input.hpp"
#include "neo/ui/print.hpp"

namespace neo {
namespace ui {
namespace terminal {

handle *
context::init()
{
    WINDOW *hdl = ::initscr();

    if (!hdl)
        throw std::runtime_error("PDCurses init: could not initialize screen");
    if (::noecho() != OK)
        throw std::runtime_error("PDCurses init: could not initialize noecho");
    if (::start_color() != OK)
        throw std::runtime_error("PDCurses init: could not initialize start_color");

    return reinterpret_cast<ui::handle *>(hdl);
}

context::context() : handle_(init())
{
    buffer_.resize(width(), height());
}

context::~context()
{
    if (!handle_)
        return;
    // ::endwin();
    handle_ = nullptr;
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
context::read() const
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
context::read() const
{
    // gainput::DeviceButtonSpec outButtons;
    // manager.GetAnyButtonDown(&outButtons, 1);

    // auto ch = std::wcin.get();
    // // int ch = ::wgetch(reinterpret_cast<WINDOW *>(handle_));
    // auto s = keyname(ch);
    // input.key() = ch;
    // input.specials()[input::special_key::shift_tab] = s == std::string("^[");
    // input.specials()[input::special_key::tab] = input.key() == 9;
    // input.specials()[input::special_key::escape] = input.key() == 27;
    // input.specials()[input::special_key::enter] = input.key() == 13;
    // input.specials()[input::special_key::backspace] = input.key() == 127;

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
