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
    auto tmp = lfs.get();
}

void Parser::parse() {
    ScopeParser sub_parser = ScopeParser(this->lexer);
    auto ptr = sub_parser.parse_side();
    lfs = std::move(ptr);
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

