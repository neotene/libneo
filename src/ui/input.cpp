#include <cwctype>

#include <neo/ui/input.hpp>

#include <fcntl.h>
#include <gainput/gainput.h>
#include <iostream>
#include <linux/kd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define ERROR -1
#include <linux/kd.h>
#include <linux/vt.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
namespace neo {
namespace ui {

input::specials_container_t input::specials_default_ = {
    {input::special_key::tab, false}, {input::special_key::shift, false}, {input::special_key::escape, false},
    // {input::special_key::enter, false}
};

input::specials_container_t const &
input::specials_default()
{
    return specials_default_;
}

input::input()
    : specials_(specials_default_)
    , key_(-1)
{}

input::specials_container_t const &
input::specials() const
{
    return specials_;
}

input::specials_container_t &
input::specials()
{
    return specials_;
}

bool
input::special(special_key key) const
{
    return specials().at(key);
}

wchar_t
input::key() const
{
    return key_;
}

wchar_t &
input::key()
{
    return key_;
}

bool
input::alphanum() const
{
    return std::iswalnum(key_);
}

bool
input::printable() const
{
    return std::iswprint(key_);
}

// ------------------------------------------------------------------------------------------------

enum key
{
    tab,
    shift,
    escape
};

struct input_manager_impl {
    gainput::InputManager manager;
    const gainput::DeviceId keyboardId;
    gainput::InputMap map;

    input_manager_impl()
        : manager()
        , keyboardId(manager.CreateDevice<gainput::InputDeviceKeyboard>())
        , map(manager)
    {}
};

input_manager::input_manager()
    : pimpl_(new input_manager_impl)
{

    input_manager_impl *impl_p = reinterpret_cast<input_manager_impl *>(pimpl_);

    impl_p->map.MapBool(key::tab, impl_p->keyboardId, gainput::KeyTab);
    impl_p->map.MapBool(key::shift, impl_p->keyboardId, gainput::KeyShiftL);
    impl_p->map.MapBool(key::escape, impl_p->keyboardId, gainput::KeyEscape);
}

input
input_manager::get()
{
    input input;

    // input_manager_impl *impl_p = reinterpret_cast<input_manager_impl *>(pimpl_);

    // // impl_p->manager.Update();

    // gainput::DeviceButtonSpec btn;
    // // impl_p->manager.GetAnyButtonDown(&btn, 1);
    // gainput::InputDevice *dev = impl_p->manager.GetDevice(impl_p->keyboardId);
    // if (dev->GetAnyButtonDown(&btn, 1) == 0)
    //     return input;

    // std::string str(50, ' ');
    // dev->GetButtonName(btn.buttonId, str.data(), 50);

    // input.specials()[input::special_key::tab] = impl_p->map.GetBoolWasDown(key::tab);
    // input.specials()[input::special_key::shift] = impl_p->map.GetBoolWasDown(key::shift);
    // input.specials()[input::special_key::escape] = impl_p->map.GetBoolWasDown(key::escape);

    // char *tty_name = ::ttyname(STDIN_FILENO);

    // auto fd = ::open(tty_name, O_RDONLY);

    // struct kbkeycode {
    //     unsigned int scancode;
    //     unsigned int keycode;
    // };

    // kbkeycode key;

    // ::ioctl(fd, KDGETKEYCODE, &key);

    // std::cout << key.scancode << " " << key.keycode << "\r";

    int fd;
    int i;

    struct kbkeycode keycode;

    char *tty_name = ::ttyname(STDIN_FILENO);

    if ((fd = open(tty_name, O_NOCTTY)) == ERROR)
    {
        perror("open");
        exit(ERROR);
    }

    printf("w00w00!\n\n");

    keycode.scancode = 1; /* Scancode to convert to keycode. */

    while (1)
    {

        if (keycode.scancode > 255)
        {
            // putchar('\n');
            // close(fd);
            // exit(0);
            keycode.scancode = 1;
            continue;
        }

        if (ioctl(fd, KDGETKEYCODE, &keycode) == ERROR)
        {
            keycode.scancode++;
            continue;
        }

        printf("Keycode: %d (from scan code %d)\n", keycode.keycode, keycode.scancode);

        keycode.scancode++;
    }

    return input;
}

}   // namespace ui
}   // namespace neo
