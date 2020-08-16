//
// Created by Sherif Abdou on 8/13/20.
//

#ifndef GTK_ALGEBRA_TEST_PARSER_H
#define GTK_ALGEBRA_TEST_PARSER_H


#include <unordered_map>
#include <deque>
#include "../lexer/Lexer.h"
#include "../ast/Expression.h"
#include "../ast/Operation.h"

using std::unique_ptr;

class Parser {
public:
    Parser(Lexer &lexer);

    void parse();

    const unique_ptr<Expression> &getLfs() const;
    const unique_ptr<Expression> &getRhs() const;
private:
    unique_ptr<Expression> lfs;
    unique_ptr<Expression> rhs;
protected:
    unique_ptr<Expression> curr_top;
    std::deque<Expression *> expr_stack;
    Lexer& lexer;
    std::unordered_map<int, int> precedent = std::unordered_map<int, int>();
};


#endif //GTK_ALGEBRA_TEST_PARSER_H
