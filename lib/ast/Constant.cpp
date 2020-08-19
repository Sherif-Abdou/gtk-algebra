//
// Created by Sherif Abdou on 8/13/20.
//

#include "Constant.h"
#include <exception>

Constant::Constant(double value) : value(value) {}

bool Constant::has_variable() {
    return false;
}

