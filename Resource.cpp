// Resource.cpp
#include "Stronghold.h"

Resource::Resource() : name("Unknown"), amount(0), productionRate(0), consumptionRate(0) {}

Resource::Resource(std::string name, int amount, int productionRate, int consumptionRate) : name(name), amount(amount), productionRate(productionRate), consumptionRate(consumptionRate) {}

string Resource::getName() const
{
    return name;
}

int Resource::getAmount() const
{
    return amount;
}

int Resource::getProductionRate() const
{
    return productionRate;
}

int Resource::getConsumptionRate() const
{
    return consumptionRate;
}

void Resource::setAmount(int newAmount)
{
    amount = newAmount;
    if (amount < 0)
    {
        amount = 0;
    }
}

void Resource::produce()
{
    amount += productionRate;
}

void Resource::consume()
{
    amount -= consumptionRate;
    if (amount < 0)
    {
        amount = 0;
    }
}

bool Resource::consume(int amountToConsume)
{
    if (amount >= amountToConsume)
    {
        amount -= amountToConsume;
        return true;
    }
    return false;
}

void Resource::changeProductionRate(int change)
{
    productionRate += change;
    if (productionRate < 0)
    {
        productionRate = 0;
    }
}

void Resource::changeConsumptionRate(int change)
{
    consumptionRate += change;
    if (consumptionRate < 0)
    {
        consumptionRate = 0;
    }
}

void Resource::displayStatus() const
{
    cout << name << ": " << amount << " (Prod: " << productionRate << ", Cons: " << consumptionRate << ")\n";
}