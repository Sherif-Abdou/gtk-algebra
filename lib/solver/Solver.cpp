//
// Created by Sherif Abdou on 8/20/20.
//

#include "Solver.h"

Solver::Solver(unique_ptr<Expression> left, unique_ptr<Expression> right) {
    this->left_side = std::move(left);
    this->right_side = std::move(right);
}

unique_ptr<Constant> Solver::solve() {
    bool var_in_left = this->left_side->has_variable();
    auto* left = this->left_side.get();
    auto* casted = dynamic_cast<Operation*>(left);
    while (var_in_left && casted) {
        this->left_side = casted->solve(this->right_side);

        left = this->left_side.get();
        var_in_left = this->left_side->has_variable();
        casted = dynamic_cast<Operation*>(left);
    }

    auto* right = this->right_side.get();
    casted = dynamic_cast<Operation*>(right);
    bool var_in_right = this->right_side->has_variable();
    return casted->simplify();
}

unique_ptr<Constant> Solver::solve(std::string full_str) {
    auto lexer = Lexer(full_str);
    auto parser = Parser(lexer);
    parser.parse();

    auto& left = parser.getLfs();
    auto& right = parser.getRhs();

    auto solver = Solver(std::move(left), std::move(right));

    auto sol = solver.solve();
    return std::move(sol);
}
