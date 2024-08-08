#ifndef NEO_TERM_CONTEXT
#define NEO_TERM_CONTEXT

#include "buffer.hpp"
#include "neo/config.hpp"
#include "neo/ui/context.hpp"
#include "neo/ui/handle.hpp"

namespace neo {
namespace ui {
namespace terminal {

class NEO_API context : public ui::context<buffer>
{
   private:
    handle *handle_;

   public:
    context();
    ~context();

   private:
    handle *init();

   public:
    virtual size_t width() const override;
    virtual size_t height() const override;
    // virtual size_t cursor_x() const override;
    // virtual size_t cursor_y() const override;
    // virtual input read() const override;
    virtual void refresh() override;
};

}   // namespace terminal
}   // namespace ui
}   // namespace neo

#endif
