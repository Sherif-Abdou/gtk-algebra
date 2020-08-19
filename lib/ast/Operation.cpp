//
// Created by Sherif Abdou on 8/13/20.
//

#include "Operation.h"

Operation::Operation(OperationTypes type) : type(type) {}

bool Operation::has_variable() {
    return this->lfs->has_variable() || this->rhs->has_variable();
}
