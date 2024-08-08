#ifndef NEO_UI_INPUT
#define NEO_UI_INPUT

#include <map>

#include "neo/config.hpp"

namespace neo {
namespace ui {

class NEO_API input
{
   public:
    enum special_key
    {
        tab,
        shift,
        escape,
        enter,
        backspace
    };
    using specials_container_t = std::map<special_key, bool>;

   private:
    static specials_container_t specials_default_;

   private:
    static specials_container_t const &specials_default();

   private:
    specials_container_t specials_;
    wchar_t key_;

   public:
    input();

   public:
    specials_container_t const &specials() const;
    specials_container_t &specials();
    bool special(special_key key) const;
    wchar_t key() const;
    wchar_t &key();
    bool alphanum() const;
    bool printable() const;
};

class NEO_API input_manager
{
   private:
    void *pimpl_;

   public:
    input_manager();

   public:
    input get();
};

}   // namespace ui
}   // namespace neo

#endif
