//
// Created by Sherif Abdou on 8/16/20.
//

#include "ScopeParser.h"
#include "../ast/Constant.h"
#include "../ast/Variable.h"

void ScopeParser::add_value(Expression *val, Expression *&expr) {
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

void ScopeParser::add_value(unique_ptr<Expression> &val, Expression *&expr) {
    if (expr == nullptr) {
        auto* val_tmp = val.get();
        curr_top = std::move(val);
        expr = val_tmp;
        return;
    }
    if (auto* operation = dynamic_cast<Operation*>(expr)) {
        if (operation->lfs == nullptr) {
            operation->lfs = std::move(val);
        } else if (operation->rhs == nullptr) {
            operation->rhs = std::move(val);
        }
    }
}

unique_ptr<Expression> ScopeParser::parse_side() {
    this->expr_stack = std::deque<Expression *>();
    Token token = this->lexer.next();
    while (token.type != tok_equals && token.type != tok_eof && token.type != tok_close_paren) {
        Expression *expression = !expr_stack.empty() ? expr_stack.back() : nullptr;
        if (expression == nullptr) {
            expr_stack.push_back(expression);
        }
        auto &expression_ref = expr_stack.back();
        if (token.type == tok_num) {
            add_value(new Constant(std::stod(token.iden)), expression_ref);
        } else if (token.type == tok_variable) {
            add_value(new Variable(token.iden), expression_ref);
        } else if (token.type == tok_open_paren) {
            ScopeParser sub_parser = ScopeParser(this->lexer);
            auto parsed = sub_parser.parse_side();
            add_value(parsed, expression_ref);
        } else {
            OperationTypes type = get_type(token);

            auto operation = std::__1::make_unique<Operation>(type);
            this->add_operation(operation);
        }
        token = this->lexer.next();
    }
    if (auto *constant = dynamic_cast<Constant *>(expr_stack.front())) {
        return unique_ptr<Constant>(constant);
    } else if (auto *variable = dynamic_cast<Variable *>(expr_stack.front())) {
        return unique_ptr<Variable>(variable);
    } else if (auto *op = dynamic_cast<Operation*>(expr_stack.front())) {
        op->isParenth = true;
        return std::move(this->curr_top);
    }
}

void ScopeParser::add_operation(std::__1::unique_ptr<Operation> &new_operation) {
    Expression *raw_back = this->expr_stack.back();
    auto *back = dynamic_cast<Operation *>(raw_back);
    if (back && !back->isParenth) {
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
            auto *op_ptr = new_operation.get();
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
            if (auto* op = dynamic_cast<Operation*>(raw_back)) {
                add_value(this->curr_top, reinterpret_cast<Expression *&>(new_operation_raw));
            } else {
                add_value(raw_back, reinterpret_cast<Expression *&>(new_operation_raw));
            }
            this->curr_top = std::move(new_operation);
        }
        this->expr_stack.push_back(new_operation_raw);
    }
}

void ScopeParser::replace(Operation *in, Expression *from, unique_ptr<Expression> &to) {
    if (in->lfs.get() == from) {
        in->lfs.swap((to));
    } else if (in->rhs.get() == from) {
        in->rhs.swap((to));
    }
}

void ScopeParser::replace(Expression *in, Expression *from, unique_ptr<Operation> &to) {

}

OperationTypes ScopeParser::get_type(Token token) {
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

Lexer ScopeParser::return_lexer() {
    return std::move(lexer);
}

ScopeParser::ScopeParser(Lexer &lexer) : Parser(lexer) {

}


