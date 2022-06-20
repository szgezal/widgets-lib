#include "textreader.hpp"
#include <fstream>
using namespace genv;

Textreader::Textreader(Application* _parent, int _x, int _y, int _sx, int _sy, std::string _filename):
                    Widget(_parent, _x, _y, _sx, _sy), filename(_filename), rows(size_y/(gout.cascent() + gout.cdescent()))
{
    btn1 = new ButtonUp(this, x + size_x - 20, y, 20, 20);
    btn2 = new ButtonDown(this, x + size_x - 20, y + 20, 20, 20);
    read();
}

#include <iostream>
using namespace std;

void Textreader::draw() {
    gout << color(120, 120, 120) << move_to(x, y) << box(size_x, size_y);
    gout << color(255, 255, 255) << move_to(x + 4, y + 4) << box(size_x - 8, size_y - 8);
    for (size_t i = 0; i < s.size() && int(i) < rows; i++) {
        gout << color(0, 0, 0) << move_to(x + 10, y + 10 + (i) * (gout.cascent() + gout.cdescent())) << text(s[i + wheel_offset]);
    }
    btn1->draw();
    btn2->draw();
}

void Textreader::handle(genv::event ev, Widget* w) {
    if (int(s.size()) > rows) {
        if ((ev.button == btn_wheeldown && wheel_offset < int(s.size()) - rows) ||
            (btn2->onWidget(ev) && ev.button > 0 && wheel_offset < int(s.size()) - rows)) {
                wheel_offset++;
        } else if ((ev.button == btn_wheelup && wheel_offset > 0) ||
                   (btn1->onWidget(ev) && ev.button > 0 && wheel_offset > 0)) {
                       wheel_offset--;
        }
    }

    btn1->handle(ev, w);
    btn2->handle(ev, w);
}

void Textreader::read() {
    std::ifstream f(filename);
    std::string _s;
    s.clear();
    while (f.good()) {
        std::getline(f, _s);
        s.push_back(_s);
    }
    f.close();
}
