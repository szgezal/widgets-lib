#ifndef SPINBOX_HPP
#define SPINBOX_HPP

#include "widget.hpp"
#include "button.hpp"

class Spinbox : public Widget
{
protected:
    int lowerlim, upperlim, n = rand() % (abs(upperlim - lowerlim)) - (abs(upperlim - lowerlim))/2;
    ButtonUp* btn1;
    ButtonDown* btn2;

public:
    Spinbox(Application*, int, int, int, int, int, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
    int getNum();
};

#endif // SPINBOX_HPP
