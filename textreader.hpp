#ifndef TEXTREADER_HPP
#define TEXTREADER_HPP

#include "widget.hpp"
#include "button.hpp"

class Textreader : public Widget
{
protected:
    std::vector<std::string> s;
    std::string filename;
    int rows;
    int wheel_offset = 0;
    ButtonUp* btn1;
    ButtonDown* btn2;

public:
    Textreader(Application*, int, int, int, int, std::string);
    void draw() override;
    void handle(genv::event, Widget*) override;
    void read();
};

#endif // TEXTREADER_HPP
