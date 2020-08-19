//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_OPERATION_H
#define GTK_ALGEBRA_TEST_OPERATION_H


#include <memory>
#include "Expression.h"


using std::unique_ptr;

enum OperationTypes {
    addition = -1,
    subtraction = -2,
    multiplication = -3,
    division = -4
};

struct Operation: public Expression {
    Operation(OperationTypes type);

    bool has_variable() override;

    unique_ptr<Expression> lfs;
    unique_ptr<Expression> rhs;
    OperationTypes type;
    bool isParenth;
};


#endif //GTK_ALGEBRA_TEST_OPERATION_H
