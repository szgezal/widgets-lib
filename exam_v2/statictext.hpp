#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "widget.hpp"

class StaticText : public Widget
{
protected:
    std::string txt;
    int r, g, b, size;
public:
    StaticText(Application*, int, int, int, int, std::string, int, int, int, int);
    void draw() override;
    void handle(genv::event, Widget*) override;
    void changePlayer(std::string);
    std::string getText();
    void setText(std::string, int, int, int);
};

#endif // STATICTEXT_HPP
