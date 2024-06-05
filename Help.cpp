#include <iostream>
#include "Help.h"

DisplayHelp::DisplayHelp() {}

DisplayHelp::~DisplayHelp() {}

void DisplayHelp::displayHelpMain() {
    std::cout << "Program Functions: " << std::endl;
    std::cout << std::endl;
    std::cout << std::left << "Press \'1\' to display all meal options available." << std::endl;
    std::cout << std::left << "Press \'2\' to purchase a meal from the vending machine." << std::endl;
    std::cout << std::left << "Press \'3\' to save the actions within the program and exit the program." << std::endl;
    std::cout << std::endl;
    std::cout << "Admin functions:" << std::endl;
    std::cout << std::left << "Press \'4\' to add food to the vending machine." << std::endl;
    std::cout << std::left << "Press \'5\' to remove food from the vending machine." << std::endl;
    std::cout << std::left << "Press \'6\' to display the remaining balance and quantity of coins available within the system." << std::endl;
    std::cout << std::left << "Press \'7\' to abort the program without saving." << std::endl;
    std::cout << std::endl;
    std::cout << "Press \'enter\' to return to the main menu." << std::endl;
    std::cout << std::endl;
    std::cin.get();
}

void DisplayHelp::displayHelpPurchase() {
    std::cout << "Purchase Help: " << std::endl;
    std::cout << std::endl;
    std::cout << std::left << "1. To purchase the item you wish type in the ID of the item into the input bar." << std::endl;
    std::cout << std::left << "2. Enter the amount of money that you wish to pay off the remaining balance that the food item costs into the input bar." << std::endl;
    std::cout << std::endl;
    std::cout << "Press \'enter\' to return to the purchasing screen." << std::endl;
    std::cout << std::endl;
    std::cin.get();
}
void DisplayHelp::displayHelpAdd() {
    std::cout << "Add Food Item Help: " << std::endl;
    std::cout << std::endl;
    std::cout << std::left << "1. To add item to the Vending Machine, type the name of the item to add into the input bar" << std::endl;
    std::cout << std::left << "2. Then, type the description of the item into the input bar" << std::endl;
    std::cout << std::left << "3. Then, type the price of the item to add into the input bar" << std::endl;
    std::cout << std::endl;
    std::cout << "Press \'enter\' to return to the add item screen." << std::endl;
    std::cin.get();
}

void DisplayHelp::displayHelpRemove() {
    std::cout << "Remove Food Item Help: " << std::endl;
    std::cout << std::endl;
    std::cout << std::left << "1. To remove item to the Vending Machine, type ID of the item to remove into the input bar" << std::endl;
    std::cout << std::endl;
    std::cout << "Press \'enter\' to return to the remove item screen." << std::endl;
    std::cin.get();
}
