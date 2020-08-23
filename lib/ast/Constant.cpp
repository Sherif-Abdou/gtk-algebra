//
// Created by Sherif Abdou on 8/13/20.
//

#include "Constant.h"
#include <exception>


Constant::Constant(double value) : value(value) {}

bool Constant::has_variable() {
    return false;
}

unique_ptr<Constant> Constant::simplify() {
    auto new_const = std::make_unique<Constant>(this->value);

    return std::move(new_const);
}

