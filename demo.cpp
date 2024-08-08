#include "neo/term/attributes.hpp"
#include "neo/term/context.hpp"
#include "neo/term/field.hpp"
#include "neo/term/label.hpp"
#include "neo/term/shape.hpp"
#include "neo/ui/attributes.hpp"

using namespace neo::ui;
int
main()
{
    term::context term;

    term::shape box(term, term::attributes(0, 0, term.width(), term.height()));

    term::field field(term, term::attributes(0, 0, 20, 3, &box.get_attributes(), anchor::center, anchor::center), 20,
                      false);

    term::label label(term,
                      term::attributes(0, 0, 10, 1, &field.get_attributes(), anchor::bottom_center, anchor::top_center),
                      u"ça marche !");

    term.run();
}