#include "neo/term/attributes.hpp"
#include "neo/term/button.hpp"
#include "neo/term/context.hpp"
#include "neo/term/field.hpp"
#include "neo/term/frame.hpp"
#include "neo/term/label.hpp"
#include "neo/term/shape.hpp"
#include "neo/ui/attributes.hpp"

using namespace neo::ui;
int
main()
{
    terminal::context term;

    terminal::frame welcome(term, terminal::attributes(0, 0, term.width() / 2, 15));

    terminal::shape box1(term, terminal::attributes(0, 0, term.width(), term.height()), &welcome);

    terminal::field field(term,
                          terminal::attributes(0, 0, 20, 3, &box1.get_attributes(), anchor::center, anchor::center), 20,
                          false, &welcome);

    terminal::label label(
        term, terminal::attributes(0, 0, 10, 1, &field.get_attributes(), anchor::bottom_center, anchor::top_center),
        u"ça marche !", &welcome);

    term.push_window(welcome);

    term.run();
}
