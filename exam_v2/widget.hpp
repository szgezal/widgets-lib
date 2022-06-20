#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "application.hpp"

class Spinbox;

class Dropdown;

class Textreader;

class Widget
{
protected:
    Application* parent;
    Spinbox* sbparent;
    Dropdown* ddparent;
    Textreader* trparent;
    int x, y, size_x, size_y;

public:
    Widget(Application*, int, int, int, int);
    Widget(Spinbox*, int, int, int, int);
    Widget(Dropdown*, int, int, int, int);
    Widget(Textreader*, int, int, int, int);
    virtual bool onWidget(genv::event);
    virtual void draw() = 0;
    virtual void handle(genv::event, Widget*) = 0;
};

#endif // WIDGET_HPP
