//
// Created by Sherif Abdou on 8/13/20.
//

#include "Token.h"

Token::Token(TokenTypes type, const string &iden) : type(type), iden(iden) {

}

Token::Token(TokenTypes type) : type(type), iden("") {}
