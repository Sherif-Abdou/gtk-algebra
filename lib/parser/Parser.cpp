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
    if (auto *op = dynamic_cast<Operation *>(*this->current)) {
        lfs = std::move(curr_top);
    } else {
        lfs = unique_ptr<Expression>(*this->current);
    }
}

void Parser::add_value(Expression *val, Expression *&expr) {
    if (expr == nullptr) {
        expr = val;
        return;
    }
    if (auto *operation = dynamic_cast<Operation *>(expr)) {
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
    this->expr_stack = std::deque<Expression *>();
    Token token = this->lexer.next();
    while (token.type != tok_equals && token.type != tok_eof && token.type) {
        Expression *expression = !expr_stack.empty() ? expr_stack.back() : nullptr;
        if (expression == nullptr) {
            expr_stack.push_back(expression);
        }
        auto &expression_ref = expr_stack.back();
        if (token.type == tok_num) {
            add_value(new Constant(std::stod(token.iden)), expression_ref);
        } else if (token.type == tok_variable) {
            add_value(new Variable(token.iden), expression_ref);
        } else {
            OperationTypes type = get_type(token);

            auto operation = std::make_unique<Operation>(type);
            this->add_operation(operation);
        }
        token = this->lexer.next();
    }
    current = &this->expr_stack.front();
}

void Parser::add_operation(unique_ptr<Operation> &new_operation) {
    Expression *raw_back = this->expr_stack.back();
    if (auto *back = dynamic_cast<Operation *>(raw_back)) {
        if (precedent[back->type] <= precedent[new_operation->type]) {
            this->expr_stack.pop_back();
            if (!this->expr_stack.empty()) {
                auto *new_back = dynamic_cast<Operation *>(this->expr_stack.back());
                replace(new_back, back, new_operation);
                this->expr_stack.push_back(new_back->lfs.get());
                auto *new_operation_again = dynamic_cast<Operation *>(this->expr_stack.back());
                new_operation_again->lfs.reset(nullptr);
                replace(new_operation_again, nullptr, new_operation);
            } else {
                new_operation->lfs = std::move(this->curr_top);
                auto *new_operation_tmp = new_operation.get();
                this->curr_top = std::move(new_operation);
                this->expr_stack.push_back(new_operation_tmp);
            }
        } else {
            auto* op_ptr = new_operation.get();
            auto expanded_unique = std::move(reinterpret_cast<unique_ptr<Expression> &>(new_operation));
            back->rhs.swap(expanded_unique);
            op_ptr->lfs.swap(expanded_unique);
            this->expr_stack.push_back(back);
            this->expr_stack.push_back(op_ptr);
        }
    } else {
        this->expr_stack.pop_back();
        auto *new_operation_raw = new_operation.get();
        if (!this->expr_stack.empty()) {
            auto *new_back = this->expr_stack.back();
            replace(new_back, raw_back, new_operation);
        } else {
            add_value(raw_back, reinterpret_cast<Expression *&>(new_operation_raw));
            this->curr_top = std::move(new_operation);
        }
        this->expr_stack.push_back(new_operation_raw);
    }
}

void Parser::replace(Operation *in, Expression *from, unique_ptr<Expression> &to) {
    if (in->lfs.get() == from) {
        in->lfs.swap((to));
    } else if (in->rhs.get() == from) {
        in->rhs.swap((to));
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

OperationTypes Parser::get_type(Token token) {
    switch (token.type) {
        case tok_plus:
            return addition;
        case tok_minus:
            return subtraction;
        case tok_times:
            return multiplication;
        case tok_divide:
            return division;
        default:
            return static_cast<OperationTypes>(0);
    }
}
