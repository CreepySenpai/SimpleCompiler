#pragma once

#include <cstdint>
#include <variant>
#include <Creepy/Arena.hpp>
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

    using NodeHandle = uint32_t;

    struct Node{
        // Use for default alloc dyn arr contain inputNode and outputNode
        static constexpr inline uint32_t DEFAULT_ALLOC_INPUTNODE = 10;
        static constexpr inline uint32_t DEFAULT_ALLOC_OUTPUTNODE = 10;

        NodeHandle nodeHandle{};
        NodeType nodeType{NodeType::None};
        NodeValueType nodeValueType{NodeValueType::None};
        NodeValue nodeValue{0};

        DynArray<NodeHandle> inputNodes;
        DynArray<NodeHandle> outputNodes;
    };

    struct NodeContainer{
        Arena nodeArena;
        DynArray<Node> nodes;
    };

    NodeContainer NodeContainer_CreateNodeContainer(Arena nodeArena, uint32_t maxNode);

    NodeHandle Node_CreateStartNode(NodeContainer& nodeContainer);
    
    NodeHandle Node_CreateReturnNode(NodeContainer& nodeContainer, NodeHandle controlNodeHandle, NodeHandle dataNodeHandle);
    
    NodeHandle Node_CreateConstantNode(NodeContainer& nodeContainer, NodeValueType valType, NodeValue val);

    NodeHandle Node_GetControlNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle);
    NodeHandle Node_GetExpresionNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle);

    bool Node_IsControlFlow(NodeContainer& nodeContainer, NodeHandle nodeHandle);

    void Node_PrintNodeInfo(const NodeContainer& nodeContainer, NodeHandle nodeHandle);
}