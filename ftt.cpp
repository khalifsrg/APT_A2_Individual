#include <iostream>
#include <limits> 
#include "Coin.h"
#include "LinkedList.h"
#include "DisplayList.h"
#include "Purchase.h"
#include "Help.h"
#include <fstream>
#include <sstream>

bool toggle = false;

void displayMainMenu(bool adminCheck, bool& toggle);
void run(bool isAdmin);
void loadFoodsData(const std::string& filename, LinkedList& foodList);
void loadCoinsData(const std::string& filename, LinkedList& coinList);
void saveAndExit(const std::string& foodsFilename, const std::string& coinsFilename, LinkedList& foodList, LinkedList& coinList);
void addFood(LinkedList& foodList, bool& toggle);
void removeFood(LinkedList& foodList, bool& toggle);
void purchaseMeal(LinkedList& foodList, LinkedList& coinList, bool& toggle);

/// @brief Main Function 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char **argv)
{
    bool isAdmin = true; // Assuming the user is an administrator by default
    run(isAdmin);
    EXIT_SUCCESS;
}


/// @brief Function to check that the user is an admin, foodlist and coin list we have imported
/// @param adminCheck 
/// @param foodList 
/// @param coinList 

/// @brief Run the program for the main function
/// @param adminCheck 
void run(bool adminCheck) {
    // Create our linked lists.
    LinkedList foodList;
    LinkedList coinList;

    // Load our data
    loadFoodsData("foods.dat", foodList); 
    loadCoinsData("coins.dat", coinList); 

    bool toggle = false; // Define and initialize toggle
    DisplayList displayList; // Create an instance of the DisplayList class
    Purchase purchase; // Create an instance of the Purchase class.

    // Loop until the user chooses to exit
    while (true) {
        std::string choice;
        displayMainMenu(adminCheck, toggle); // Pass both arguments to displayMainMenu

        std::cout << "Select your option (1-8): ";
        std::getline(std::cin, choice);

        if (choice == "help" && toggle) {
            DisplayHelp help;
            help.displayHelpMain();
        }

        // Handle the user's choice
        if (choice == "1") {
            // Ask the user if they want to traverse the list forwards or backwards if toggle is true
            if (toggle) {
                // Enable doubly linked list functionality
                foodList.setDoublyLinked(true);
                
                std::string traversalChoice;
                std::cout << "Do you want to display the menu forwards or backwards? (f/b): ";
                std::getline(std::cin, traversalChoice);

                if (traversalChoice == "f") {
                    std::cout << "Displaying forward:" << std::endl;
                    foodList.displayForward();
                } else if (traversalChoice == "b") {
                    std::cout << "Displaying backward:" << std::endl;
                    foodList.displayBackward();
                } else {
                    std::cout << "Invalid choice. Displaying forward by default:" << std::endl;
                    foodList.displayForward();
                }
            } else {
                // Display food options that are being sold.
                displayList.displayMealOptions(foodList, toggle);
            }
            std::cout << "Press enter to continue: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Set stream to max and clears input buffer
        } else if (choice == "2") {
            // Purchase a meal
            purchase.purchaseMeal(foodList, coinList, toggle); 
        } else if (choice == "3") {
            // Save and exit program, saving files.
            saveAndExit("foods.dat", "coins.dat", foodList, coinList); // Save to a different file to compare original and new one
            return;  // Exit the program after saving
        } else if (choice == "4") {
            // Safety check that user is an admin before allowing to run admin menu.
            if (adminCheck) {
                addFood(foodList, toggle);
            } else {
                std::cout << PERMISSION_DENIED_MSG << std::endl;
            }
        } else if (choice == "5") {
            // Remove a food item 
            if (adminCheck) {
                removeFood(foodList, toggle);
            } else {
                std::cout << PERMISSION_DENIED_MSG << std::endl;
            }
        } else if (choice == "6") {
            // Display balance of your coins from coinList.
            if (adminCheck) {
               displayList.displayBalance(coinList);
            } else {
                std::cout << PERMISSION_DENIED_MSG << std::endl;
            }
        } else if (choice == "7") {
            // Exit and reset entire program, deallocate
            return;
        } else if (choice == "8") {
            // Toggle enhancements
            if (adminCheck) { // Ensure this is only accessible to admin
                toggle = !toggle;
                std::cout << (toggle ? "Enhancements have been turned on." : "Enhancements have been turned off.") << std::endl;
            } else {
                std::cout << PERMISSION_DENIED_MSG << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter a number between 1 and 8." << std::endl;
        }
    }
}

/// @brief Display menu to the user.
/// @param adminCheck 
/// @param toggle 
void displayMainMenu(bool adminCheck, bool& toggle) {
    std::cout << "Main Menu:" << std::endl;
    std::cout << "    1. Display Meal Options" << std::endl;
    std::cout << "    2. Purchase Meal" << std::endl;
    std::cout << "    3. Save and Exit" << std::endl;
    
    if (adminCheck) { // Must be admin to view the admin options.
        std::cout << "Administrator-Only Menu:" << std::endl;
        std::cout << "    4. Add Food" << std::endl;
        std::cout << "    5. Remove Food" << std::endl;
        std::cout << "    6. Display Balance" << std::endl;
        std::cout << "    7. Abort Program" << std::endl;
        std::cout << "    8. Toggle Enhancements" << std::endl;
    }
}


/// @brief Loading the foods.dat file and inserting the nodes into a linked list with param foodList
/// @param filename 
/// @param foodList 
void loadFoodsData(const std::string& filename, LinkedList& foodList) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, desc;
        Price price;

        if (std::getline(iss, id, '|') &&
            std::getline(iss, name, '|') &&
            std::getline(iss, desc, '|') &&
            (iss >> price)) {
            FoodItem* newItem = new FoodItem{id, name, desc, price, DEFAULT_FOOD_STOCK_LEVEL};
            Node* newNode = new Node{newItem, nullptr};
            foodList.insertNode(newNode);

        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}

/// @brief Loading the coins.dat file and inserting the nodes into a linked list with param coinList
/// @param filename 
/// @param coinList 
void loadCoinsData(const std::string& filename, LinkedList& coinList) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string denomStr, countStr;
        if (std::getline(iss, denomStr, ',') && std::getline(iss, countStr)) {
            int denomValue = std::stoi(denomStr);
            unsigned count = std::stoul(countStr);

            Coin* newCoin = new Coin{static_cast<Denomination>(denomValue), count};
            Node* newNode = new Node{newCoin, nullptr};
            coinList.insertNode(newNode);
            
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

}

///@brief Save food and coin data to respective files.
///@param foodsFilename The filename to save food data.
///@param coinsFilename The filename to save coin data.
///@param foodList The linked list containing food items.
///@param coinList The linked list containing coins
void saveAndExit(const std::string& foodsFilename, const std::string& coinsFilename, LinkedList& foodList, LinkedList& coinList) {
    std::ofstream foodFile(foodsFilename);
    if (foodFile.is_open()) {
        Node* currentFood = foodList.getHead();
        while (currentFood != nullptr) {
            FoodItem* currentItem = static_cast<FoodItem*>(currentFood->data);
            // Write food item details to file
            foodFile << currentItem->id << '|' << currentItem->name << '|' << currentItem->description << '|' << currentItem->price.dollars << '.' << currentItem->price.cents << '\n';
            currentFood = currentFood->next;
        }
        std::cout << foodsFilename << " has been saved to the system" << std::endl;
        foodFile.close();
    } else {
        std::cerr << "Error: Unable to open food file for writing." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream coinFile(coinsFilename);
    if (coinFile.is_open()) {
    Node* currentCoin = coinList.getHead();
    while (currentCoin != nullptr) {
        Coin* currentCoinData = static_cast<Coin*>(currentCoin->data);
        // Write coin denomination and count to file
        coinFile << static_cast<int>(currentCoinData->denom) << ',' << currentCoinData->count << '\n';
        currentCoin = currentCoin->next;
    }
    std::cout << coinsFilename << " has been saved to the system" << std::endl;
    coinFile.close();
} else {
        std::cerr << "Error: Unable to open coin file for writing." << std::endl;
        exit(EXIT_FAILURE);
    }
}

/// @brief Adds food to the foodList LL through user input and then calling the addFoodItem function
/// @param foodList 
/// @param toggle 
void addFood(LinkedList& foodList, bool& toggle) {
    std::string name, description;
    int dollars, cents;

    while (true) {
        std::cout << "Enter the item name: ";
        std::getline(std::cin >> std::ws, name);

        if (toggle && name == "help") {
            DisplayHelp help;
            help.displayHelpAdd();
            continue; // Continue to prompt again after displaying help
        }

        break; // Exit the loop if name is not 'help'
    }

    std::cout << "Enter the item description: ";
    std::getline(std::cin, description);

    std::cout << "Enter the price dollars: ";
    std::cin >> dollars;
    std::cout << "Enter the price cents: ";
    std::cin >> cents;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Price price{static_cast<unsigned int>(dollars), static_cast<unsigned int>(cents)};
    foodList.addFoodItem(name, description, price, toggle);

    std::cout << "Food item added successfully!" << std::endl;
}

/// @brief Remove food from foodList, by getting the ID of the food item.
/// @param foodList 
/// @param toggle 
void removeFood(LinkedList& foodList, bool& toggle) {
    std::string id;

    while (true) {
        std::cout << "Enter the ID of the food item to delete: ";
        std::getline(std::cin >> std::ws, id);

        if (toggle && id == "help") {
            DisplayHelp help;
            help.displayHelpRemove();
            continue; // Continue to prompt again after displaying help
        }

        break; // Exit the loop if id is not 'help'
    }

    foodList.deleteNode(id, toggle);
}






