#include <iostream>
#include "DisplayList.h"
#include <iomanip>
#include <stack>
#include "Coin.h"
// Constants for padding
const int PADDING_ID = 5;
const int PADDING_LENGTH = 5;
const int PADDING_MAX = 50;
const int PADDING_DENOM = 5;
const int PADDING_QUANTITY = 9;
const int PADDING_VALUE = 6;

/// @brief Display the meal options through the food items that are stored in the LinkedList "foodList"
/// @param foodList 
void DisplayList::displayMealOptions(LinkedList& foodList, bool toggle) {
    
    if (toggle == false) {
        //Code Display Meal options with input.
        Node* current = foodList.getHead(); // Get the head of the foodList
        if (!current) {
            std::cout << "No food items available." << std::endl;
            return;
        }
        // Space for better readability.
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Food Menu" << std::endl;
        std::cout << "----------" << std::endl;
        // Print the table header
        std::cout << std::setw(PADDING_ID) << std::left << "ID" << LINE; //ID is left-aligned with width of 6 chars
        std::cout << std::setw(PADDING_MAX) << std::left << " Name" << LINE; //Length is left-aligned with width of 51 chars
        std::cout << std::setw(PADDING_LENGTH) << std::left << "Length" << std::endl; //Length is left-aligned with width of 5 chars

        std::cout << "---------------------------------------------------------------------" << std::endl;

        // Iterate through the foodList and display details of each FoodItem
        while (current != nullptr) {
        // Dereference the data pointer to access the FoodItem
        FoodItem* currentItem = static_cast<FoodItem*>(current->data);
        
        // Print the details of the FoodItem with manual padding
        std::cout << currentItem->id << LINE
                  << currentItem->name.substr(0, 45); // Limiting the name to 45 characters
        for (int i = 0; i < PADDING_MAX - static_cast<int>(currentItem->name.length()); ++i) {
            std::cout << " "; // Padding spaces to make the total width 50 characters
        }
        std::cout << LINE;
        std::cout << std::fixed << std::setprecision(2) << DOLLARSIGN << currentItem->price.dollars << '.';
        std::cout << std::setw(2) << std::setfill(' ') << currentItem->price.cents << std::endl; 
        
        // Move to the next node
        current = current->next;
    }
     std::cout << std::endl;

    } else {
        std::cout << "Unable to display meal options." << std::endl;
    }
    
}

/// @brief Display the balance that is calculated through the quantity of the coins and value stored in the LinkedList "coinList"
/// @param coinList 
void DisplayList::displayBalance(LinkedList& coinList) {
    // Code to display balance, set to zero to avoid stacking last
    totalBalance = 0;
    std::cout << std::endl;

    std::cout << "Balance Summary" << std::endl;
    std::cout << std::setw(PADDING_DENOM) << std::left << "Denom" << " " << LINE << " ";
    std::cout << std::setw(PADDING_QUANTITY) << std::left << "Quantity" << " " << LINE << " " ;
    std::cout << std::setw(PADDING_VALUE + 2) << std::left << "Value" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // Stack to store pointers to nodes in reverse order
    std::stack<Node*> nodeStack;

    // Traverse the linked list and push node pointers onto the stack
    Node* current = coinList.getHead();
    while (current != nullptr) {
        nodeStack.push(current);
        current = current->next;
    }

    // Pop elements from the stack and print them to achieve reverse order
    while (!nodeStack.empty()) {
        current = nodeStack.top();
        nodeStack.pop();

        Coin* currentCoin = static_cast<Coin*>(current->data);
        double value = currentCoin->denom * currentCoin->count / 100.0; // Convert denomination to dollars
        std::cout << std::setw(PADDING_DENOM) << std::left << std::left <<currentCoin->denom << " " << LINE << " "; // Denomination
        std::cout << std::setw(PADDING_QUANTITY) << std::fixed << currentCoin->count << " " << LINE; // Quantity
        std::cout << DOLLARSIGN << std::setw(PADDING_VALUE) << std::fixed << std::setprecision(2) << std::right << value << std::endl; // Value
        // Add value of coin to our balance per iteration
        totalBalance += value;


    }

    std::cout << "------------------------------" << std::endl;

    // Calculate and print total balance (dummy value for demonstration)
std::cout << std::setw(PADDING_VALUE + PADDING_QUANTITY + PADDING_VALUE) << std::fixed << std::setprecision(2) << std::right << DOLLARSIGN << totalBalance << std::endl; // Balance
}




