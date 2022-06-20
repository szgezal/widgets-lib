#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include "widget.hpp"
#include <sstream>

using namespace std;

class Inputbox : public Widget
{
protected:
    string s;
    vector<string> v;
    int curpos = 0;
public:
    Inputbox(Application*, int _x, int _y, int _sx, int _sy, string s, vector<string> v);
    void draw() override;
    void handle(genv::event ev, Widget*) override;
    std::string getText();

};

#endif // INPUTBOX_HPP
