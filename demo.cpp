#include "neo/term/button.hpp"
#include "neo/term/field.hpp"
#include "neo/term/shape.hpp"
#include "neo/term/types.hpp"
#include "neo/ui/attributes.hpp"
#include <neo/term.hpp>

using namespace neo::ui;

int
main()
{
    terminal::context term;

    terminal::frame welcome(term, terminal::attributes(0, 0, term.width() / 2, 15));

    terminal::shape box1(term, terminal::attributes(0, 0, term.width(), term.height()), &welcome);

    terminal::button btn1(term,
                          terminal::attributes(0, 0, 10, 3, &box1.get_attributes(), anchor::center, anchor::center),
                          L"Button 1", &welcome);

    terminal::shape box2(
        term, terminal::attributes(0, 0, 20, 20, &box1.get_attributes(), anchor::center, anchor::center), &welcome);

    terminal::shape box3(
        term, terminal::attributes(0, 0, 10, 20, &box2.get_attributes(), anchor::center_left, anchor::center_right),
        &welcome);

    terminal::shape box4(
        term, terminal::attributes(0, 0, 10, 20, &box2.get_attributes(), anchor::center_right, anchor::center_left),
        &welcome);

    terminal::shape box5(
        term, terminal::attributes(0, 0, 20, 10, &box2.get_attributes(), anchor::top_center, anchor::bottom_center),
        &welcome);

    terminal::shape box6(
        term, terminal::attributes(0, 0, 20, 10, &box2.get_attributes(), anchor::bottom_center, anchor::top_center),
        &welcome);

    terminal::shape box7(
        term, terminal::attributes(0, 0, 10, 10, &box2.get_attributes(), anchor::top_left, anchor::bottom_right),
        &welcome);

    terminal::shape box8(
        term, terminal::attributes(0, 0, 10, 10, &box2.get_attributes(), anchor::bottom_right, anchor::top_left),
        &welcome);

    terminal::shape box9(
        term, terminal::attributes(0, 0, 10, 10, &box2.get_attributes(), anchor::top_right, anchor::bottom_left),
        &welcome);

    terminal::shape box10(
        term, terminal::attributes(0, 0, 10, 10, &box2.get_attributes(), anchor::bottom_left, anchor::top_right),
        &welcome);

    term.push_window(welcome);

    term.run();
}
