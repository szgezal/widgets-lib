#include "listbox.hpp"
#include <math.h>
#include <sstream>
using namespace genv;

#include <iostream>
using namespace std;

Listbox::Listbox(Application* _parent, int _x, int _y, int _sx, int _sy,
                 std::vector<std::string> _elements, int _free_space):
                 Widget(_parent, _x, _y, _sx, _sy),
                 elements(_elements),
                 free_space(_free_space)
{

}

void Listbox::draw() {
    gout << color(120, 120, 120) << move_to(x, y) << box(size_x, size_y);
    gout << color(200, 200, 200) << move_to(x + 4, y + 4) << box(size_x - 8, size_y - 8);

    if (index_of_selected != -1 || item_vector.size() > 0)
        for (int i = wheel_offset; i < (size_y/40) + wheel_offset && (i >= 0 && i < int(elements.size())); i++) {
            if (i == index_of_selected) {
                gout << color(180, 180, 255) << move_to(x + 4, y + (i - wheel_offset) * 40 + 4)
                     << box(size_x - 8, (y + (i + 1 - wheel_offset) * 40 - 2) - (y + (i - wheel_offset) * 40 - 2));
            }
            gout << color(0, 0, 0) << move_to(x + size_x/2 - gout.twidth(elements[(i)])/2,
                (y + (20 + (gout.cascent() - gout.cdescent())/2)/2 + (i - wheel_offset) * 40))
                << text(elements[(i)]);
        }
}

void Listbox::handle(genv::event ev, Widget * w) {

    if (ev.button == btn_wheeldown && wheel_offset < int(item_vector.size()) - size_y/40) {
            wheel_offset++;
    } else if (ev.button == btn_wheelup && wheel_offset > 0) {
            wheel_offset--;
    }

    if (ev.button == btn_left && w->onWidget(ev)) {
        index_of_selected = floor((ev.pos_y - y) / 41) + wheel_offset;
        if (item_vector.size() == 0 || index_of_selected >= int(item_vector.size()))
            index_of_selected = -1;
    }
}

void Listbox::addItemToVector(std::string s, int n) {
    item_vector.push_back(new Item<string, int> (s, n));
}

void Listbox::addItemToFilteredVector(std::string s, int n) {
    filtered_item_vector.push_back(new Item<string, int> (s, n));
}

void Listbox::removeItemFromVector(int index) {
    item_vector.erase(item_vector.begin() + index);
}

void Listbox::removeItemFromFilteredVector(int index) {
    item_vector.erase(filtered_item_vector.begin() + index);
}

void Listbox::updateElements(bool checked) {
    elements.clear();
    if (!checked)
        for (size_t i = 0; i < item_vector.size(); i++) {
            stringstream ss;
            ss << item_vector[i]->getT1() << "(" << item_vector[i]->getT2() << ")";
            elements.push_back(ss.str());
        }
    else if (checked)
        for (size_t i = 0; i < filtered_item_vector.size(); i++) {
            stringstream ss;
            ss << filtered_item_vector[i]->getT1() << "(" << filtered_item_vector[i]->getT2() << ")";
            elements.push_back(ss.str());
        }
}

void Listbox::autoAdjustSelectedItem(bool checked) {
    if (index_of_selected > 0 && wheel_offset > 0) {
        index_of_selected--;
        wheel_offset--;
    }
    if (!checked)
        while(index_of_selected > int(item_vector.size()) - 1) {
            index_of_selected--;
            if (wheel_offset > 0){
                wheel_offset--;
            }
        }
    else if (checked)
        while(index_of_selected > int(filtered_item_vector.size()) - 1) {
            index_of_selected--;
            if (wheel_offset > 0){
                wheel_offset--;
            }
        }
}


//nem ellenorzott

//void Listbox::addElement(std::string s) {
//    for (std::string & el: elements)
//        if (el == "") {
//            el = s;
//            return;
//        }

//    elements.push_back(s);
//    //filtering
////    original_elements.push_back(s);
//}

//void Listbox::removeElement() {
//    if (index_of_selected != -1 && elements[index_of_selected] != "" && elements[index_of_selected] != "") {

//        elements.erase(elements.begin() + index_of_selected);

//        if (wheel_offset > 0)
//            wheel_offset--;

//        if (index_of_selected < size_y/40 && int(elements.size()) < size_y/40 && !filtering)
//            elements.push_back("");
//    }

//    //filtering
////    for (size_t i = 0; i < original_elements.size(); i++)
////        if (original_elements[i] == elements[index_of_selected]) {
////            original_elements.erase(elements.begin() + i);
////            return;
////        }
//}

//void Listbox::removeElement(int i) {
//    elements.erase(elements.begin() + i);

//    if (wheel_offset > 0)
//        wheel_offset--;
//}
