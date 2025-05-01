// Military.cpp
#include "Stronghold.h"

Military::Military()
{
    soldiers = 0;
    training = 1;
    morale = 50;
    equipment = 1;
    cost = 0;
}

Military::Military(int initialSoldiers)
{
    soldiers = initialSoldiers;
    training = 1;
    morale = 50;
    equipment = 1;
    cost = soldiers * 2;
}

int Military::getSoldiers() const
{
    return soldiers;
}

int Military::getTraining() const
{
    return training;
}

int Military::getMorale() const
{
    return morale;
}

int Military::getEquipment() const
{
    return equipment;
}

int Military::getCost() const
{
    return cost;
}

void Military::recruit(int count)
{
    if (count > 0)
    {
        if (soldiers > 0 && count > soldiers / 10)
        {
            training = (training * 9) / 10;
        }
        soldiers += count;
        cost = soldiers * 2;
    }
}

void Military::train(int level)
{
    training += level;

    if (training < 1)
    {
        training = 1;
    }
    else if (training > 10)
    {
        training = 10;
    }

    morale += level * 2;
    if (morale > 100)
    {
        morale = 100;
    }
}

void Military::changeMorale(int change)
{
    morale += change;

    if (morale < 0)
    {
        morale = 0;
    }
    else if (morale > 100)
    {
        morale = 100;
    }
}

void Military::setSoldiers(int count)
{
    soldiers = count;
    if (soldiers < 0)
    {
        soldiers = 0;
    }
    cost = soldiers * 2;
}

void Military::equip(int level)
{
    equipment += level;

    if (equipment < 1)
    {
        equipment = 1;
    }
    else if (equipment > 10)
    {
        equipment = 10;
    }

    morale += level * 3;
    if (morale > 100)
    {
        morale = 100;
    }
}

int Military::calculateStrength() const
{
    if (soldiers == 0)
    {
        return 0;
    }

    int baseStrength = soldiers * 10;

    double trainingModifier = training / 5.0;
    double moraleModifier = morale / 100.0;
    double equipmentModifier = equipment / 5.0;

    double finalStrength = baseStrength * trainingModifier * moraleModifier * equipmentModifier;

    return finalStrength;
}

void Military::paySoldiers(int gold)
{
    int expectedPay = soldiers * 2;

    // Calculate the percentage of expected pay that was received
    double payPercentage = (expectedPay > 0) ? static_cast<double>(gold) / expectedPay : 0;

    if (payPercentage >= 1.0)
    {
        // Full pay or better, morale improves
        changeMorale(5);
    }
    else if (payPercentage >= 0.75)
    {
        // Decent pay, morale slightly improves
        changeMorale(2);
    }
    else if (payPercentage >= 0.5)
    {
        // Half pay, morale slightly decreases
        changeMorale(-2);
    }
    else if (payPercentage >= 0.25)
    {
        // Quarter pay, morale decreases
        changeMorale(-5);
    }
    else
    {
        changeMorale(-10);
    }

    // If morale is very low, some soldiers may desert
    if (morale < 20)
    {
        int deserters = soldiers / 10;
        soldiers -= deserters;

        if (soldiers < 0)
        {
            soldiers = 0;
        }

        cost = soldiers * 2;
    }
}

void Military::displayStatus() const
{
    cout << "Soldiers: " << soldiers << "\n"
         << "Training: " << training << "/10\n"
         << "Equipment: " << equipment << "/10\n"
         << "Morale: " << morale << "%\n"
         << "Upkeep: " << cost << " gold/turn\n";
}