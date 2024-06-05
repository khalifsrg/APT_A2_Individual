#ifndef DISPLAYLIST_H
#define DISPLAYLIST_H
#include "LinkedList.h"
#include "Coin.h"
#define PERMISSION_DENIED_MSG "You do not have permission to perform this action."
#define LINE "|"
#define DOLLARSIGN "$ "




class DisplayList
{
public:

/**
 * Manages the display of food items stored in a linked list.
* Provides functionality to iterate over the list and print
* details of each food item, including ID, name, description,
* and price. Also displays balance, denom sorted from lowest to highest
 **/
    // Update total balance
    double totalBalance;
    void displayMealOptions(LinkedList& foodList, bool toggle);

    /** Displays and counts notes/coins that are alligned and sorted from lowest to highest value
    *Include total balance at the end. 
    **/
    void displayBalance(LinkedList& coinList);



  
};

#endif  // DISPLAYLIST_H