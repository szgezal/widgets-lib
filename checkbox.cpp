#include "checkbox.hpp"
using namespace genv;

Checkbox::Checkbox(Application* _parent, int _x, int _y, int _sx, int _sy, std::string _type):
                         Widget(_parent,     _x,     _y,     _sx,     _sy),       type(_type)
{

}

void Checkbox::draw() {
    gout << color(0, 0, 0) << move_to(x, y) << box(size_x, size_y);


    if (type == "cb") {
        //default checkbox design
        gout << color(120, 120, 120) << move_to(x, y) << box(size_x, size_y);
        gout << color(0, 0, 0) << move_to(x + size_x/10, y + size_y/10) << box(size_x - 2*size_x/10, size_y - 2*size_y/10);
    } else if (type == "rb") {
        //radio button design
        for (int i = -size_y/2; i < size_y/2; i++)
            for (int j = -size_x/2; j < size_x/2; j++)
                if (i*i + j*j <= (size_x/2)*(size_x/2) && i*i + j*j > (size_x/2 - size_x/8)*(size_x/2 - size_y/8))
                    gout << color(120, 120, 120) << move_to(x + j + size_x/2, y + i + size_y/2) << dot;
        }

    if (checked) {
        if (type == "cb") {
            //default checkbox design
            gout << color(120, 120, 120) << move_to(x + 2*size_x/10, y + 2*size_x/10)
                                         << line_to(x + size_x - 2*size_x/10 - 1, y + size_y - 2*size_x/10 - 1)
                                         << move_to(x + size_x - 2*size_x/10, y + 2*size_x/10)
                                         << line_to(x + 2*size_x/10, y + size_y - 2*size_x/10 - 1);
            gout << color(120, 120, 120) << move_to(x + 2*size_x/10, y + 2*size_x/10 - 1)
                                         << line_to(x + size_x - size_x/4, y + size_y - 2*size_x/10 - 1)
                                         << move_to(x + size_x - 2*size_x/10 - 1, y + 2*size_x/10)
                                         << line_to(x + 2*size_x/10, y + size_y - size_x/4);
            gout << color(120, 120, 120) << move_to(x + 2*size_x/10 - 1, y + 2*size_x/10)
                                         << line_to(x + size_x - size_x/4, y + size_y - 2*size_x/10 - 1)
                                         << move_to(x + size_x - 2*size_x/10, y + 2*size_x/10 - 1)
                                         << line_to(x + 2*size_x/10 - 1, y + size_y - 2*size_x/10 - 1);
        } else if (type == "rb") {
            //radio button design
            for (int i = -size_y/2; i < size_y/2; i++)
                for (int j = -size_x/2; j < size_x/2; j++)
                    if (i*i + j*j <= (size_x/2 - size_x/4)*(size_x/2 - size_y/4))
                        gout << color(120, 120, 120) << move_to(x + j + size_x/2, y + i + size_y/2) << dot;
        }
    }
}

void Checkbox::handle(genv::event ev, Widget * w) {
    if (ev.button == btn_left && w->onWidget(ev))
        checked = !checked;
}
