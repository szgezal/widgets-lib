#include "dropdown.hpp"
#include <sstream>
#include <math.h>

using namespace genv;


Dropdown::Dropdown(Application* _parent, int _x, int _y, int _sx, int _sy,
                         std::vector<std::string> _elements,
                         int _e):
                         Widget(_parent, _x, _y, _sx, _sy),
                         elements(_elements),
                         e(_e),
                         selected(""),
                         original_size_y(_sy)
{
    while (this->e > int(elements.size()))
        elements.push_back("");
    btn = new ButtonDown(this, x + size_x - size_y/2, y, size_y/2, size_y);

}

void Dropdown::draw() {

    if (!this->open) {
        gout << color(0, 0, 0) << move_to(x, y) << box(size_x, this->size_y * (this->e + 1));
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x, size_y);
        gout << color(200, 200, 200) << move_to(x + 4, y + 4) << box(size_x - 8, size_y - 8);
        gout << color(0, 0, 0) << move_to(x + size_x/2 - original_size_y/4 - gout.twidth(selected)/2,
                                          y + size_y/2 - gout.cascent() + 2 * gout.cdescent()) << text(selected);
    } else {
        gout << color(150, 150, 150) << move_to(x, y) << box(size_x - original_size_y/2, size_y);
        gout << color(200, 200, 200) << move_to(x + 4, y + 4) << box(size_x - original_size_y/2 - 8, size_y - 8);
        gout << color(0, 0, 0) << move_to(x + size_x/2 - original_size_y/4 - gout.twidth(selected)/2,
                                          y + original_size_y/2 - gout.cascent() + 2 * gout.cdescent())
                               << text(selected);

        for (int i = wheel_offset; i < this->e + wheel_offset; i++) {
            gout << color(150, 150, 150) << move_to(x, y + (i - wheel_offset) * original_size_y + original_size_y - 2)
                 << box(size_x - original_size_y/2, 4);
            gout << color(0, 0, 0) << move_to(x + size_x/2 - original_size_y/4 - gout.twidth(elements[(i)])/2,
              (y + 3*original_size_y/2 - gout.cascent() + 2 * gout.cdescent()) + (i - wheel_offset) * original_size_y)
                 << text(elements[(i)]);
        }
    }

    btn->draw();
}


void Dropdown::handle(genv::event ev, Widget* w) {

    if (!this->open && ev.button > 0 && btn->onWidget(ev))
        this->size_y = this->size_y * (this->e + 1);
    else if (this->open && ev.button > 0 && btn->onWidget(ev))
        this->size_y = this->size_y / (this->e + 1);

    if (btn->onWidget(ev) && ev.button > 0) {
        this->open = !this->open;
    }

    btn->handle(ev, w);

    if (ev.button == btn_wheeldown && wheel_offset < int(elements.size()) - e) {
            wheel_offset++;
    } else if (ev.button == btn_wheelup && wheel_offset > 0) {
            wheel_offset--;
    }

    if (ev.button == btn_left && w->onWidget(ev) && floor((ev.pos_y - y) / double(original_size_y)) != 0) {
        index_of_selected = floor((ev.pos_y - y) / double(original_size_y)) - 1 + wheel_offset;
        selected = elements[index_of_selected];
        open = false;
        size_y = original_size_y;
    }
}

std::string Dropdown::getSelected() {
    return selected;
}

void Dropdown::addElement(std::string s) {
    for (std::string & el: elements)
        if (el == "") {
            el = s;
            return;
        }

    elements.push_back(s);

}

void Dropdown::removeElement() {
    if (elements[index_of_selected] == selected && elements[index_of_selected] != "" && selected != "") {

        elements.erase(elements.begin() + index_of_selected);

        if (wheel_offset > 0)
            wheel_offset--;

        if (index_of_selected < e && int(elements.size()) < e)
            elements.push_back("");
    }
}

void Dropdown::setSelected() {
    if (index_of_selected < int(elements.size()) && elements[index_of_selected] != "")
        selected = elements[index_of_selected];
    else if (index_of_selected > 0) {
        selected = elements[index_of_selected - 1];
        index_of_selected--;
    } else
        selected = "";
}

bool Dropdown::getState() {
    return open;
}
