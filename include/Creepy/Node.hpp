#pragma once

#include <cstdint>
#include <variant>
#include <Creepy/DynArray.hpp>

namespace Creepy {
    
    enum class NodeType : uint32_t {
        None = 0,
        Start,
        Return,
        Constant
    };

    enum class NodeValueType : uint32_t {
        None = 0,
        Sint32, Sint64,
        Uint32, Uint64,
        Pointer
    };

    using NodeValue = std::variant<int32_t, int64_t, uint32_t, uint64_t, uintptr_t>;


    struct Node{
        uint64_t nodeID{};
        NodeType nodeType{NodeType::None};
        NodeValueType nodeValueType{NodeValueType::None};
        NodeValue nodeValue{0};

        DynArray<Node*> inputNodes;
        DynArray<Node*> outputNodes;
    };


    struct Arena;

    Node* Node_CreateStartNode(Arena& arena);
    Node* Node_CreateReturnNode(Arena& arena, Node* controlNode, Node* dataNode);
    Node* Node_CreateConstantNode(Arena& arena, NodeValueType type, NodeValue val);

    Node* Node_GetControlNode(const Node* returnNode);
    Node* Node_GetExpresionNode(const Node* returnNode);

    bool Node_IsControlFlow(const Node* node);
}