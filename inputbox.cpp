#include "inputbox.hpp"
#include <iostream>
#include <algorithm>

using namespace genv;
using namespace std;

Inputbox::Inputbox(Application* _parent, int _x, int _y, int _sx, int _sy, string _s, vector<string> _v):
    Widget(_parent, _x, _y, _sx, _sy), s(_s), v(_v)
{

}

void Inputbox::draw() {
    gout << move_to(x, y) << color(100,100,100) << box(size_x + 4, size_y);
    gout << move_to(x+2, y+2) << color(255,255,255) << box(size_x, size_y-4);
    gout << color(0, 0, 0) << move_to(x+4, y + size_y/2 - (gout.cascent()+gout.cdescent())/2 - gout.cdescent()/2) << text(s);
}

void Inputbox::handle(genv::event ev, Widget*) {

    if (ev.type == ev_key && ev.keycode > 0) {

        if (ev.keycode == key_lshift || ev.keycode == key_capsl)
            ev.keycode = 0;

        // kurzor balra
        else if (ev.keycode == key_left && curpos > 0) {

            string cur = s.substr(curpos, 1);
            s = s.substr(0, curpos) + s.substr(curpos + 1, s.length() - curpos - 1);
            s = s.substr(0, curpos - 1) + cur + s.substr(curpos - 1, 1) + s.substr(curpos, s.length() - curpos);

            curpos--;

        // kurzor jobbra
        } else if (ev.keycode == key_right && curpos < int(s.length() + v.size() - 1) && curpos < int(s.length()) - 1) {

            string cur = s.substr(curpos, 1);
            s = s.substr(0, curpos) + s.substr(curpos + 1, s.length() - curpos - 1);
            s = s.substr(0, curpos) + s.substr(curpos, 1) + cur + s.substr(curpos + 1, s.length() - curpos - 1);

            curpos++;

        // torles
        } else if (ev.keycode == key_backspace && ev.keycode != key_left) {
            // ha nem latszik minden beirt karakter
            if (v.size() > 0) {

                s = v[v.size() - 1] + s.substr(0, curpos - 1) + s.substr(curpos, s.length() - curpos);
                v.pop_back();

            // ha latszik minden karakter (a vektorban nincs elem) és nem az elejerol torlok
            } else
                if (curpos > 0) {

                    s = s.substr(0, curpos - 1) + s.substr(curpos, s.length() - curpos);

                    curpos--;
                }

        // gepeles
        } else if (ev.keycode != key_right && ev.keycode != key_left){

            // kilogna e a szoveg a dobozbol? ---> vektorba
            if (gout.twidth(s) + gout.twidth(ev.keyutf8) + gout.twidth("|") > size_x) {
                v.push_back(s.substr(0, 1));

            // ha tobb szoveg van, mint hely ---> elcsusztatva beszur
                if (v.size() > 0)
                    s = s.substr(1, curpos - 1) + ev.keyutf8 + s.substr(curpos, s.length() - curpos);

            // itt csak siman beszur
            } else {
                s = s.substr(0, curpos) + ev.keyutf8 + s.substr(curpos, s.length() - curpos + 2);
                if (v.size() > 0)
                    curpos++;
            }

            if (v.size() == 0)
                curpos++;
        }
    }

}

std::string Inputbox::getText() {
    std::string tmp = s;
    tmp.erase(tmp.begin() + curpos);
    return tmp;
}
