//
// Created by Sherif Abdou on 8/18/20.
//

#include <boost/test/unit_test.hpp>
#include "../lib/lexer/Lexer.h"
#include "../lib/parser/Parser.h"

BOOST_AUTO_TEST_SUITE(expression_tests)

BOOST_AUTO_TEST_CASE(test_check_variable) {
    auto lexer = Lexer("(3*x)+2=5");
    auto parser = Parser(lexer);

    parser.parse();

    const auto& left = parser.getLfs();
    const auto& right = parser.getRhs();
    BOOST_TEST(left->has_variable() == true);
    BOOST_TEST(right->has_variable() == false);
}

BOOST_AUTO_TEST_SUITE_END()