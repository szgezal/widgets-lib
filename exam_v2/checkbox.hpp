#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widget.hpp"

class Checkbox : public Widget
{
protected:
    bool checked = false;
    std::string type;
public:
    Checkbox(Application*, int, int, int, int, std::string);
    void draw() override;
    void handle(genv::event, Widget*) override;
};

#endif // CHECKBOX_HPP
