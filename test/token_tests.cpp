//
// Created by Sherif Abdou on 8/13/20.
//


#include <boost/test/unit_test.hpp>
#include "../lib/Lexer.h"

BOOST_AUTO_TEST_SUITE(token_test)

BOOST_AUTO_TEST_CASE(test_test) {
    BOOST_TEST(1 == 1);
}

BOOST_AUTO_TEST_CASE(test_lexer) {
    Lexer lexer = Lexer("5 + 3x = 8");
    BOOST_TEST(lexer.next().type == TokenTypes::tok_num);
    BOOST_TEST(lexer.next().type == TokenTypes::tok_plus);
    BOOST_TEST(lexer.next().type == TokenTypes::tok_num);
    BOOST_TEST(lexer.next().type == TokenTypes::tok_variable);
    BOOST_TEST(lexer.next().type == TokenTypes::tok_equals);
    BOOST_TEST(lexer.next().type == TokenTypes::tok_num);
}

BOOST_AUTO_TEST_SUITE_END()