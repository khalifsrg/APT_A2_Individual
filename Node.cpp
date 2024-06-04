#include "Node.h"

Node::Node() {
    data = nullptr; // Initialize data pointer to nullptr
    next = nullptr;
}


Node::~Node() {
    //delete data; 
}

Node::Node(void* item, Node* nextNode) {
    data = item;       // Initialize data pointer to the provided item
    next = nextNode;   // Initialize next pointer to the provided nextNode
}
 


