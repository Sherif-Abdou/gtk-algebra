//
// Created by Sherif Abdou on 8/13/20.
//

#include "HelloWorld.h"

HelloWorld::HelloWorld() {
    set_border_width(10);

    this->top_box.setDelegate(this);

    this->main_box.pack_start(this->top_box);
    this->main_box.pack_start(this->answer_label);
    this->add(main_box);
    this->show_all_children();
}

HelloWorld::~HelloWorld() {

}

void HelloWorld::on_submit_clicked() {
    std::cout << "submit" << std::endl;

    auto text = this->top_box.get_equation();



    this->answer_label.set_text(text);
}
