#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include "widget.hpp"
#include <sstream>

using namespace std;

class Inputbox : public Widget
{
protected:    
    string cur;
    string s;
    vector<string> v;
    int curpos = s.length() - 1;
public:
    Inputbox(Application*, int, int, int, int, string _cur, string _s, vector<string>);
    void draw() override;
    void handle(genv::event ev, Widget*) override;
    std::string getText();

};

#endif // INPUTBOX_HPP
