#include "application.hpp"
#include "widget.hpp"

using namespace genv;

Application::Application(int width, int height) {
    gout.open(width, height);
    gout.load_font("LiberationSans-Regular.ttf");
}

void Application::eventloop() {
    for (Widget* w: widgets) {
        w->draw();
    }
    gout << refresh;

    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.button == btn_left) {
            focused = nullptr;
            for (Widget* w: widgets)
                if (w->onWidget(ev))
                    focused = w;
            //callbacks
            //textRead();
        }
        if (focused != nullptr)
            focused->handle(ev, focused);

        for (Widget* w: widgets)
            w->draw();

        //postHandler(ev, focused);

        gout << refresh;
    }
}

void Application::addWidget(Widget* w) {
    widgets.push_back(w);
}
