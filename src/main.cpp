#include <iostream>
#include <gtkmm.h>
#include "HelloWorld.h"

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv, "something");
    auto button = Gtk::Button("Click me");

    HelloWorld window;

    std::cout << "Hello, World!" << std::endl;

    return app->run(window);
}
