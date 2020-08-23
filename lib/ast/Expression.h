//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_EXPRESSION_H
#define GTK_ALGEBRA_TEST_EXPRESSION_H

#include <memory>

class Constant;

using std::unique_ptr;

struct Expression {
    virtual bool has_variable() = 0;
    virtual unique_ptr<Constant> simplify() = 0;
    virtual std::string to_string() = 0;
};


#endif //GTK_ALGEBRA_TEST_EXPRESSION_H
