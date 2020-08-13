//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_CONSTANT_H
#define GTK_ALGEBRA_TEST_CONSTANT_H


#include "Expression.h"

struct Constant: public Expression {
    double value;

    Constant(double value);
};


#endif //GTK_ALGEBRA_TEST_CONSTANT_H
