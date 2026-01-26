#include <Creepy/Parser.hpp>
#include <Creepy/Formater.hpp>

namespace Creepy{
    
    Parser Parser_CreateParser(StringView srcCode, Arena nodeArena, uint32_t maxNodeCanStore){
        Parser parser{
            .srcCode = srcCode,
            .lexer = Lexer_CreateLexer(srcCode),
            .nodeContainer = NodeContainer_CreateNodeContainer(nodeArena, maxNodeCanStore)
        };

        parser.startNode = NodeContainer_CreateStartNode(parser.nodeContainer);

        return parser;
    }


    static NodeHandle Parser_ParseToReturnNode(Parser& parser);

    static NodeHandle Parser_ParseToConstantNode(Parser& parser);

    static NodeHandle Parser_ParseStatement(Parser& parser);

    static NodeHandle Parser_ParseExpression(Parser& parser);

    static NodeHandle Parser_ParsePrimary(Parser& parser);

    static void Parser_CheckSyntax(Parser& parser, const char* syntax);

    static void Parser_SyntaxError(Parser& parser, const char* syntax);


    NodeHandle Parser_Parse(Parser& parser) {
        NodeHandle val = Parser_ParseStatement(parser);

        if(!Lexer_IsEOF(parser.lexer)){
            Parser_SyntaxError(parser, "unexpect");
        }

        return val;
    }


    NodeHandle Parser_ParseStatement(Parser& parser) {
        if(Lexer_IsMatchExact(parser.lexer, "return")){
            return Parser_ParseToReturnNode(parser);
        }

        Parser_SyntaxError(parser, "statement");

        return Node::INVALID_NODE_HANDLE;
    }


    NodeHandle Parser_ParseExpression(Parser& parser) {
        return Parser_ParsePrimary(parser);
    }

    NodeHandle Parser_ParsePrimary(Parser& parser) {
        Lexer_SkipWhiteSpace(parser.lexer);

        if(Lexer_IsNumber(parser.lexer)){
            return Parser_ParseToConstantNode(parser);
        }

        Parser_SyntaxError(parser, "constant");

        return Node::INVALID_NODE_HANDLE;
    }

    NodeHandle Parser_ParseToReturnNode(Parser& parser) {
        NodeHandle returnExpression = Parser_ParseExpression(parser);
        
        Parser_CheckSyntax(parser, ";");

        return NodeContainer_CreateReturnNode(parser.nodeContainer, parser.startNode, returnExpression);
    }
    
    NodeHandle Parser_ParseToConstantNode(Parser& parser) {
        const uint64_t num = Lexer_ParseToNumber(parser.lexer);
        return NodeContainer_CreateConstantNode(parser.nodeContainer, parser.startNode, NodeValueType::Uint64, UInt64{num});
    }

    void Parser_CheckSyntax(Parser& parser, const char* syntax) {
        if(!Lexer_IsMatch(parser.lexer, syntax)){
            Parser_SyntaxError(parser, syntax);
        }
    }

    void Parser_SyntaxError(Parser& parser, const char* syntax) {
        LOG("Syntax error, expected: {} but get {}", syntax, Lexer_GetAnyNextToken(parser.lexer));
    }
}