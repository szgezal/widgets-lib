#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include "graphics.hpp"

class Widget;

class Application {
protected:
    std::vector<Widget*> widgets;
    Widget* focused;
    genv::event loop_event;

public:
    Application(int, int);
    void eventloop();
    void addWidget(Widget*);
    virtual void textRead() = 0;
    virtual void postHandler(genv::event, Widget*) = 0;
};


#endif // APPLICATION_HPP
