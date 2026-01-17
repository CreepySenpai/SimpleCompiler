#include <Creepy/Logger.hpp>
#include <Creepy/Assert.hpp>
#include <Creepy/DynArray.hpp>
#include <Creepy/Node.hpp>

int main(){

    constexpr uint64_t ARENA_SIZE = 40 * 4096;
    uint8_t* buffer = new uint8_t[ARENA_SIZE]{};
    std::memset(buffer, 0, ARENA_SIZE);

    Creepy::NodeContainer nodeContainer = Creepy::NodeContainer_CreateNodeContainer(Creepy::Arena{.mem = buffer, .count = 0, .capacity = ARENA_SIZE}, 100);

    std::println("Done A");
    auto startNode = Creepy::Node_CreateStartNode(nodeContainer);
    std::println("Done B");
    auto constantNode = Creepy::Node_CreateConstantNode(nodeContainer, Creepy::NodeValueType::Uint32, 69);
    std::println("Done C");
    auto endNode = Creepy::Node_CreateReturnNode(nodeContainer, startNode, constantNode);
    std::println("Done D");

    for(uint32_t i{}; i < nodeContainer.nodes.count; ++i){
        Creepy::Node_PrintNodeInfo(nodeContainer, i);
    }
    
    return 0;
}
