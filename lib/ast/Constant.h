//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_CONSTANT_H
#define GTK_ALGEBRA_TEST_CONSTANT_H


#include <memory>
#include "Expression.h"

using std::unique_ptr;

class Constant: public Expression {
public:
    double value;

    Constant(double value);

    bool has_variable() override;

    unique_ptr<Constant> simplify() override;
};


#endif //GTK_ALGEBRA_TEST_CONSTANT_H
