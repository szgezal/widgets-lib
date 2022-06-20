#include "button.hpp"
#include "dropdown.hpp"
#include <sstream>

#include <iostream>
using namespace std;

using namespace genv;

//Button
Button::Button(Application* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

Button::Button(Spinbox* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

Button::Button(Dropdown* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

Button::Button(Textreader* _parent, int _x, int _y, int _sx, int _sy): Widget(_parent, _x, _y, _sx, _sy) {}

void Button::handle(genv::event ev, Widget*) {
    if (this->onWidget(ev) && ev.button > 0)
        this->down = true;
    else if (!this->onWidget(ev) || ev.button == -btn_left)
        this->down = false;
}

//Funktor Button
FunktorButton::FunktorButton(Application* _parent, int _x, int _y, int _sx, int _sy, std::string _txt, std::function<void()> _f):
                                 Button(_parent, _x, _y, _sx, _sy), txt(_txt), f(_f) {}

void FunktorButton::draw() {
    if (down) {
        gout << color(100, 100, 100) << move_to(x, y) << box(size_x, size_y);
        gout << color(0, 0, 0) << move_to(x + size_x/2 - gout.twidth(txt)/2, y + size_y/2 - gout.cascent() + 2*gout.cdescent()) << text(txt);

    } else {
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
        gout << color(0, 0, 0) << move_to(x + size_x/2 - gout.twidth(txt)/2, y + size_y/2 - gout.cascent() + 2*gout.cdescent()) << text(txt);
    }
}

void FunktorButton::handle(genv::event ev, Widget*) {
    this->update(ev);
    if (ev.type == ev_mouse && ev.button > 0)
        f();
}


bool FunktorButton::onWidget(genv::event ev) {
    return ev.pos_x > x && ev.pos_y > y &&
           ev.pos_x < x + size_x && ev.pos_y < y + size_y;
}

void FunktorButton::update(genv::event ev) {
    if (this->onWidget(ev) && ev.button > 0)
        this->down = true;
    else if (!this->onWidget(ev) || ev.button == -btn_left)
        this->down = false;
}

//ButtonUp
ButtonUp::ButtonUp(Spinbox* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

ButtonUp::ButtonUp(Textreader* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

void ButtonUp::draw() {
    if (down) {
        gout << color(100, 100, 100) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + 12 - i) << line(10 - 2*i, 0);
    } else {
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + 12 - i) << line(10 - 2*i, 0);
    }
}


//ButtonDown
ButtonDown::ButtonDown(Spinbox* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

ButtonDown::ButtonDown(Textreader* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

ButtonDown::ButtonDown(Dropdown* _parent, int _x, int _y, int _sx, int _sy): Button(_parent, _x, _y, _sx, _sy) {}

void ButtonDown::draw() {
    if (down) {
        gout << color(100, 100, 100) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + size_y/2 - 2 + i) << line(10 - 2*i, 0);
    } else {
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
        for (int i = 0; i < 5; i++)
            gout << color(50, 50, 50) << move_to(x + 5 + i, y + size_y/2 - 2 + i) << line(10 - 2*i, 0);
    }
}
