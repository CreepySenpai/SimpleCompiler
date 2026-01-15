#include <Creepy/Node.hpp>
#include <Creepy/Logger.hpp>

namespace Creepy{

    NodeContainer NodeContainer_CreateNodeContainer(Arena nodeArena, uint32_t maxNode) {
        return {
            .nodeArena = nodeArena,
            .nodes = DynArray_Create<Node>(nodeArena, maxNode)
        };
    }

    static void Node_AddCurrentNodeHandleToAllInputNode(NodeContainer& nodeContainer, NodeHandle currentNodeHandle){
        Node& currentNode = DynArray_At(nodeContainer.nodes, currentNodeHandle);
        
        for(uint32_t i{}; i < currentNode.inputNodes.count; ++i){
            const uint32_t inputNodeHandle = DynArray_At(currentNode.inputNodes, i);
            Node& inputNode = DynArray_At(nodeContainer.nodes, inputNodeHandle);
            
            DynArray_Add(inputNode.outputNodes, nodeContainer.nodeArena, currentNodeHandle);
        }
    }

    NodeHandle Node_CreateStartNode(NodeContainer& nodeContainer) {
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

    NodeHandle Node_CreateReturnNode(NodeContainer& nodeContainer, NodeHandle controlNodeHandle, NodeHandle dataNodeHandle) {
        const NodeHandle currentNodeHandle = nodeContainer.nodes.count;

        Node returnNode{
            .nodeHandle = currentNodeHandle,
            .nodeType = NodeType::Return,
            .nodeValueType = NodeValueType::None,
            .inputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_INPUTNODE),
            .outputNodes = DynArray_Create<NodeHandle>(nodeContainer.nodeArena, Node::DEFAULT_ALLOC_OUTPUTNODE)
        };

        std::println("Non1");
        DynArray_Add(returnNode.inputNodes, nodeContainer.nodeArena, controlNodeHandle);
        std::println("Non2");
        DynArray_Add(returnNode.inputNodes, nodeContainer.nodeArena, dataNodeHandle);
        std::println("Non3");
        DynArray_Add(nodeContainer.nodes, nodeContainer.nodeArena, returnNode);
        std::println("Non4");

        Node_AddCurrentNodeHandleToAllInputNode(nodeContainer, currentNodeHandle);
        std::println("Non5");

        return currentNodeHandle;
    }

    NodeHandle Node_CreateConstantNode(NodeContainer& nodeContainer, NodeValueType valType, NodeValue val) {
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

    NodeHandle Node_GetControlNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle) {
        const Node& returnNode = DynArray_At(nodeContainer.nodes, returnNodeHandle);

        ASSERT_MSG(returnNode.nodeType == NodeType::Return, "Expect returnNode");
        
        return returnNode.inputNodes.element[0];
    }

    NodeHandle Node_GetExpresionNode(NodeContainer& nodeContainer, NodeHandle returnNodeHandle) {
        const Node& returnNode = DynArray_At(nodeContainer.nodes, returnNodeHandle);

        ASSERT_MSG(returnNode.nodeType == NodeType::Return, "Expect returnNode");
        
        return returnNode.inputNodes.element[1];
    }

    bool Node_IsControlFlow(NodeContainer& nodeContainer, NodeHandle nodeHandle) {
        const Node& node = DynArray_At(nodeContainer.nodes, nodeHandle);

        switch (node.nodeType) {
            case NodeType::Return: [[fallthrough]];
            case NodeType::Start:{
                return true;
            }
        }

        return false;
    }

    void Node_PrintNodeInfo(const NodeContainer& nodeContainer, NodeHandle nodeHandle) {
        const Node& node = DynArray_At(nodeContainer.nodes, nodeHandle);

        std::println("---------------------------");
        std::println("  nodeHandle: {}", node.nodeHandle);
        std::println("  nodeType: {}", (uint32_t)node.nodeType);
        std::println("  nodeValueType: {}", (uint32_t)node.nodeValueType);
        // std::println("  nodeValue: {}", node.nodeValue);

        std::print("  inputNodes: ");
        for(uint32_t i{}; i < node.inputNodes.count; ++i){
            std::print(" {} ", node.inputNodes.element[i]);
        }
        std::println();

        std::print("  outputNodes: ");
        for(uint32_t i{}; i < node.outputNodes.count; ++i){
            std::print(" {} ", node.outputNodes.element[i]);
        }

        std::println();

        std::println("---------------------------");
    }
}