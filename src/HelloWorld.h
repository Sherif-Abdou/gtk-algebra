//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_HELLOWORLD_H
#define GTK_ALGEBRA_TEST_HELLOWORLD_H

#include <iostream>

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/window.h>
#include "ui/TopBox.h"

class HelloWorld: public Gtk::Window, public TopBoxDelegate {
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    virtual void on_submit_clicked() override;

    TopBox top_box {};
    Gtk::Box main_box = Gtk::Box(static_cast<Gtk::Orientation>(GTK_ORIENTATION_VERTICAL), 10);
    Gtk::Label answer_label {};
};


#endif //GTK_ALGEBRA_TEST_HELLOWORLD_H
