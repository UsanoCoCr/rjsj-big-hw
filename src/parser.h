#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <deque>
#include <memory>
#include <string>
#include <utility>
#include "./value.h"
#include "./token.h"

using ValuePtr = std::shared_ptr<Value>;

class Parser{
public:
    std::deque<TokenPtr> tokens;
    Parser(std::deque<TokenPtr> tokens);
    ValuePtr parse();
    ValuePtr parseTails();
};

#endif