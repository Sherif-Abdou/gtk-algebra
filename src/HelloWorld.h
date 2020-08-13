//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_HELLOWORLD_H
#define GTK_ALGEBRA_TEST_HELLOWORLD_H

#include <iostream>

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/window.h>

class HelloWorld: public Gtk::Window {
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    void on_clicked();

    Gtk::Button btn;
};


#endif //GTK_ALGEBRA_TEST_HELLOWORLD_H
