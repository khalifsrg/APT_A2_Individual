#include "LinkedList.h"
#include "Node.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr), tail(nullptr), doublyLinked(false), count(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

Node* LinkedList::getHead() const {
    return head;
}

void LinkedList::insertNode(Node* newNode) {
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        if (doublyLinked) {
            newNode->prev = tail;
        }
        tail = newNode;
    }
    count++;
}

void LinkedList::deleteNode(const std::string& name, bool toggle) {
    Node* current = head;
    while (current != nullptr) {
        FoodItem* item = static_cast<FoodItem*>(current->data);
        if (item->name == name) {  // Directly access the name member variable
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            delete current;
            count--;
            return;
        }
        current = current->next;
    }
}

void LinkedList::addFoodItem(const std::string& name, const std::string& desc, const Price& price, bool toggle) {
    std::ostringstream idStream;
    idStream << "F" << std::setw(4) << std::setfill('0') << (count + 1);
    std::string id = idStream.str();

    // Create new node and food item class pointers.
    FoodItem* newItem = new FoodItem{id, name, desc, price};
    Node* newNode = new Node{newItem, nullptr};
    // Call function to insert node.
    insertNode(newNode);
    // Message to confirm succesfully added
    std::cout << "This item \"" << name << " - " << desc << "\" has now been added to the food menu." << std::endl;
}

void LinkedList::setDoublyLinked(bool toggle) {
    doublyLinked = toggle;
}

void LinkedList::displayForward() const {
    Node* current = head;
    while (current != nullptr) {
        FoodItem* item = static_cast<FoodItem*>(current->data);
        std::cout << item->name << " ";  // Directly access the name member variable
        current = current->next;
    }
    std::cout << std::endl;
}

void LinkedList::displayBackward() const {
    if (!doublyLinked) {
        std::cout << "Doubly linked list functionality is disabled." << std::endl;
        return;
    }

    Node* current = tail;
    while (current != nullptr) {
        FoodItem* item = static_cast<FoodItem*>(current->data);
        std::cout << item->name << " ";  // Directly access the name member variable
        current = current->prev;
    }
    std::cout << std::endl;
}

/// @brief The LinkedList is iterated through to find the ID that the user wishes to modify
/// @param id 
/// @return 
FoodItem* LinkedList::findFoodItemByID(const std::string& id) {
    Node* current = head;
    while (current != nullptr) {
        FoodItem* foodItem = static_cast<FoodItem*>(current->data);
        if (foodItem->id == id) {
            return foodItem;
        }
        current = current->next;
    }
    return nullptr; 
}