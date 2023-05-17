#include <cwctype>

// #include <gainput/gainput.h>

#include <neo/ui/input.hpp>

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
    // gainput::InputManager manager;
    // const gainput::DeviceId keyboardId;
    // gainput::InputMap map;

    // input_manager_impl()
    //     : manager()
    //     , keyboardId(manager.CreateDevice<gainput::InputDeviceKeyboard>())
    //     , map(manager)
    // {}
};

input_manager::input_manager()
    : pimpl_(new input_manager_impl)
{

    // input_manager_impl *impl_p = reinterpret_cast<input_manager_impl *>(pimpl_);

    // impl_p->map.MapBool(key::tab, impl_p->keyboardId, gainput::KeyTab);
    // impl_p->map.MapBool(key::shift, impl_p->keyboardId, gainput::KeyShiftL);
    // impl_p->map.MapBool(key::escape, impl_p->keyboardId, gainput::KeyEscape);
}

input
input_manager::get()
{
    input input;

    return input;
}

}   // namespace ui
}   // namespace neo
