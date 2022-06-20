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
#include <sstream>


#include <iostream>
using namespace std;

const int height = 600, width = 500;


class App : public Application {
protected:
    Spinbox* spb1;
    FunktorButton* add_button;
    FunktorButton* delete_button1;
    FunktorButton* delete_button2;
    Inputbox* ib;
    StaticText* free_space_text;
    Listbox* lb1;
    Listbox* lb2;

    /*
    Spinbox* spb2;
    Dropdown* dd1;
    Dropdown* dd2;
    FunktorButton* fb;
    FunktorButton* save;
    FunktorButton* to_left;
    FunktorButton* to_right;
    FunktorButton* _search;
    Textreader* tr;
    Checkbox* cb;
    Checkbox* rb;
    */

public:
    App(int width, int height) : Application(width, height) {
        std::vector<std::string> elements1 = {};

        std::vector<std::string> elements2 = {};

        std::string filename = "saved.txt";

        ib = new Inputbox(this, 20, 20, 200, 40, "|", "", {});

        spb1 = new Spinbox(this, 240, 20, 200, 40, 1, 10000);

        lb1 = new Listbox(this, 20, 140, 200, 208, elements1, 25);
        lb2 = new Listbox(this, 240, 140, 200, 208, elements2, 25);

        add_button = new FunktorButton(this, 20, 80, 80, 40, "Uj elem",
                          [=](){addItem(ib->getText(), spb1->getNum(), lb1); focused = nullptr;}); //always define after dropdown or listbox

        delete_button1 = new FunktorButton(this, 20, 360, 80, 40, "Torol1",
                          [=](){deleteItem(lb1); focused = lb1;}); //always define after dropdown or listbox

        delete_button2 = new FunktorButton(this, 240, 360, 80, 40, "Torol2",
                          [=](){deleteItem(lb2); focused = lb2;}); //always define after dropdown or listbox

        stringstream ss;
        ss << "az elsodleges taroloban meg szabad: " << lb1->getFreeSpace();
        free_space_text = new StaticText(this, 0, 420, 350, 20, ss.str(), 255, 255, 255, 16);


        /*
        {"Text 0","Text 1","Text 2","Text 3","Text 4","Text 5","Text 6","Text 7","Text 8","Text 9"};
        {"Text 10","Text 11","Text 12","Text 13","Text 14","Text 15","Text 16","Text 17","Text 18","Text 19"};

        //dd1 = new Dropdown(this, 20, 140, 200, 40, elements1, 4); //always define as first object
        //dd2 = new Dropdown(this, 350, 140, 200, 40, elements2, 3); //always define as first object

        to_left = new FunktorButton(this, 240, 140, 40, 40, "->",
                      [=](){moveItem(lb1, lb2); focused = lb1;});  //always define after dropdown or listbox

        to_right = new FunktorButton(this, 290, 140, 40, 40, "<-",
                       [=](){moveItem(lb2, lb1); focused = lb2;}); //always define after dropdown or listbox

        _search = new FunktorButton(this, 630, 190, 40, 40, "Filter",
                             [=](){filter(ib->getText(), lb1);}); //always define after dropdown or listbox

        spb2 = new Spinbox(this, 350, 60, 200, 40, -30, 30);

        fb = new FunktorButton(this, 630, 140, 40, 40, "F", [=](){}); //empty funktor button (does nothing)
        save = new FunktorButton(this, 680, 140, 40, 40, "Save", [=](){saveToTxt(filename); textRead();});

        tr = new Textreader(this, 20, 350, 200, 200, filename);

        cb = new Checkbox(this, 830, 140, 40, 40, "cb");
        rb = new Checkbox(this, 880, 140, 40, 40, "rb");

        */
    }


    void moveItem(Listbox* src, Listbox* dst) {
        if (src->getIndexOfSelected() != -1) {
            dst->addItemToVector(src->getItem(src->getIndexOfSelected())->getT1(), src->getItem(src->getIndexOfSelected())->getT2());
            src->removeItemFromVector(src->getIndexOfSelected());
            src->updateElements();
            dst->updateElements();
            src->autoAdjustSelectedItem();
            src->draw();
        }
    }

    void addItem(std::string item, int size, Listbox* dst) {
        if (item != "") {
            if (dst->getFreeSpace() - size >= 0) {
                dst->addItemToVector(item, size);
                dst->updateElements();
                dst->setFreeSpace(dst->getFreeSpace() - size);
                dst->autoAdjustSelectedItem();
                dst->draw();
            } else if (lb2->getFreeSpace() - size >= 0) {
                lb2->addItemToVector(item, size);
                lb2->updateElements();
                lb2->setFreeSpace(lb2->getFreeSpace() - size);
                lb2->autoAdjustSelectedItem();
                lb2->draw();
            }

            stringstream ss;
            ss << "az elsodleges taroloban meg szabad: " << dst->getFreeSpace();
            free_space_text->setText(ss.str(), 255, 255, 255);
        }
    }

    void deleteItem(Listbox* list) {

        //simple delete
        if (list->getItemVector().size() > 0 && list->getIndexOfSelected() != -1) {

            if (list == lb1) {
                int tmp = list->getFreeSpace() + list->getItem(list->getIndexOfSelected())->getT2();

                list->removeItemFromVector(list->getIndexOfSelected());
                list->updateElements();
                list->setFreeSpace(tmp);
                list->autoAdjustSelectedItem();
                list->draw();

                stringstream ss;
                ss << "az elsodleges taroloban meg szabad: " << tmp;
                free_space_text->setText(ss.str(), 255, 255, 255);
            } else {
                list->removeItemFromVector(list->getIndexOfSelected());
                list->updateElements();
                list->autoAdjustSelectedItem();
                list->draw();
            }
        }

        //moving items
        if (lb1->getFreeSpace() != 0) {

            int i = 0;

            while (lb2->getItemVector().size() != 0 && i != -1) {
                for (size_t j = 0; j < lb2->getItemVector().size(); j++)
                    if (lb2->getItem(j)->getT2() < lb2->getItem(i)->getT2())
                        i = j;

                if (i != -1 && lb2->getItem(i)->getT2() <= lb1->getFreeSpace()) {
                    lb1->addItemToVector(lb2->getItem(i)->getT1(), lb2->getItem(i)->getT2());
                    lb1->setFreeSpace(lb1->getFreeSpace() - lb2->getItem(i)->getT2());
                    lb2->removeItemFromVector(i);
                    lb1->updateElements();
                    lb2->updateElements();

                    lb1->autoAdjustSelectedItem();
                    lb1->draw();
                    lb2->autoAdjustSelectedItem();
                    lb2->draw();

                    stringstream ss;
                    ss << "az elsodleges taroloban meg szabad: " << lb1->getFreeSpace();
                    free_space_text->setText(ss.str(), 255, 255, 255);

                    i = 0;
                } else
                    i = -1;
            }
        }
    }


//    //Funktor button be like: help me step handler i'm stuck
//    void postHandler(genv::event ev, Widget*) override{

//        delete_button1->update(ev);
//        delete_button1->draw();
//        delete_button2->update(ev);
//        delete_button2->draw();
//        add_button->update(ev);
//        add_button->draw();

//        // eredeti ez alatt
//        to_left->update(ev);
//        to_left->draw();
//        to_right->update(ev);
//        to_right->draw();


//    }


    /*
    void saveToTxt(std::string filename){
        std::ofstream f(filename);
        f << spb1->getNum() << ", ";
        f << spb2->getNum() << "\n";
        f << lb1->getSelected() << ", ";
        f << lb2->getSelected();
        f.close();
    }
    */
/*
    void textRead() override {
        tr->read();
    }
*/





//    void filter(std::string item, Listbox* & target) {
//        if (item == ""){
//            target->updateElements(target->getOriginalElements());
//            target->setFiltering(false);
//            return;
//        }

//        target->setFiltering(true);

//        std::vector<std::string> v = {};
//        for (std::string & item_vector: target->getOriginalElements()) {
//            if (item_vector == item)
//                v.push_back(item_vector);
//        }
//        target->updateElements(v);
//    }
};


int main()
{
    srand(time(NULL));

    App* app = new App(width, height);

    app->eventloop();

    return 0;
}
