#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include "graphics.hpp"

class Widget;

class Application {
protected:
    std::vector<Widget*> widgets;
    Widget* focused = nullptr;

public:
    Application(int, int);
    void eventloop();
    void addWidget(Widget*);
    //virtual void postHandler(genv::event, Widget*) = 0;
    //virtual void textRead() = 0;

};


#endif // APPLICATION_HPP
