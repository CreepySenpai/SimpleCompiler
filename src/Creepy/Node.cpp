#include <Creepy/Node.hpp>
#include <Creepy/Logger.hpp>

namespace Creepy{
    static uint64_t g_totalNode = 0;

    Node* Node_CreateStartNode(Arena& arena) {
        Node* startNode = Arena_Alloc<Node>(arena);
        startNode->nodeID = g_totalNode++;
        startNode->nodeType = NodeType::Start;
        startNode->nodeValueType = NodeValueType::None;

        return startNode;
    }

    Node* Node_CreateReturnNode(Arena& arena, Node* controlNode, Node* dataNode) {
        Node* returnNode = Arena_Alloc<Node>(arena);

        returnNode->nodeID = g_totalNode++;
        returnNode->nodeType = NodeType::Return;
        returnNode->nodeValueType = NodeValueType::None;
        returnNode->inputNodes = DynArray_Create<Node*>(arena, 5);
        returnNode->outputNodes = DynArray_Create<Node*>(arena, 5);

        DynArray_Add(returnNode->inputNodes, arena, controlNode);
        DynArray_Add(returnNode->inputNodes, arena, dataNode);

        for(uint32_t i{}; i < returnNode->inputNodes.count; ++i){
            if(returnNode->inputNodes.element[i]){
                DynArray_Add(returnNode->outputNodes, arena, returnNode);
            }
        }

        return returnNode;
    }

    Node* Node_CreateConstantNode(Arena& arena, NodeValueType type, NodeValue val) {
        Node* constantNode = Arena_Alloc<Node>(arena);


        constantNode->nodeID = g_totalNode++;
        constantNode->nodeType = NodeType::Constant;
        constantNode->nodeValueType = type;
        constantNode->nodeValue = val;

        return constantNode;
    }

    Node* Node_GetControlNode(const Node* returnNode) {
        if(returnNode->nodeType != NodeType::Return){
            LOG("Expect returnNode");
        }

        return returnNode->inputNodes.element[0];
    }

    Node* Node_GetExpresionNode(const Node* returnNode) {
        if(returnNode->nodeType != NodeType::Return){
            LOG("Expect returnNode");
        }

        return returnNode->inputNodes.element[1];
    }

    bool Node_IsControlFlow(const Node* node) {
        switch (node->nodeType) {
            case NodeType::Return: [[fallthrough]];
            case NodeType::Start:{
                return true;
            }
        }

        return false;
    }
}