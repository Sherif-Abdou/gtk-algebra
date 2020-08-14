//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_TOKEN_H
#define GTK_ALGEBRA_TEST_TOKEN_H

#include <string>

using std::string;

enum TokenTypes {
    tok_unknown = 0,
    tok_num = -1,
    tok_variable = -2,
    tok_plus = -3,
    tok_minus = -4,
    tok_times = -5,
    tok_divide = -6,
    tok_equals = -7,
    tok_eof = -8
};

struct Token {
    Token();

    Token(TokenTypes type, const string &iden);
    Token(TokenTypes type);

    TokenTypes type;
    string iden;
};


#endif //GTK_ALGEBRA_TEST_TOKEN_H
