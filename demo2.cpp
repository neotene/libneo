#include "neo/term/attributes.hpp"
#include "neo/term/button.hpp"
#include "neo/term/context.hpp"
#include "neo/term/field.hpp"
#include "neo/term/frame.hpp"
#include "neo/term/shape.hpp"

using namespace neo::ui;
int
main()
{
    terminal::context term;

    terminal::frame welcome(term, terminal::attributes(0, 0, term.width() / 2, 15));

    terminal::shape box1(term, terminal::attributes(0, 0, term.width(), term.height()), &welcome);

    terminal::field field(term, terminal::attributes(10, 10, 20, 3), 10, false, &welcome);

    term.push_window(welcome);

    term.run();
}
