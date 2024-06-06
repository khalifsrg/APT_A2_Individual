#include "Node.h"

Node::Node() : data(nullptr), next(nullptr), prev(nullptr) {}

Node::~Node() {
    // Assume data should be deleted by the class managing it.
}

Node::Node(void* data, Node* nextNode) : data(data), next(nextNode), prev(nullptr) {}
