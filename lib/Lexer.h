//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_LEXER_H
#define GTK_ALGEBRA_TEST_LEXER_H

#include <string>
#include <queue>
#include "Token.h"

using std::string;
using std::queue;

class Lexer {
private:
    string full_str;
    queue<char> char_backlog;
    char pop();
public:
    Lexer(const string &fullStr);

    Token next();
};


#endif //GTK_ALGEBRA_TEST_LEXER_H
