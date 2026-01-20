#include <Creepy/Parser.hpp>


namespace Creepy{
    
    Parser Parser_CreateParser(StringView srcCode, Arena nodeArena, uint32_t maxNodeCanStore){
        return Parser{
            .srcCode = srcCode,
            .lexer = Lexer_CreateLexer(srcCode),
            .nodeContainer = NodeContainer_CreateNodeContainer(nodeArena, maxNodeCanStore)
        };
    }

    Node Parser_ParseToReturnNode(Parser& parser) {
        return {};
    }
    
    Node Parser_ParseToConstantNode(Parser& parser) {
        return {};
    }
}