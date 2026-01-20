#pragma once

#include <Creepy/Lexer.hpp>
#include <Creepy/Node.hpp>

namespace Creepy{

    struct Parser{
        StringView srcCode;
        Lexer lexer;
        NodeContainer nodeContainer;
    };

    Parser Parser_CreateParser(StringView srcCode, Arena nodeArena, uint32_t maxNodeCanStore);

    Node Parser_ParseToReturnNode(Parser& parser);
    
    Node Parser_ParseToConstantNode(Parser& parser);
}