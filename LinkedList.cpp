#include "LinkedList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

LinkedList::LinkedList() {
   head = nullptr;
   count = 0;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while(current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
     head = nullptr;
}

/// @brief insertNode function to insert the text file data into the linkedList
/// @param newNode 
void LinkedList::insertNode(Node* newNode) {
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

/// @brief Store head, get head to access linked list from other classes or functions
/// @return head
Node* LinkedList::getHead() const {
    return head;
}

/// @brief deleteNode function to remove the item from the LinkedList
/// @param id 
void LinkedList::deleteNode(const std::string& id, bool toggle) {
    if (head == nullptr) {
        std::cout << "The List is Empty" << std::endl;
        return;
    }

    if (static_cast<FoodItem*>(head->data)->id == id) {
        Node* temp = head;
        head = head->next;
        std::string name = static_cast<FoodItem*>(temp->data)->name; // Save the name
        std::string description = static_cast<FoodItem*>(temp->data)->description; // Save the description
        delete temp;
        count--;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && static_cast<FoodItem*>(current->data)->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Node with ID " << id << " not found." << std::endl;
        return;
    } 
    std::string name = static_cast<FoodItem*>(current->data)->name; // Save the name
    std::string description = static_cast<FoodItem*>(current->data)->description; // Save the description
    previous->next = current->next;
    delete current;
    count--;
        std::cout << "\"" << id << " - " << name << " - "<< description << "\" has been removed from the system." << std::endl;

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

/// @brief Adds the food item to the LinkedList through the inputted name, des, price while also assigning an ID
/// @param name 
/// @param desc 
/// @param price 
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
