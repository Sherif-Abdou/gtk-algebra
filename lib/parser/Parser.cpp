//
// Created by Sherif Abdou on 8/13/20.
//

#include "Parser.h"
#include "../ast/Constant.h"
#include "../ast/Operation.h"
#include "../ast/Variable.h"

Parser::Parser(const Lexer &lexer) : lexer(lexer) {
    this->precedent[addition] = 2;
    this->precedent[subtraction] = 2;
    this->precedent[multiplication] = 1;
    this->precedent[division] = 1;
    auto tmp = lfs.get();
    this->current = &tmp;
}

void Parser::parse() {
    this->parse_side();
    lfs = unique_ptr<Expression>(*this->current);
}

void Parser::add_value(Expression *val, Expression *&expr) {
    if (expr == nullptr) {
        expr = val;
        return;
    }
    if (auto* operation = dynamic_cast<Operation*>(expr)) {
        if (operation->lfs == nullptr) {
            operation->lfs = std::unique_ptr<Expression>(val);
        } else if (operation->rhs == nullptr) {
            operation->rhs = std::unique_ptr<Expression>(val);
        }
    } else {
        throw std::exception();
    }
}

void Parser::parse_side() {
    this->expr_stack = std::deque<Expression*>();
    Token token = this->lexer.next();
    Expression* expression = !expr_stack.empty() ? expr_stack.back(): nullptr;
    expr_stack.push_back(expression);
    auto& expression_ref = expr_stack.back();
    while (token.type != tok_equals && token.type != tok_eof) {
        if (token.type == tok_num) {
            add_value(new Constant(std::stod(token.iden)), expression_ref);
        } else if (token.type == tok_variable) {
            add_value(new Variable(token.iden), expression_ref);
        }
        token = this->lexer.next();
    }
    current = &this->expr_stack.front();
}

void Parser::add_operation(unique_ptr<Operation> &new_operation) {
    Expression* raw_back = this->expr_stack.back();
    if (auto* back = dynamic_cast<Operation*>(raw_back)) {
        if (precedent[back->type] < precedent[new_operation->type]) {
            this->expr_stack.pop_back();
            auto* new_back = dynamic_cast<Operation*>(this->expr_stack.back());
            auto* new_operation_raw = new_operation.get();
            replace(new_back, back, new_operation);
            this->expr_stack.push_back(new_back->lfs.get());
            auto* new_operation_again = dynamic_cast<Operation*>(this->expr_stack.back());
            new_operation_again->lfs.reset(nullptr);
            replace(new_operation_again, nullptr, new_operation);
        } else {
        }
    } else {
        this->expr_stack.pop_back();
        auto* new_back = this->expr_stack.back();
        auto* new_operation_raw = new_operation.get();
        replace(new_back, raw_back, new_operation);
        this->expr_stack.push_back(new_operation_raw);
    }
}

void Parser::replace(Operation *in, Expression *from, unique_ptr<Operation> &to) {
    if (in->lfs.get() == from) {
        in->lfs.swap(reinterpret_cast<unique_ptr<Expression> &>(to));
    } else if (in->rhs.get() == from) {
        in->rhs.swap(reinterpret_cast<unique_ptr<Expression> &>(to));
    }
}

void Parser::replace(Expression *in, Expression *from, unique_ptr<Operation> &to) {

}

const unique_ptr<Expression> &Parser::getLfs() const {
    return lfs;
}

const unique_ptr<Expression> &Parser::getRhs() const {
    return rhs;
}
