#ifndef PURCHASE_H
#define PURCHASE_H

#include "LinkedList.h"
#include "Coin.h"

class Purchase
{
public:
    // Function is responsible for the entire transaction, from purchasing to change and receiving the coins/money.
    void purchaseMeal(LinkedList& foodList, LinkedList& coinList, bool toggle);

    // Checks whether money given is valid, and if it is a valid currency.
    bool isValidDenomination(int value);

    // Calculate how much change is given
    void calculateChange(LinkedList& coinList, double cost);

    // Is there enough coins to be given back as change? Checks that option.
    bool canGiveChange(LinkedList& coinList, int amount);

    // Remove coins from balance
    void subtractCoins(LinkedList& coinList, int amount);

    // Refund and give money back to customer.
    void refundMoney(LinkedList &coinList, int refundCents);

    // Receiving payment and add the total to the balance.
    void addCoins(LinkedList& coinList, int amount);
};

#endif // PURCHASE_H