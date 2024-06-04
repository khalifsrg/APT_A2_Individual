#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    
    Node* getHead() const; // Declaration of the getHead() method, returns head of linked list.
    // Responsible for inserting a new food item into node.
    void insertNode(Node* newNode);

    // Delete a food item from the list, checks id to find the specific item to be removed.
    void deleteNode(const std::string& id);

    // Basic method for finding food by ID.
    FoodItem* findFoodItemByID(const std::string& id);

    // Collect variables for new food item to be added, name, descripton and price. Then prints a message that it is successful.
    void addFoodItem(const std::string& name, const std::string& desc, const Price& price);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H
