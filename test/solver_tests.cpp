//
// Created by Sherif Abdou on 8/21/20.
//

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../lib/lexer/Lexer.h"
#include "../lib/parser/Parser.h"
#include "../lib/solver/Solver.h"

BOOST_AUTO_TEST_SUITE(solver_tests);

BOOST_AUTO_TEST_CASE(test_solve) {
    auto lexer = Lexer("(2*x)+3=5");
    auto parser = Parser(lexer);
    parser.parse();

    auto& left = parser.getLfs();
    auto& right = parser.getRhs();

    auto solver = Solver(std::move(left), std::move(right));

    auto sol = solver.solve();

    BOOST_TEST(sol->value == 1);
}

BOOST_AUTO_TEST_CASE(test_solve_again) {
    auto lexer = Lexer("(5*x)+3=5");
    auto parser = Parser(lexer);
    parser.parse();

    auto& left = parser.getLfs();
    auto& right = parser.getRhs();

    auto solver = Solver(std::move(left), std::move(right));

    auto sol = solver.solve();
    auto value = sol->value;

    std::cout << "Answer: " << value << std::endl;
    BOOST_TEST((value == 0.4));
}

BOOST_AUTO_TEST_CASE(test_divide_variable) {
    auto lexer = Lexer("(5/x)+3=5");
    auto parser = Parser(lexer);
    parser.parse();

    auto& left = parser.getLfs();
    auto& right = parser.getRhs();

    auto solver = Solver(std::move(left), std::move(right));

    auto sol = solver.solve();
    auto value = sol->value;

    std::cout << "Answer: " << value << std::endl;
    BOOST_TEST((value == 2.5));
}


BOOST_AUTO_TEST_SUITE_END()
