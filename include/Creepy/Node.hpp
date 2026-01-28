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


    struct SInt32{
        int32_t val{};
    };

    struct SInt64{
        int64_t val{};
    };

    struct UInt32{
        uint32_t val{};
    };

    struct UInt64{
        uint64_t val{};
    };

    using NodeValue = std::variant<std::monostate, SInt32, SInt64, UInt32, UInt64, uintptr_t>;

    using NodeHandle = uint32_t;

    struct Node{
        // Use for default alloc dyn arr contain inputNode and outputNode
        static constexpr inline uint32_t DEFAULT_ALLOC_INPUTNODE = 10;
        static constexpr inline uint32_t DEFAULT_ALLOC_OUTPUTNODE = 10;
        static constexpr inline NodeHandle INVALID_NODE_HANDLE = 0xffffffff;

        NodeHandle nodeHandle{};
        NodeType nodeType{NodeType::None};
        NodeValueType nodeValueType{NodeValueType::None};
        NodeValue nodeValue{};
        
        DynArray<NodeHandle> inputNodes{};
        DynArray<NodeHandle> outputNodes{};
    };

    void Node_PrintNodeInfo(const Node& node);

    struct NodeContainer{
        Arena nodeArena;
        DynArray<Node> nodes;
    };

    
    NodeContainer NodeContainer_CreateNodeContainer(Arena nodeArena, uint32_t maxNode);

    NodeHandle NodeContainer_CreateStartNode(NodeContainer& nodeContainer);
    
    NodeHandle NodeContainer_CreateReturnNode(NodeContainer& nodeContainer, NodeHandle controlNodeHandle, NodeHandle dataNodeHandle);
    
    NodeHandle NodeContainer_CreateConstantNode(NodeContainer& nodeContainer, NodeHandle startNodeHandle, NodeValueType valType, NodeValue val);

    NodeHandle NodeContainer_GetControlNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle);
    NodeHandle NodeContainer_GetExpresionNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle);

    bool NodeContainer_IsControlFlow(NodeContainer& nodeContainer, NodeHandle nodeHandle);

    void NodeContainer_PrintNodeInfo(const NodeContainer& nodeContainer, NodeHandle nodeHandle);
}