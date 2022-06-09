#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "widget.hpp"

class Listbox : public Widget
{
protected:
    std::vector<std::string> elements;
    std::vector<std::string> original_elements = elements;
    std::string selected;
    int index_of_selected = -1;
    int wheel_offset = 0;
    bool filtering = false;
public:
    Listbox(Application*, int, int, int, int, std::vector<std::string>);
    void draw() override;
    void handle(genv::event, Widget*) override;
    std::string getSelected();
    void setSelected();
    void resetSelected();
    void addElement(std::string);
    void removeElement();
    std::vector<std::string> getElements() {return elements;}
    std::vector<std::string> getOriginalElements() {return original_elements;}
    void setElements(std::vector<std::string> v) {elements = v;}
    void setFiltering(bool f) {filtering = f;}
};

#endif // LISTBOX_HPP
