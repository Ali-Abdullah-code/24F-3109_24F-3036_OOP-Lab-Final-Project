// Leadership.cpp
#include "Stronghold.h"

Leadership::Leadership() : currentRuler("Unknown Ruler"), popularity(50), leadershipAbility(50), corruptionLevel(0)
{
    srand(time(0)); // Seed for random number generation
}

Leadership::Leadership(string initialRuler) : currentRuler(initialRuler), popularity(50), leadershipAbility(50), corruptionLevel(0)
{
    srand(time(0)); // Seed for random number generation
}

string Leadership::getCurrentRuler() const
{
    return currentRuler;
}

int Leadership::getPopularity() const
{
    return popularity;
}

int Leadership::getLeadershipAbility() const
{
    return leadershipAbility;
}

int Leadership::getCorruptionLevel() const
{
    return corruptionLevel;
}

void Leadership::setRuler(string ruler)
{
    currentRuler = ruler;
    popularity = 50 + (rand() % 21) - 10; // 40-60 initial popularity
    leadershipAbility = 3 + (rand() % 5); // 3-7 leadership ability
    corruptionLevel = rand() % 20;        // 0-19 corruption level

    // Keep all attributes within bounds
    if (popularity < 0)
    {
        popularity = 0;
    }
    else if (popularity > 100)
    {
        popularity = 100;
    }

    if (leadershipAbility < 1)
    {
        leadershipAbility = 1;
    }
    else if (leadershipAbility > 10)
    {
        leadershipAbility = 10;
    }

    if (corruptionLevel < 0)
    {
        corruptionLevel = 0;
    }
    else if (corruptionLevel > 100)
    {
        corruptionLevel = 100;
    }
}

void Leadership::changePopularity(int change)
{
    popularity += change;
    if (popularity > 100)
    {
        popularity = 100;
    }
    if (popularity < 0)
    {
        popularity = 0;
    }
}

void Leadership::changeLeadershipAbility(int change)
{
    leadershipAbility += change;
    if (leadershipAbility > 100)
    {
        leadershipAbility = 100;
    }
    if (leadershipAbility < 0)
    {
        leadershipAbility = 0;
    }
}

void Leadership::changeCorruptionLevel(int change)
{
    corruptionLevel += change;
    if (corruptionLevel > 100)
    {
        corruptionLevel = 100;
    }
    if (corruptionLevel < 0)
    {
        corruptionLevel = 0;
    }
    // High corruption reduces popularity
    if (corruptionLevel > 50)
    {
        changePopularity(-2);
    }

    if (change != 0)
    {
        cout << "Ruler corruption " << (change > 0 ? "increased" : "decreased")
             << " by " << abs(change) << " to " << corruptionLevel << "%.\n";
    }
}

bool Leadership::checkForCoup() const
{
    if (popularity < 40 && corruptionLevel > 20)
    {
        return (rand() % 100) < (corruptionLevel - 20);
    }
    return false;
}

void Leadership::handleElection()
{
    if (rand() % 100 < 30)
    {
        popularity += 10;
    }
    else
    {
        popularity -= 10;
    }

    //  Elections are influenced by popularity
    // The current ruler has an advantage if popular, disadvantage if unpopular

    // Calculate election chance:
    // At 100 popularity, 90% chance to win
    // At 0 popularity, 10% chance to win
    int reelectionChance = 10 + (popularity * 0.8);

    // Random roll to determine election outcome
    int roll = rand() % 100;

    if (roll >= reelectionChance)
    {
        // Ruler loses election, new ruler takes over
        string oldRuler = currentRuler;

        // Simple names for new rulers
        string possibleRulers[] = {"Alexander", "Isabella", "Marcus", "Victoria", "William", "Catherine", "Henry", "Elizabeth", "Richard", "Mary"};

        // Pick a random new ruler
        std::string newRuler = possibleRulers[rand() % 10];

        // Ensure the new ruler is different
        while (newRuler == oldRuler)
        {
            newRuler = possibleRulers[rand() % 10];
        }

        // Set the new ruler
        setRuler(newRuler);
    }
    else
    {
        
        changeLeadershipAbility(1);

        // Popularity boost from winning
        changePopularity(10);

        // Slight increase in corruption
        changeCorruptionLevel(5);
    }
}