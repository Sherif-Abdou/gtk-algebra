//
// Created by Sherif Abdou on 8/13/20.
//

#include "Lexer.h"


char Lexer::pop() {
    if (!char_backlog.empty()) {
        auto val = char_backlog.back();
        char_backlog.pop();
        return val;
    }
    auto val = full_str[0];
    full_str.erase(0, 1);
    return val;
}

Token Lexer::next() {
    if (full_str.empty()) {
        return tok_eof;
    }

    char c = this->pop();
    while (isblank(c)) {
        c = this->pop();
    }

    string iden;

    if (isnumber(c)) {
        while (isnumber(c)) {
            iden += c;
            c = this->pop();
        }
        char_backlog.push(c);
        return {tok_num, iden};
    }

    switch (c) {
        case '+':
            return tok_plus;
        case '-':
            return tok_minus;
        case '*':
            return tok_times;
        case '/':
            return tok_divide;
        case '=':
            return tok_equals;
        default:
            return {tok_variable, string {c}};
    }
}

Lexer::Lexer(const string &fullStr) : full_str(fullStr) {}
