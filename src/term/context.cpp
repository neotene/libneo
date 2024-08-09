#include <curses.h>

#include "neo/term/context.hpp"
#include "neo/ui/color.hpp"

#ifdef NEO_SYSTEM_WINDOWS
# include <windows.h>
#else
# include <gainput/gainput.h>

#endif   // NEO_SYSTEM_WINDOWS

#include <panel.h>

#include <stdexcept>

#include "neo/term/buffer.hpp"
#include "neo/ui/input.hpp"

namespace neo {
namespace ui {
namespace term {

std::map<color, int> const colors = {
    {color::white, COLOR_WHITE}, {color::black, COLOR_BLACK}, {color::red, COLOR_RED},
    {color::green, COLOR_GREEN}, {color::blue, COLOR_BLUE},
};

class context::p_impl
{
    WINDOW *win_hdl_;

    WINDOW *init_win_hdl()
    {
        WINDOW *win_hdl = ::initscr();

        if (!win_hdl)
            throw std::runtime_error("PDCurses init: could not initialize screen");
        if (::noecho() != OK)
            throw std::runtime_error("PDCurses init: could not initialize noecho");
        if (::start_color() != OK)
            throw std::runtime_error("PDCurses init: could not initialize start_color");

        return win_hdl;
    }

   public:
    WINDOW *win_hdl() const
    {
        return win_hdl_;
    }

#ifdef NEO_SYSTEM_WINDOWS
   private:
    HANDLE std_handle_;

   public:
    HANDLE std_handle()
    {
        return std_handle_;
    }

    p_impl()
    {
        win_hdl_ = init_win_hdl();
        std_handle_ = GetStdHandle(STD_INPUT_HANDLE);
        if (std_handle_ == nullptr)
            throw std::runtime_error("GetStdHandle returned NULL");
    }

#else
   private:
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

    p_impl()
        : input_map_(input_manager_)
    {
        win_hdl_ = init_win_hdl();

        const gainput::DeviceId keyboardId = input_manager_.CreateDevice<gainput::InputDeviceKeyboard>();

        input_map_.MapBool(input::special_key::backspace, keyboardId, gainput::KeyBackSpace);
        input_map_.MapBool(input::special_key::enter, keyboardId, gainput::KeyKpEnter);
        input_map_.MapBool(input::special_key::escape, keyboardId, gainput::KeyEscape);
        input_map_.MapBool(input::special_key::shift, keyboardId, gainput::KeyShiftL);
        input_map_.MapBool(input::special_key::tab, keyboardId, gainput::KeyTab);
    }
#endif
};

context::context()
    : p_impl_(std::make_unique<p_impl>())
{
    buffer_.resize(width(), height());

#ifdef NEO_SYSTEM_LINUX
    p_impl_.get()->input_manager().SetDisplaySize(width(), height());
#endif
}

context::~context() = default;

size_t
context::width() const
{
    [[maybe_unused]] int h;
    int w;
    getmaxyx(p_impl_.get()->win_hdl(), h, w);
    return w;
}

size_t
context::height() const
{
    int h;
    [[maybe_unused]] int w;
    getmaxyx(p_impl_.get()->win_hdl(), h, w);
    return h;
}

#ifdef NEO_SYSTEM_WINDOWS
input
context::read()
{
    DWORD cc;
    INPUT_RECORD irec;

    KEY_EVENT_RECORD key;

    ReadConsoleInput(p_impl_->std_handle(), &irec, 1, &cc);

    input input;

    if (irec.EventType == KEY_EVENT && ((KEY_EVENT_RECORD &) irec.Event).bKeyDown)
    {
        key = (KEY_EVENT_RECORD &) irec.Event;

        input.key() = key.uChar.UnicodeChar;
        input.specials()[input::special_key::shift] = (key.dwControlKeyState & SHIFT_PRESSED) == SHIFT_PRESSED;
        input.specials()[input::special_key::tab] = input.key() == 9;
        input.specials()[input::special_key::escape] = input.key() == 27;
        input.specials()[input::special_key::enter] = input.key() == 13;
        input.specials()[input::special_key::backspace] = input.key() == 8;
    }

    return input;
}
#else
input
context::read()
{
    p_impl_.get()->input_manager().Update();

    input input;

    input.specials()[input::special_key::shift] = p_impl_.get()->input_map().GetBoolWasDown(input::special_key::shift);
    input.specials()[input::special_key::tab] = p_impl_.get()->input_map().GetBoolWasDown(input::special_key::tab);
    input.specials()[input::special_key::escape] =
        p_impl_.get()->input_map().GetBoolWasDown(input::special_key::escape);
    input.specials()[input::special_key::enter] = p_impl_.get()->input_map().GetBoolWasDown(input::special_key::enter);
    input.specials()[input::special_key::backspace] =
        p_impl_.get()->input_map().GetBoolWasDown(input::special_key::backspace);

    return input;
}
#endif

void
context::refresh()
{
    buffer_.fill(buffer_type::cell_type(' '));

    for (auto &layer : stack_)
    {
        for (auto &obj : layer)
            obj->draw(buffer_);
    }

    buffer_type::size_type y = 0;
    buffer_.for_each([&y, this](buffer::line_type const &line) {
        int x = 0;
        for (buffer::cell_type const &character : line)
            print_ch16(x++, y, character.ch, {color::red, color::white});
        y++;
    });
    ::wrefresh(p_impl_->win_hdl());
}

void
context::print_ch16(unsigned int x, unsigned int y, char16_t ch, std::pair<color, color> const &foreground_background)
{
    ::init_pair(1, colors.at(foreground_background.first), colors.at(foreground_background.second));
    ::attron(COLOR_PAIR(1));
    ::wmove(p_impl_->win_hdl(), y, x);
    ::waddch(p_impl_->win_hdl(), ch);
    ::attroff(COLOR_PAIR(1));
}

}   // namespace term
}   // namespace ui
}   // namespace neo
