//
// Created by Sherif Abdou on 8/23/20.
//

#include "TopBox.h"

TopBox::TopBox(): Box(static_cast<Gtk::Orientation>(GTK_ORIENTATION_HORIZONTAL), 0) {
    this->equation.set_placeholder_text("Enter equation");

    this->submit_solve.signal_clicked()
        .connect(sigc::mem_fun(*this, &TopBox::on_submit_clicked));

    this->pack_start(this->equation);
    this->pack_start(this->submit_solve);

    this->show_all_children(false);
}

std::string TopBox::get_equation() {
    return this->equation.get_text();
}

TopBoxDelegate *TopBox::getDelegate() const {
    return delegate;
}

void TopBox::setDelegate(TopBoxDelegate *delegate) {
    TopBox::delegate = delegate;
}

void TopBox::on_submit_clicked() {
    if (this->delegate != nullptr) {
        this->delegate->on_submit_clicked();
    }
}
