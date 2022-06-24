#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widget.hpp"
#include <functional>

class Checkbox : public Widget
{
protected:
    bool checked = false;
    std::string type;
    std::function<void()> f;
public:
    Checkbox(Application*, int, int, int, int, std::string, std::function<void()>);
    void draw() override;
    void handle(genv::event, Widget*) override;
    bool getChecked() {return checked;}
};

#endif // CHECKBOX_HPP
