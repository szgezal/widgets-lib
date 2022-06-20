#include "graphics.hpp"

#include "dropdown.hpp"
#include "inputbox.hpp"
#include "listbox.hpp"
#include "spinbox.hpp"
#include "statictext.hpp"
#include "textreader.hpp"
#include "checkbox.hpp"

#include <vector>
#include <time.h>
#include <fstream>


#include <iostream>
using namespace std;

const int height = 600, width = 1000;


class App : public Application {
protected:
    Spinbox* spb1;
    Spinbox* spb2;
    Dropdown* dd1;
    Dropdown* dd2;
    FunktorButton* fb;
    FunktorButton* save;
    FunktorButton* to_left;
    FunktorButton* to_right;
    FunktorButton* add_element;
    FunktorButton* delete_element;
    FunktorButton* search;
    Inputbox* ib;
    StaticText* title;
    Textreader* tr;
    Listbox* lb1;
    Listbox* lb2;
    Checkbox* cb;
    Checkbox* rb;

public:
    App(int width, int height) : Application(width, height) {
        std::vector<std::string> elements1 = /*{};*/
        {"Text 0","Text 1","Text 2","Text 3","Text 4","Text 5","Text 6","Text 7","Text 8","Text 9"};

        std::vector<std::string> elements2 = /*{};*/
        {"Text 10","Text 11","Text 12","Text 13","Text 14","Text 15","Text 16","Text 17","Text 18","Text 19"};

        std::string filename = "saved.txt";

        dd1 = new Dropdown(this, 20, 140, 200, 40, elements1, 4); //always define as first object
        dd2 = new Dropdown(this, 350, 140, 200, 40, elements2, 3); //always define as first object

        lb1 = new Listbox(this, 350, 350, 200, 208, elements1);
        lb2 = new Listbox(this, 630, 350, 200, 208, elements2);

        to_left = new FunktorButton(this, 240, 140, 40, 40, "->",
                      [=](){moveItem(lb1, lb2); focused = lb1;});  //always define after dropdown or listbox

        to_right = new FunktorButton(this, 290, 140, 40, 40, "<-",
                       [=](){moveItem(lb2, lb1); focused = lb2;}); //always define after dropdown or listbox

        add_element = new FunktorButton(this, 730, 140, 40, 40, "Add",
                          [=](){addItem(ib->getText(), lb1);}); //always define after dropdown or listbox
        delete_element = new FunktorButton(this, 780, 140, 40, 40, "Del",
                             [=](){deleteItem(lb1);}); //always define after dropdown or listbox

//        search = new FunktorButton(this, 630, 190, 40, 40, "Filter",
//                             [=](){filter(ib->getText(), lb1);}); //always define after dropdown or listbox

        spb1 = new Spinbox(this, 20, 60, 200, 40, -20, 20);
        spb2 = new Spinbox(this, 350, 60, 200, 40, -30, 30);

        ib = new Inputbox(this, 630, 60, 200, 40, "|", {});

        fb = new FunktorButton(this, 630, 140, 40, 40, "F", [=](){}); //empty funktor button (does nothing)
        save = new FunktorButton(this, 680, 140, 40, 40, "Save", [=](){saveToTxt(filename); textRead();});

        title = new StaticText(this, 20, 20, 200, 20, "Static text", 255, 255, 255, 16);

        tr = new Textreader(this, 20, 350, 200, 200, filename);

        cb = new Checkbox(this, 830, 140, 40, 40, "cb");
        rb = new Checkbox(this, 880, 140, 40, 40, "rb");
    }

    void saveToTxt(std::string filename){
        std::ofstream f(filename);
        f << spb1->getNum() << ", ";
        f << spb2->getNum() << "\n";
        f << lb1->getSelected() << ", ";
        f << lb2->getSelected();
        f.close();
    }

    void moveItem(Listbox* src, Listbox* dst) {
        if (src->getSelected() != "") {
            dst->addElement(src->getSelected());
            src->removeElement();
            src->setSelected();
        }
    }

    void addItem(std::string item, Listbox* dst) {
        if (item != "")
            dst->addElement(item);
    }

    void deleteItem(Listbox* list) {
        list->removeElement();
        list->setSelected();
    }

    void textRead() override {
        tr->read();
    }

    //Funktor button be like: help me step handler i'm stuck
    void postHandler(genv::event ev, Widget*) override{
        to_left->update(ev);
        to_left->draw();
        to_right->update(ev);
        to_right->draw();
    }

//    void filter(std::string item, Listbox* & target) {
//        if (item == ""){
//            target->setElements(target->getOriginalElements());
//            target->setFiltering(false);
//            return;
//        }

//        target->setFiltering(true);

//        std::vector<std::string> v = {};
//        for (std::string & items: target->getOriginalElements()) {
//            if (items == item)
//                v.push_back(items);
//        }
//        target->setElements(v);
//    }
};


int main()
{
    srand(time(NULL));

    App* app = new App(width, height);

    app->eventloop();

    return 0;
}
