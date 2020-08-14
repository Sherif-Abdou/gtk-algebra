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


BOOST_AUTO_TEST_SUITE_END()
