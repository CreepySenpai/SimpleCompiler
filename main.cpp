#include <Creepy/Logger.hpp>
#include <Creepy/Assert.hpp>
#include <Creepy/DynArray.hpp>
#include <Creepy/Node.hpp>
#include <Creepy/Lexer.hpp>
#include <Creepy/Parser.hpp>
#include <Creepy/Formater.hpp>


constexpr uint64_t ARENA_SIZE = 40 * 4096;

void testNodeContainer();
void testLexer();
void testParser();

int main(){

    // testNodeContainer();
    
    // LOG("--------------------------------------------------------------");

    // testLexer();
    
    // LOG("--------------------------------------------------------------");
    
    testParser();

    return 0;
}


void testNodeContainer() {
    uint8_t* buffer = new uint8_t[ARENA_SIZE]{};
    std::memset(buffer, 0, ARENA_SIZE);

    Creepy::NodeContainer nodeContainer = Creepy::NodeContainer_CreateNodeContainer(Creepy::Arena{.mem = buffer, .count = 0, .capacity = ARENA_SIZE}, 100);

    std::println("Done A");
    auto startNode = Creepy::NodeContainer_CreateStartNode(nodeContainer);
    std::println("Done B");
    auto constantNode = Creepy::NodeContainer_CreateConstantNode(nodeContainer, startNode, Creepy::NodeValueType::Uint32, Creepy::UInt32{69});
    std::println("Done C");
    auto endNode = Creepy::NodeContainer_CreateReturnNode(nodeContainer, startNode, constantNode);
    std::println("Done D");

    for(uint32_t i{}; i < nodeContainer.nodes.count; ++i){
        Creepy::NodeContainer_PrintNodeInfo(nodeContainer, i);
    }
}

void testLexer() {
    char srcCode[] = "return 69;";

    Creepy::Lexer lexer = Creepy::Lexer_CreateLexer(Creepy::StringView{.ptr = srcCode, .count = sizeof(srcCode) - 1});
    
    std::println("Val ne1: {}", Creepy::Lexer_GetAnyNextToken(lexer));
    std::println("Val ne2: {}", Creepy::Lexer_GetAnyNextToken(lexer));
    std::println("Val ne3: {}", Creepy::Lexer_GetAnyNextToken(lexer));
    std::println("Val ne4: {}", Creepy::Lexer_GetAnyNextToken(lexer));
}

void testParser() {
    uint8_t* buffer = new uint8_t[ARENA_SIZE]{};
    std::memset(buffer, 0, ARENA_SIZE);

    char srcCode[] = "return 69;";       // Test ok
    // char srcCode[] = "return 0;";       // Test ok
    // char srcCode[] = "ret;";             // Test fail
    // char srcCode[] = "return 0123";       // Test fail
    // char srcCode[] = "return -69;";       // Test fail
    // char srcCode[] = "return 69";         // Test fail
    // char srcCode[] = "return69";
    // char srcCode[] = "return 1;}";

    Creepy::Parser parser = Creepy::Parser_CreateParser(Creepy::StringView{.ptr = srcCode, .count = sizeof(srcCode) - 1}, 
        Creepy::Arena{.mem = buffer, .count = 0, .capacity = ARENA_SIZE}, 
        200);
    
    auto nodeParsed = Creepy::Parser_Parse(parser);

    Creepy::NodeContainer_PrintNodeInfo(parser.nodeContainer, nodeParsed);

    LOG("Parsed all node");
    
    for(uint32_t i{}; i < parser.nodeContainer.nodes.count; ++i){
        Creepy::NodeContainer_PrintNodeInfo(parser.nodeContainer, i);
    }
}
