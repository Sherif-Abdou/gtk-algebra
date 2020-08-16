//
// Created by Sherif Abdou on 8/13/20.
//

#include <boost/test/unit_test.hpp>
#include "../lib/lexer/Lexer.h"
#include "../lib/parser/Parser.h"
#include "../lib/ast/Constant.h"
#include "../lib/ast/Variable.h"

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(test_constant) {
    Lexer lexer = Lexer("5");
    Parser parser = Parser(lexer);

    parser.parse();

    auto left = parser.getLfs().get();

    BOOST_TEST(dynamic_cast<Constant*>(left)->value == 5);
}

BOOST_AUTO_TEST_CASE(test_variable) {
    Lexer lexer = Lexer("v");
    Parser parser = Parser(lexer);

    parser.parse();

    auto left = parser.getLfs().get();

    BOOST_TEST(dynamic_cast<Variable*>(left)->name == "v");
}

BOOST_AUTO_TEST_CASE(test_operation) {
    Lexer lexer = Lexer("3+1*5");
    Parser parser = Parser(lexer);

    parser.parse();

    auto left = parser.getLfs().get();

    auto* as_op = dynamic_cast<Operation*>(left);

    BOOST_TEST(as_op != nullptr);
    auto* left_side = dynamic_cast<Constant*>(as_op->lfs.get());
    BOOST_TEST(left_side != nullptr);
    BOOST_TEST(left_side->value == 3);
}

BOOST_AUTO_TEST_CASE(test_other_operation) {
    Lexer lexer = Lexer("2+3+4-5");
    Parser parser = Parser(lexer);

    parser.parse();

    auto right = dynamic_cast<Operation*>(parser.getLfs().get());
    auto right_const = dynamic_cast<Constant*>(right->rhs.get());
    BOOST_TEST(right_const != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
