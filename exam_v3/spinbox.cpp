#include "spinbox.hpp"
#include <sstream>

using namespace genv;


Spinbox::Spinbox(Application* _parent, int _x, int _y, int _sx, int _sy, int _lowerlim, int _upperlim, int _n):
                 Widget(_parent, _x, _y, _sx, _sy), lowerlim(_lowerlim), upperlim(_upperlim), n(_n)
{
    btn1 = new ButtonUp(this, x + size_x - size_y/2, y, size_y/2, size_y/2);
    btn2 = new ButtonDown(this, x + size_x - size_y/2, y + size_y/2, size_y/2, size_y/2);
}

void Spinbox::draw() {
    std::stringstream ss;
    ss << n;
    gout << color(120, 120, 120) << move_to(x, y) << box(size_x - size_y/2, size_y);
    gout << color(255, 255, 255) << move_to(x + 4, y + 4) << box(size_x - size_y/2 - 8, size_y - 8);
    gout << color(0, 0, 0) << move_to(x + size_x/2 - gout.twidth(ss.str())/2 - size_y/4,
                                      y + size_y/2 - gout.cascent() + 2 * gout.cdescent()) << text(ss.str());
    btn1->draw();
    btn2->draw();
}

void Spinbox::handle(genv::event ev, Widget* w) {
    if (n > lowerlim && n < upperlim) {

        if (btn1->onWidget(ev) && ev.button > 0) {
            n++;
        } else if (btn2->onWidget(ev) && ev.button > 0) {
            n--;
        }

        if(w == this && ev.type == ev_key) {

            if (ev.keycode == key_up)
                n++;
            else if (ev.keycode == key_down)
                n--;
            else if (ev.keycode == key_pgup)
                n += 10;
            else if (ev.keycode == key_pgdn)
                n -= 10;
        }

    } else if (n == lowerlim && (ev.keycode == key_up || (btn1->onWidget(ev) && ev.button > 0)))
        n++;
    else if (n == upperlim && (ev.keycode == key_down || (btn2->onWidget(ev) && ev.button > 0)))
        n--;
    else if (n == lowerlim && ev.keycode == key_pgup)
        n += 10;
    else if (n == upperlim && ev.keycode == key_pgdn)
        n -= 10;

    if (n < lowerlim)
        n = lowerlim;
    if (n > upperlim)
        n = upperlim;

    btn1->handle(ev, w);
    btn2->handle(ev, w);
}

int Spinbox::getNum() {
    return n;
}
