#ifndef NEO_TERM_CONTEXT
#define NEO_TERM_CONTEXT

#include <memory>

#include "neo/config.hpp"
#include "neo/term/ascii.hpp"
#include "neo/term/buffer.hpp"
#include "neo/ui/context.hpp"

namespace neo {
namespace ui {
namespace term {

class NEO_API context : public ui::context<term::context>
{
   public:
    using buffer_type = buffer;

   private:
    class p_impl;
    std::unique_ptr<p_impl> p_impl_;
    buffer buffer_;

   public:
    context();
    ~context();

   public:
    void print_char(unsigned int x, unsigned int y, term_char_type,
                    std::pair<color, color> const &foreground_background = {color::white, color::black});

    virtual input read() override;
    virtual void refresh() override;

    virtual size_t width() const override;
    virtual size_t height() const override;
};

}   // namespace term
}   // namespace ui
}   // namespace neo

#endif
