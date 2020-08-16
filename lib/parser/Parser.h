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
private:
    Lexer lexer;
    std::unordered_map<int, int> precedent = std::unordered_map<int, int>();
    std::deque<Expression*> expr_stack;

public:
    Parser(const Lexer &lexer);
    void parse();
    const unique_ptr<Expression> &getLfs() const;

private:
    unique_ptr<Expression> lfs;
    unique_ptr<Expression> rhs;
    unique_ptr<Expression> curr_top;
public:
    const unique_ptr<Expression> &getRhs() const;

private:
    Expression** current;

    OperationTypes get_type(Token token);
    void add_value(Expression *val, Expression*& expr);
    void parse_side();
    void add_operation(unique_ptr<Operation> &new_operation);
    void replace(Operation* in, Expression* from, unique_ptr<Expression> &to);
    void replace(Expression* in, Expression* from, unique_ptr<Operation> &to);
};


#endif //GTK_ALGEBRA_TEST_PARSER_H
