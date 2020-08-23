//
// Created by Sherif Abdou on 8/23/20.
//

#ifndef GTK_ALGEBRA_TEST_TOPBOX_H
#define GTK_ALGEBRA_TEST_TOPBOX_H

#include <gtkmm.h>
#include <gtkmm/window.h>
#include "../interfaces/TopBoxDelegate.h"

class TopBox: public Gtk::Box {
public:
    TopBox();
    std::string get_equation();

protected:
    Gtk::Button submit_solve = Gtk::Button("Solve");
    Gtk::Entry equation = Gtk::Entry();
    TopBoxDelegate* delegate;

    void on_submit_clicked();
public:
    TopBoxDelegate *getDelegate() const;

    void setDelegate(TopBoxDelegate *delegate);
};


#endif //GTK_ALGEBRA_TEST_TOPBOX_H
