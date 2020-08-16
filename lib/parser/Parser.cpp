//
// Created by Sherif Abdou on 8/13/20.
//

#include "Parser.h"
#include "../ast/Constant.h"
#include "../ast/Operation.h"
#include "../ast/Variable.h"
#include "ScopeParser.h"

Parser::Parser(Lexer &lexer) : lexer(lexer) {
    this->precedent[addition] = 2;
    this->precedent[subtraction] = 2;
    this->precedent[multiplication] = 1;
    this->precedent[division] = 1;
}

void Parser::parse() {
    ScopeParser sub_parser_left = ScopeParser(this->lexer);
    auto ptr_left = sub_parser_left.parse_side();
    lfs = std::move(ptr_left);

    ScopeParser sub_parser_right = ScopeParser(this->lexer);
    auto ptr_right = sub_parser_right.parse_side();
    rhs = std::move(ptr_right);
//    if (auto *op = dynamic_cast<Operation *>(ptr.get())) {
//    } else {
//        lfs = unique_ptr<Expression>(ptr.get());
//    }
}

const unique_ptr<Expression> &Parser::getLfs() const {
    return lfs;
}

const unique_ptr<Expression> &Parser::getRhs() const {
    return rhs;
}

