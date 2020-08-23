//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_OPERATION_H
#define GTK_ALGEBRA_TEST_OPERATION_H


#include <memory>
#include <unordered_map>
#include "Expression.h"
#include "Constant.h"


using std::unique_ptr;

enum OperationTypes {
    addition = -1,
    subtraction = -2,
    multiplication = -3,
    division = -4
};

class Operation: public Expression {
private:
    std::unordered_map<OperationTypes, OperationTypes> reverses = std::unordered_map<OperationTypes, OperationTypes>();
public:
    Operation(OperationTypes type);

    bool has_variable() override;

    unique_ptr<Expression> solve(unique_ptr<Expression> &other_side);

    unique_ptr<Constant> simplify() override;

    unique_ptr<Expression> lfs;
    unique_ptr<Expression> rhs;
    OperationTypes type;
    bool isParenth;
};


#endif //GTK_ALGEBRA_TEST_OPERATION_H
