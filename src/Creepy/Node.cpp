#include <Creepy/Node.hpp>
#include <Creepy/Logger.hpp>

namespace Creepy{

    NodeContainer NodeContainer_CreateNodeContainer(Arena nodeArena, uint32_t maxNode) {
        NodeContainer nodeContainer{
            .nodeArena = nodeArena
        };

        nodeContainer.nodes = DynArray_Create<Node>(nodeContainer.nodeArena, maxNode);

        return nodeContainer;
    }

    static void NodeContainer_AddCurrentNodeHandleToAllInputNode(NodeContainer& nodeContainer, NodeHandle currentNodeHandle){
        Node& currentNode = DynArray_At(nodeContainer.nodes, currentNodeHandle);

        for(uint32_t i{}; i < currentNode.inputNodes.count; ++i){
            const NodeHandle inputNodeHandle = DynArray_At(currentNode.inputNodes, i);

            Node& inputNode = DynArray_At(nodeContainer.nodes, inputNodeHandle);
            
            DynArray_Add(inputNode.outputNodes, nodeContainer.nodeArena, currentNodeHandle);
        }
    }

    NodeHandle NodeContainer_CreateStartNode(NodeContainer& nodeContainer) {
        const NodeHandle currentNodeHandle = nodeContainer.nodes.count;

        Node startNode{
            .nodeHandle = currentNodeHandle,
            .nodeType = NodeType::Start,
            .nodeValueType = NodeValueType::None,
            .inputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_INPUTNODE),
            .outputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_OUTPUTNODE)
        };

        DynArray_Add(nodeContainer.nodes, nodeContainer.nodeArena, startNode);

        return currentNodeHandle;
    }

    NodeHandle NodeContainer_CreateReturnNode(NodeContainer& nodeContainer, NodeHandle controlNodeHandle, NodeHandle dataNodeHandle) {
        const NodeHandle currentNodeHandle = nodeContainer.nodes.count;

        Node returnNode{
            .nodeHandle = currentNodeHandle,
            .nodeType = NodeType::Return,
            .nodeValueType = NodeValueType::None,
            .inputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_INPUTNODE),
            .outputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_OUTPUTNODE)
        };

        DynArray_Add(returnNode.inputNodes, nodeContainer.nodeArena, controlNodeHandle);

        DynArray_Add(returnNode.inputNodes, nodeContainer.nodeArena, dataNodeHandle);

        DynArray_Add(nodeContainer.nodes, nodeContainer.nodeArena, returnNode);

        NodeContainer_AddCurrentNodeHandleToAllInputNode(nodeContainer, currentNodeHandle);

        return currentNodeHandle;
    }

    NodeHandle NodeContainer_CreateConstantNode(NodeContainer& nodeContainer, NodeValueType valType, NodeValue val) {
        const NodeHandle currentNodeHandle = nodeContainer.nodes.count;

        Node constantNode{
            .nodeHandle = currentNodeHandle,
            .nodeType = NodeType::Constant,
            .nodeValueType = valType,
            .nodeValue = val,
            .inputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_INPUTNODE),
            .outputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_OUTPUTNODE)
        };

        DynArray_Add(nodeContainer.nodes, nodeContainer.nodeArena, constantNode);

        return currentNodeHandle;
    }

    NodeHandle NodeContainer_GetControlNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle) {
        const Node& returnNode = DynArray_At(nodeContainer.nodes, returnNodeHandle);

        ASSERT_MSG(returnNode.nodeType == NodeType::Return, "Expect returnNode");
        
        return returnNode.inputNodes.element[0];
    }

    NodeHandle NodeContainer_GetExpresionNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle) {
        const Node& returnNode = DynArray_At(nodeContainer.nodes, returnNodeHandle);

        ASSERT_MSG(returnNode.nodeType == NodeType::Return, "Expect returnNode");
        
        return returnNode.inputNodes.element[1];
    }

    bool NodeContainer_IsControlFlow(NodeContainer& nodeContainer, NodeHandle nodeHandle) {
        const Node& node = DynArray_At(nodeContainer.nodes, nodeHandle);

        switch (node.nodeType) {
            case NodeType::Return: [[fallthrough]];
            case NodeType::Start:{
                return true;
            }
        }

        return false;
    }

    void Node_PrintNodeInfo(const Node& node) {
        std::println("---------------------------");
        std::println("  nodeHandle: {}", node.nodeHandle);
        std::println("  nodeType: {}", (uint32_t)node.nodeType);
        std::println("  nodeValueType: {}", (uint32_t)node.nodeValueType);
        // std::println("  nodeValue: {}", node.nodeValue);

        std::print("  inputNodes: {} {} ", (uint64_t)node.inputNodes.element, node.inputNodes.count);
        for(uint32_t i{}; i < node.inputNodes.count; ++i){
            std::print(" {} ", node.inputNodes.element[i]);
        }
        std::println();

        std::print("  outputNodes: {} {}", (uint64_t)node.outputNodes.element, node.outputNodes.count);
        for(uint32_t i{}; i < node.outputNodes.count; ++i){
            std::print(" {} ", node.outputNodes.element[i]);
        }

        std::println();

        std::println("---------------------------");
    }

    void NodeContainer_PrintNodeInfo(const NodeContainer& nodeContainer, NodeHandle nodeHandle) {
        const Node& node = DynArray_At(nodeContainer.nodes, nodeHandle);
        Node_PrintNodeInfo(node);
    }
}