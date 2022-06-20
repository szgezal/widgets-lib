#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "widget.hpp"

using namespace std;

template <typename T1, typename T2>
class Item {
protected:
    T1 t1;
    T2 t2;
public:
    Item(T1 _t1, T2 _t2) : t1(_t1), t2(_t2) {}
    T1 getT1() {return t1;}
    T2 getT2() {return t2;}
    void setT1(T1 _t1) {t1 = _t1;}
    void setT2(T2 _t2) {t2 = _t2;}
};

class Listbox : public Widget
{
protected:
    vector<string> elements;
    vector<string> original_elements = elements;
    int index_of_selected = -1;
    int wheel_offset = 0;
    bool filtering = false;

    //project
    vector<Item<string, int>*> item_vector = {};
    int free_space;

public:
    //constructor
    Listbox(Application*, int, int, int, int, std::vector<string>, int);

    //inherited functions
    void draw() override;
    void handle(genv::event, Widget*) override;

    //getters
    int getIndexOfSelected() {return index_of_selected;}
    Item<string, int>* getItem(int ind) {return item_vector[ind];}
    vector<Item<string, int>*> getItemVector() {return item_vector;}
    int getFreeSpace() {return free_space;}
//    vector<string> getElements() {return elements;}
//    vector<string> getOriginalElements() {return original_elements;}

    //setters
    void autoAdjustSelectedItem();
    void updateElements();
    void setFiltering(bool f) {filtering = f;}
    void addItemToVector(string, int);
    void setFreeSpace(int szam) {free_space = szam;}

    //others
    void removeItemFromVector(int);
//    void addElement(string);
//    void removeElement();
//    void removeElement(int);

};

#endif // LISTBOX_HPP
