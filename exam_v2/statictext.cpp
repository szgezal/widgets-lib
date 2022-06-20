#include "statictext.hpp"

using namespace genv;

StaticText::StaticText(Application* _parent, int _x, int _y, int _sx, int _sy, std::string _txt, int _r, int _g, int _b, int _size):
                        Widget(_parent, _x, _y, _sx, _sy), txt(_txt), r(_r), g(_g), b(_b), size(_size)
{

}

void StaticText::draw() {
    gout.load_font("LiberationSans-Regular.ttf", size);
    //if (txt != "") if the text size is not 16 uncomment and insert text between ""
        gout << color(255-r, 255-g, 255-b) << move_to(x, y) << box(size_x, size_y);
    gout << color(r, g, b) << move_to(x + size_x/2 - gout.twidth(txt)/2, y + size_y/2 - gout.cascent() + 2*gout.cdescent()) << text(txt);
    gout.load_font("LiberationSans-Regular.ttf", 16);
}

void StaticText::handle(genv::event, Widget*) {}

void StaticText::changePlayer(std::string _txt) {
    txt = _txt;
    int tmp = r;
    r = b;
    b = tmp;
}

std::string StaticText::getText() {
    return txt;
}

void StaticText::setText(std:: string _txt, int _r, int _g, int _b) {
    txt = _txt;
    r = _r;
    g = _g;
    b = _b;
}
