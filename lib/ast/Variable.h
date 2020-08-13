//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_VARIABLE_H
#define GTK_ALGEBRA_TEST_VARIABLE_H

#include <string>
#include "Expression.h"

struct Variable: public Expression {
    using string = std::string;

    string name;

    Variable(const string &name);
};


#endif //GTK_ALGEBRA_TEST_VARIABLE_H
