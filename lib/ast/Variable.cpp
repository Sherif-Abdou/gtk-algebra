//
// Created by Sherif Abdou on 8/13/20.
//

#include "Variable.h"
#include <exception>

Variable::Variable(const Variable::string &name) : name(name) {}

bool Variable::has_variable() {
    return true;
}

unique_ptr<Constant> Variable::simplify() {
    throw std::exception();
}
