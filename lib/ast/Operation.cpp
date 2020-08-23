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

    if (left_side_var  || this->type == OperationTypes::subtraction || this->type == OperationTypes::division) {
        unique_ptr<Expression> new_exp = std::make_unique<Operation>(this->reverses[type]);
        auto new_exp_ptr = dynamic_cast<Operation*>(new_exp.get());
        new_exp_ptr->rhs = std::move(this->rhs);
        new_exp_ptr->lfs = std::move(other_side);
        other_side = std::move(new_exp);
        if (this->type == OperationTypes::division && other_side->has_variable()) {
            this->lfs.swap(other_side);
        }
        return std::move(this->lfs);
    } else {
        unique_ptr<Expression> new_exp = std::make_unique<Operation>(this->reverses[type]);
        auto new_exp_ptr = dynamic_cast<Operation*>(new_exp.get());
        new_exp_ptr->lfs = std::move(this->lfs);
        new_exp_ptr->rhs = std::move(other_side);
        if (new_exp_ptr->type == OperationTypes::division) {
            new_exp_ptr->lfs.swap(new_exp_ptr->rhs);
        }
        other_side = std::move(new_exp);
        return std::move(this->rhs);
    }
}

unique_ptr<Constant> Operation::simplify() {
    if (this->has_variable()) {
        throw std::exception();
    }

    auto left = this->lfs->simplify()->value;
    auto right = this->rhs->simplify()->value;

    double new_value = 0.0;

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

std::string Operation::to_string() {
    auto operation_string = "";
    switch (this->type) {
        case addition:
            operation_string = "+";
            break;
        case subtraction:
            operation_string = "-";
            break;
        case multiplication:
            operation_string = "*";
            break;
        case division:
            operation_string = "/";
            break;
    }

    auto full = this->lfs->to_string() + " " + operation_string + " " + this->rhs->to_string();

    return isParenth ? "("+full+")" : full;
}


