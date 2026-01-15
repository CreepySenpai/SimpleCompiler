#include <Creepy/Logger.hpp>
#include <Creepy/Assert.hpp>
#include <Creepy/DynArray.hpp>
#include <Creepy/Node.hpp>

int main(){

    constexpr uint64_t ARENA_SIZE = 30 * 4096;
    uint8_t* buffer = new uint8_t[ARENA_SIZE]{};

    Creepy::Arena arena{
        .mem = buffer,
        .count = 0,
        .capacity = ARENA_SIZE
    };

    Creepy::Arena_Align(arena, 8);

    // auto myArr = Creepy::DynArray_Create<int>(arena, 20);

    // for(uint32_t i{}; i < myArr.capacity; ++i){
    //     myArr.element[i] = i;
    // }

    // for(uint32_t i{}; i < myArr.capacity; ++i){
    //     ASSERT_MSG(myArr.element[i] != i, "Hum wrong");

    //     LOG("Ele: {}", myArr.element[i]);
    // }

    Creepy::NodeContainer nodeContainer = Creepy::NodeContainer_CreateNodeContainer(arena, 100);

    std::println("Done A");

    for(uint32_t i{}; i < 10; ++i){
        Creepy::Node_CreateStartNode(nodeContainer);
    }

    std::println("Done B");

    for(uint32_t i{}; i < 10; ++i){
        Creepy::Node_CreateConstantNode(nodeContainer, Creepy::NodeValueType::Uint32, 69 + i);
    }

    std::println("Done C");

    for(uint32_t i{}; i < 10; ++i){
        Creepy::Node_CreateReturnNode(nodeContainer, i, i + 10);
    }

    std::println("Done D");

    for(uint32_t i{}; i < nodeContainer.nodes.count; ++i){
        Creepy::Node_PrintNodeInfo(nodeContainer, i);
    }

    std::println("Done E");

    return 0;
}
