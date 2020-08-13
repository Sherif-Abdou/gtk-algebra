//
// Created by Sherif Abdou on 8/13/20.
//

#include "HelloWorld.h"

HelloWorld::HelloWorld(): btn("Click me") {
    set_border_width(10);

    auto lambda = [](){};

    this->btn.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::on_clicked));

    this->add(this->btn);

    this->btn.show();
}

void HelloWorld::on_clicked() {
    std::cout << "Hello World" << std::endl;
}

HelloWorld::~HelloWorld() {

}
