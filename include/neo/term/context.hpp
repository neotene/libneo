#ifndef NEO_TERM_CONTEXT
#define NEO_TERM_CONTEXT

#include <experimental/propagate_const>
#include <memory>

#include "neo/config.hpp"
#include "neo/term/buffer.hpp"
#include "neo/ui/context.hpp"

namespace neo {
namespace ui {
namespace terminal {

class NEO_API context : public ui::context<buffer>
{
    class p_impl;
    std::experimental::propagate_const<std::unique_ptr<p_impl>> p_impl_;

   public:
    context();

   public:
    virtual size_t width() const override;
    virtual size_t height() const override;
    virtual input read() const override;
    virtual void refresh() override;
};

}   // namespace terminal
}   // namespace ui
}   // namespace neo

#endif
