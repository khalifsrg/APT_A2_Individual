#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <string>
#include <sstream>
#include <iomanip>

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    
    Node* getHead() const;

    void insertNode(Node* newNode);

    void deleteNode(const std::string& name, bool toggle);

    void addFoodItem(const std::string& name, const std::string& desc, const Price& price, bool toggle);

    void setDoublyLinked(bool toggle);

    FoodItem* findFoodItemByID(const std::string& id);
    
    void displayForward() const;
    void displayBackward() const;

private:
    Node* head;
    Node* tail;  // Add this line to keep track of the tail node
    bool doublyLinked;  // Add this line
    unsigned count;
};

#endif // LINKEDLIST_H
