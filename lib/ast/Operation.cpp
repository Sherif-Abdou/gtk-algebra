//
// Created by Sherif Abdou on 8/13/20.
//

#include "Operation.h"

Operation::Operation(OperationTypes type) : type(type) {
    this->reverses[OperationTypes::addition] = OperationTypes::subtraction;
    this->reverses[OperationTypes::subtraction] = OperationTypes::addition;
    this->reverses[OperationTypes::multiplication] = OperationTypes::division;
    this->reverses[OperationTypes::division] = OperationTypes::multiplication;
}

bool Operation::has_variable() {
    return this->lfs->has_variable() || this->rhs->has_variable();
}

unique_ptr<Expression> Operation::solve(unique_ptr<Expression> &other_side) {
    bool left_side_var = this->lfs->has_variable();

    if (left_side_var || this->type == OperationTypes::subtraction || this->type == OperationTypes::division) {
        unique_ptr<Expression> new_exp = std::make_unique<Operation>(this->reverses[type]);
        auto new_exp_ptr = dynamic_cast<Operation*>(new_exp.get());
        new_exp_ptr->rhs = std::move(this->rhs);
        new_exp_ptr->lfs = std::move(other_side);
        other_side = std::move(new_exp);
        return std::move(this->lfs);
    } else {
        unique_ptr<Expression> new_exp = std::make_unique<Operation>(this->reverses[type]);
        auto new_exp_ptr = dynamic_cast<Operation*>(new_exp.get());
        new_exp_ptr->lfs = std::move(this->lfs);
        new_exp_ptr->rhs = std::move(other_side);
        other_side = std::move(new_exp);
        return std::move(this->lfs);
    }
}

unique_ptr<Constant> Operation::simplify() {
    if (this->has_variable()) {
        throw std::exception();
    }

    auto left = this->lfs->simplify()->value;
    auto right = this->rhs->simplify()->value;

    auto new_value = 0;

    switch (this->type) {
        case addition:
            new_value = left+right;
            break;
        case subtraction:
            new_value = left-right;
            break;
        case multiplication:
            new_value = left*right;
            break;
        case division:
            new_value = left/right;
            break;
    }

    return std::make_unique<Constant>(new_value);
}
