#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

#include "widget.hpp"

class Button : public Widget
{
protected:
    bool down = false;

public:
    Button(Application*, int, int, int, int);
    Button(Spinbox*, int, int, int, int);
    Button(Dropdown*, int, int, int, int);
    Button(Textreader*, int, int, int, int);
    virtual void draw() override = 0;
    void handle(genv::event, Widget*) override;
};

class FunktorButton : public Button {
protected:
    std::string txt;
    std::function<void()> f;
public:
    FunktorButton(Application*, int, int, int, int, std::string, std::function<void()>);
    void draw() override;
    void handle(genv::event, Widget*) override;
    bool onWidget(genv::event) override;
    void update(genv::event);
    void setTxt(std::string s) {txt = s;}
};

class ButtonUp : public Button {
public:
    ButtonUp(Spinbox*, int, int, int, int);
    ButtonUp(Textreader*, int, int, int, int);
    void draw() override;
};

class ButtonDown : public Button {
public:
    ButtonDown(Spinbox*, int, int, int, int);
    ButtonDown(Textreader*, int, int, int, int);
    ButtonDown(Dropdown*, int, int, int, int);
    void draw() override;
};

#endif // BUTTON_HPP
