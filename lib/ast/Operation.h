//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_OPERATION_H
#define GTK_ALGEBRA_TEST_OPERATION_H


#include "Expression.h"

enum OperationTypes {
    addition = -1,
    subtraction = -2,
    multiplication = -3,
    division = -4
};

struct Operation: public Expression {
    Operation(OperationTypes type);

    Expression lfs;
    Expression rhs;
    OperationTypes type;
};


#endif //GTK_ALGEBRA_TEST_OPERATION_H
