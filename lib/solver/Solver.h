//
// Created by Sherif Abdou on 8/20/20.
//

#ifndef GTK_ALGEBRA_TEST_SOLVER_H
#define GTK_ALGEBRA_TEST_SOLVER_H


#include <string>
#include "../parser/Parser.h"

class Solver {
private:
    unique_ptr<Expression> left_side;
    unique_ptr<Expression> right_side;
public:
    explicit Solver(unique_ptr<Expression> left, unique_ptr<Expression> right);
    unique_ptr<Constant> solve();

    static unique_ptr<Constant> solve(std::string full_str);
};


#endif //GTK_ALGEBRA_TEST_SOLVER_H
