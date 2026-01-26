#pragma once

#include <Creepy/Lexer.hpp>
#include <Creepy/Node.hpp>

namespace Creepy{

    struct Parser{
        StringView srcCode;
        Lexer lexer;
        NodeContainer nodeContainer;
        NodeHandle startNode;
    };

    Parser Parser_CreateParser(StringView srcCode, Arena nodeArena, uint32_t maxNodeCanStore);

    NodeHandle Parser_Parse(Parser& parser);
}