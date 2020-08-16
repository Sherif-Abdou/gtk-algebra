//
// Created by Sherif Abdou on 8/16/20.
//

#ifndef GTK_ALGEBRA_TEST_SCOPEPARSER_H
#define GTK_ALGEBRA_TEST_SCOPEPARSER_H


#include "Parser.h"

class ScopeParser : public Parser {
public:
    unique_ptr<Expression> parse_side();
    explicit ScopeParser(Lexer &lexer);
private:
    void add_value(Expression *val, Expression*& expr);
    void add_value(unique_ptr<Expression> &val, Expression*& expr);

    Expression** current;


    void add_operation(std::__1::unique_ptr<Operation> &new_operation);

    void replace(Operation* in, Expression* from, unique_ptr<Expression> &to);

    void replace(Expression* in, Expression* from, unique_ptr<Operation> &to);

    OperationTypes get_type(Token token);

    Lexer return_lexer();
};


#endif //GTK_ALGEBRA_TEST_SCOPEPARSER_H
