#ifndef NODE_H
#define NODE_H

#include <memory>
#include <string> 
#include <iostream>
#include "Coin.h"


//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a food item name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a food item description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The possible default food stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_FOOD_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 9

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
class Price
{
public:
    // The dollar value, and the cents value for some price
    unsigned dollars, cents;

    // Overloading the >> operator for Price class
    friend std::istream& operator>>(std::istream& is, Price& price) {
        char dot;
        if (is >> price.dollars >> dot >> price.cents && dot == '.') {
            return is;
        } else {
            is.setstate(std::ios::failbit);
            return is;
        }
    }
};

/**
 * data structure to represent a food item within the system
 **/
class FoodItem
{
public:
    //the unique id for this food item
    std::string id;

    //the name of this food item
    std::string name;
    
    //the description of this food item   
    std::string description;
    
    //the price of this food item
    Price price;
    
    // how many of this food item do we have on hand? 
    unsigned on_hand;

    bool toggle;    
};

/**
 * the node that holds the data about a food item stored in memory
 **/
class Node {
public:
    Node();
    ~Node();
    Node(void* data, Node* nextNode);

    void* data;
    Node* next;
    Node* prev;  // Add this line for doubly-linked list
};

#endif // NODE_H