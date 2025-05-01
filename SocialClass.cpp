// SocialClass.cpp
#include "Stronghold.h"

SocialClass::SocialClass()
{
    name = "Unknown";
    population = 0;
    taxRate = 0;
    happiness = 50;
    productivity = 50;
}

SocialClass::SocialClass(string name, int population, int taxRate)
{
    this->name = name;
    this->population = population;
    this->taxRate = taxRate;
    happiness = 50;
    productivity = 50;
}

SocialClass::~SocialClass()
{
    // Destructor
}

string SocialClass::getName() const
{
    return name;
}

int SocialClass::getPopulation() const
{
    return population;
}

int SocialClass::getTaxRate() const
{
    return taxRate;
}

int SocialClass::getHappiness() const
{
    return happiness;
}

int SocialClass::getProductivity() const
{
    return productivity;
}

void SocialClass::setPopulation(int pop)
{
    population = pop;
    if (population < 0)
    {
        population = 0;
    }
}

void SocialClass::setTaxRate(int rate)
{
    taxRate = rate;
    if (taxRate < 0)
    {
        taxRate = 0;
    }
    else if (taxRate > 50)
    {
        taxRate = 50;
    }
    if (taxRate > 20)
    {
        changeHappiness(-5);
    }
    else if (taxRate < 10)
    {
        changeHappiness(5);
    }
}

void SocialClass::changeHappiness(int change)
{
    happiness += change;
    if (happiness < 0)
    {
        happiness = 0;
    }
    else if (happiness > 100)
    {
        happiness = 100;
    }
    updateProductivity();
}

void SocialClass::updateProductivity()
{
    if (happiness < 30)
    {
        productivity = 30;
    }
    else if (happiness < 50)
    {
        productivity = 50;
    }
    else if (happiness < 70)
    {
        productivity = 70;
    }
    else
    {
        productivity = 90;
    }
}

int SocialClass::generateTax() const
{
    int baseIncome = 0;
    if (name == "Peasants")
    {
        baseIncome = 1;
    }
    else if (name == "Merchants")
    {
        baseIncome = 5;
    }
    else if (name == "Nobles")
    {
        baseIncome = 10;
    }
    else
    {
        baseIncome = 2;
    }
    int totalIncome = population * baseIncome;
    totalIncome = (totalIncome * productivity) / 100;
    int taxCollected = (totalIncome * taxRate) / 100;
    return taxCollected;
}