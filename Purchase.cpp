#include <iostream>
#include <limits>
#include "Purchase.h"
#include <vector>

/// @brief Function responsible for meal purchase, receiving money and refunding change to the customer.
/// @param foodList 
/// @param coinList 
void Purchase::purchaseMeal(LinkedList& foodList, LinkedList& coinList) {
    std::string foodId;
    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Please enter the ID of the food you wish to purchase: ";


    // Reads user's input and check's if it is a valid food ID or available.
    std::cin >> foodId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    FoodItem* selectedFood = foodList.findFoodItemByID(foodId);
    if (selectedFood == nullptr || selectedFood->on_hand <= 0) {
        std::cout << "Error: Food item not found or out of stock." << std::endl;
        return;
    }

    // Only space, ctrl-D or a valid denom is valid at this stage of the program
    std::cout << "You have selected \"" << selectedFood->name << " - " << selectedFood->description << "\". This will cost you $"
              << selectedFood->price.dollars << '.' << (selectedFood->price.cents < 10 ? "0" : "") << selectedFood->price.cents << std::endl;
    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;
    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;

    // Calculate amount owed, with conversion
    int totalAmount = selectedFood->price.dollars * 100 + selectedFood->price.cents;
    // Variable to store amount owing.
    int remainingAmount = totalAmount;
    // Variable to keep track of total amount paid so far
    int totalPaid = 0;

    std::vector<int> userPayment;
    

    // Checks whether amount is fully paid off or not.
    while (remainingAmount > 0) {
        std::cout << "You still need to give us $" << remainingAmount / 100 << '.'
                  << (remainingAmount % 100 < 10 ? "0" : "") << remainingAmount % 100 << ": ";
        std::string input;
        std::getline(std::cin, input);

         // Check for EOF (Ctrl+D)
        if (std::cin.eof()) {
            std::cin.clear(); // Clear flag
            std::cout << "\nPurchase cancelled. Refunding money." << std::endl;
            for (int payment : userPayment) {
                refundMoney(coinList, payment / 100.0);
            }
            return;
        }

        
        // Cancellation of purchase
        if (input.empty() || std::cin.eof()) {
            std::cout << "Purchase cancelled. Refunding money." << std::endl;
        for(int payment : userPayment){
                refundMoney(coinList, payment/100.0);
        }
            return;
        }
        // Checks if payment is a valid input.
        int payment;
        try {
            payment = std::stoi(input);
        } catch (...) {
            std::cout << "Error: invalid input. Please enter a valid amount in cents." << std::endl;
            continue;
        }

        if (!isValidDenomination(payment)) {
            std::cout << "Error: invalid denomination encountered." << std::endl;
            continue;
        }
        // If payment is valid, will add it towards the amount the total amount user has paid.
        totalPaid += payment;
        // Will also track how much is remaining.
        remainingAmount -= payment;


        // If remaining amount is 0 or less, and there is not change, then a full refund will occur.
        if (remainingAmount <= 0) {
            int change = -remainingAmount;
            if (change > 0 && !canGiveChange(coinList, change)) {
                std::cout << "Sorry, we cannot provide change for this purchase. Purchase canceled." << std::endl;
                refundMoney(coinList, totalPaid);
                return;
            }

            // Successful payment, money is added to coins, and change is given to customer.
            std::cout << "Thank you for your purchase." << std::endl;
            selectedFood->on_hand--; // Decrement stock count
            addCoins(coinList, totalPaid); // Add the payment to the balance
            if (change > 0) {
                refundMoney(coinList, change);
            }
            return;
        }
    }
}
/// @brief Check for valid denoms. Ensure valid money.
/// @param value 
/// @return 
bool Purchase::isValidDenomination(int value) {
    switch (value) {
        case Denomination::FIVE_CENTS:
        case Denomination::TEN_CENTS:
        case Denomination::TWENTY_CENTS:
        case Denomination::FIFTY_CENTS:
        case Denomination::ONE_DOLLAR:
        case Denomination::TWO_DOLLARS:
        case Denomination::FIVE_DOLLARS:
        case Denomination::TEN_DOLLARS:
        case Denomination::TWENTY_DOLLARS:
        case Denomination::FIFTY_DOLLARS:
            return true;
        default:
            return false;
    }
}

/// @brief Calculate the change for the user after they purchase a foodItem and deduct the amount from the balance
/// @param coinList 
/// @param amount 
/// @return 
bool Purchase::canGiveChange(LinkedList& coinList, int amount) {
    int remainingAmount = amount;
    Node* current = coinList.getHead();

    while (current != nullptr && remainingAmount > 0) {
        Coin* currentCoin = static_cast<Coin*>(current->data);
        int coinsToUse = std::min(remainingAmount / currentCoin->denom, (int)currentCoin->count);
        remainingAmount -= coinsToUse * currentCoin->denom;
        current = current->next;
    }

    return remainingAmount == 0;
}

/// @brief Add coins to the coinList LinkedList for the user's total balance to use
/// @param coinList 
/// @param amount 
void Purchase::addCoins(LinkedList& coinList, int amount) {
    int remainingAmount = amount;
    Node* current = coinList.getHead();

    while (current != nullptr && remainingAmount > 0) {
        Coin* currentCoin = static_cast<Coin*>(current->data);
        int coinsToAdd = remainingAmount / currentCoin->denom;
        currentCoin->count += coinsToAdd;
        remainingAmount -= coinsToAdd * currentCoin->denom;
        current = current->next;
    }
}

/// @brief refund the user's money based on their purchase
/// @param coinList 
/// @param refundCents 
void Purchase::refundMoney(LinkedList& coinList, int refundCents) {
    std::vector<int> refundedDenominations;
    std::vector<int> refundedCounts;

    int tempRefundCents = refundCents;
    // first pass: check if enough coins are available
    Node* current = coinList.getHead();
    while (current != nullptr && tempRefundCents > 0) {
        Coin* currentCoin = static_cast<Coin*>(current->data);

        int refundableCoins = std::min(tempRefundCents / currentCoin->denom, (int)currentCoin->count);
        tempRefundCents -= refundableCoins * currentCoin->denom;

        current = current->next;
    }

    if (tempRefundCents > 0) {
        std::cout << "Error: Not enough coins for refund." << std::endl;
        return;
    }

    current = coinList.getHead();
    while (current != nullptr && refundCents > 0) {
        Coin* currentCoin = static_cast<Coin*>(current->data);

        int refundableCoins = std::min(refundCents / currentCoin->denom, (int)currentCoin->count);
        refundCents -= refundableCoins * currentCoin->denom;
        currentCoin->count -= refundableCoins;

        if (refundableCoins > 0) {
            refundedDenominations.push_back(currentCoin->denom);
            refundedCounts.push_back(refundableCoins);
        }

        current = current->next;
    }

    std::cout << "Your change is: ";
    for (size_t i = 0; i < refundedDenominations.size(); i++) {
        for (int j = 0; j < refundedCounts[i]; j++) {
            if (refundedDenominations[i] >= 100) {
                std::cout << "$" << refundedDenominations[i] / 100 << " ";
            } else {
                std::cout << refundedDenominations[i] << "c ";
            }
        }
    }
    std::cout << std::endl;
}