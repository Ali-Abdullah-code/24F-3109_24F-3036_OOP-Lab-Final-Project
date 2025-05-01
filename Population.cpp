// Population.cpp
#include "Stronghold.h"

Population::Population() : totalPopulation(0), growthRate(5), deathRate(2), happiness(50), health(75) {}

Population::Population(int initialPopulation) : totalPopulation(initialPopulation), growthRate(5), deathRate(2), happiness(50), health(75) {}

int Population::getTotal() const
{
    return totalPopulation;
}

int Population::getGrowthRate() const
{
    return growthRate;
}

int Population::getHappiness() const
{
    return happiness;
}

int Population::getHealth() const
{
    return health;
}

void Population::setPopulation(int newPopulation)
{
    totalPopulation = newPopulation;
    if (totalPopulation < 0)
    {
        totalPopulation = 0;
    }
}

void Population::setGrowthRate(int rate)
{
    growthRate = rate;
    if (growthRate < 0)
    {
        growthRate = 0;
    }
}

void Population::setDeathRate(int rate)
{
    deathRate = rate;
    if (deathRate < 0)
    {
        deathRate = 0;
    }
}

void Population::updatePopulation()
{
    // Adjust death rate based on health
    int adjustedDeathRate = deathRate + (health < 50 ? (50 - health) / 10 : 0); // +1% death rate for every 10% health below 50
    int change = (totalPopulation * (growthRate - adjustedDeathRate)) / 100;
    totalPopulation += change;
    if (totalPopulation < 0)
    {
        totalPopulation = 0;
    }
    if (change != 0)
    {
        cout << "Population changed by " << change << " (Growth: " << growthRate << "%, Death: " << adjustedDeathRate << "%).\n";
    }
}

void Population::changeHappiness(int change)
{
    happiness += change;
    if (happiness > 100)
    {
        happiness = 100;
    }
    if (happiness < 0)
    {
        happiness = 0;
    }
}

void Population::changeHealth(int change)
{
    health += change;
    if (health > 100)
    {
        health = 100;
    }
    if (health < 0)
    {
        health = 0;
    }
}

bool Population::checkForRevolt() const
{
    if (happiness < 20)
    {
        // The lower the happiness, the higher the chance of revolt
        int revoltChance = 100 - (happiness * 5);

        // Random number between 0 and 99
        int roll = rand() % 100;

        return roll < revoltChance;
    }

    return false;
}