// Kingdom.cpp
#include "Stronghold.h"

Kingdom::Kingdom()
{
    name = "Unnamed Kingdom";
    population = Population(1000);
    socialClasses = new SocialClass *[3];
    numSocialClasses = 3;
    socialClasses[0] = new Noble(50);
    socialClasses[1] = new Merchant(200);
    socialClasses[2] = new Peasant(750);

    military = Military(100);
    economy = Economy(1000);
    leadership = Leadership("Gryphonian Empire");
    bank = Bank(500);

    resources = new Resource[4];
    numResources = 4;
    resources[0] = Resource("Gold", 1000, 100, 50);
    resources[1] = Resource("Food", 5000, 500, 0);
    resources[2] = Resource("Stone", 2000, 200, 100);
    resources[3] = Resource("Wood", 3000, 300, 150);
}

Kingdom::Kingdom(string name)
{
    this->name = "Gryphonian Empire";
    population = Population(1000);
    socialClasses = new SocialClass *[3];
    numSocialClasses = 3;
    socialClasses[0] = new Noble(50);
    socialClasses[1] = new Merchant(200);
    socialClasses[2] = new Peasant(750);

    military = Military(100);
    economy = Economy(1000);
    leadership = Leadership(name);
    bank = Bank(500);

    resources = new Resource[4];
    numResources = 4;
    resources[0] = Resource("Gold", 1000, 100, 50);
    resources[1] = Resource("Food", 5000, 500, 0);
    resources[2] = Resource("Stone", 2000, 200, 100);
    resources[3] = Resource("Wood", 3000, 300, 150);
}

Kingdom::~Kingdom()
{
    for (int i = 0; i < numSocialClasses; i++)
    {
        delete socialClasses[i];
    }
    delete[] socialClasses;
    delete[] resources;
}

string Kingdom::getName() const
{
    return name;
}

Population &Kingdom::getPopulation()
{
    return population;
}

Military &Kingdom::getMilitary()
{
    return military;
}

Economy &Kingdom::getEconomy()
{
    return economy;
}

Leadership &Kingdom::getLeadership()
{
    return leadership;
}

Bank &Kingdom::getBank()
{
    return bank;
}

int Kingdom::getNumSocialClasses() const
{
    return numSocialClasses;
}

void Kingdom::addSocialClass(const SocialClass &newClass)
{
    SocialClass **temp = new SocialClass *[numSocialClasses + 1];
    for (int i = 0; i < numSocialClasses; i++)
    {
        temp[i] = socialClasses[i];
    }
    temp[numSocialClasses] = newClass.clone(); // Assuming a clone method
    for (int i = 0; i < numSocialClasses; i++)
    {
        delete socialClasses[i]; // Delete old objects
    }
    delete[] socialClasses;
    socialClasses = temp;
    numSocialClasses++;
}

SocialClass &Kingdom::getSocialClass(int index)
{
    if (index >= 0 && index < numSocialClasses)
    {
        return *socialClasses[index];
    }
    throw runtime_error("Invalid social class index");
}

void Kingdom::addResource(const Resource &newResource)
{
    Resource *temp = new Resource[numResources + 1];
    for (int i = 0; i < numResources; i++)
    {
        temp[i] = resources[i];
    }
    temp[numResources] = newResource;
    delete[] resources;
    resources = temp;
    numResources++;
}

Resource &Kingdom::getResource(int index)
{
    return resources[index];
}

Resource &Kingdom::getResource(const string &name)
{
    for (int i = 0; i < numResources; i++)
    {
        if (resources[i].getName() == name)
        {
            return resources[i];
        }
    }
    throw runtime_error("Resource not found");
}

void Kingdom::advanceTurn()
{
    cout << "\n--- Advancing to next turn for " << name << " ---\n";

    // Calculate dynamic food consumption based on population and military
    int totalPopulation = population.getTotal();
    int militarySize = military.getSoldiers();
    int foodConsumption = (totalPopulation / 2) + (militarySize / 2);
    getResource("Food").changeConsumptionRate(foodConsumption - getResource("Food").getConsumptionRate());

    // Check for food shortage
    Resource &food = getResource("Food");
    if (food.getAmount() < foodConsumption)
    {
        population.changeHealth(-10);
        cout << "WARNING: Food shortage! Population health declining.\n";
    }

    // Social classes consume resources
    int totalFoodConsumedByClasses = 0;
    int goldConsumedByNobles = 0;
    for (int i = 0; i < numSocialClasses; i++)
    {
        int foodToConsume = socialClasses[i]->getPopulation() / 2;
        totalFoodConsumedByClasses += socialClasses[i]->consume(&food, foodToConsume);
        if (socialClasses[i]->getName() == "Nobles")
        {
            Resource &gold = getResource("Gold");
            goldConsumedByNobles = socialClasses[i]->getPopulation() * 2;
            economy.setTreasury(economy.getTreasury() - goldConsumedByNobles);
            if (economy.getTreasury() < 0)
            {
                economy.setTreasury(0);
            }
        }
    }
    cout << "Social classes consumed " << totalFoodConsumedByClasses << " food.\n";
    if (goldConsumedByNobles > 0)
    {
        cout << "Nobles consumed " << goldConsumedByNobles << " gold for luxury.\n";
    }

    // Check for other resource shortages
    Resource &wood = getResource("Wood");
    if (wood.getAmount() < 50)
    {
        cout << "WARNING: Low wood reserves! Construction may be impacted.\n";
    }
    Resource &stone = getResource("Stone");
    if (stone.getAmount() < 50)
    {
        cout << "WARNING: Low stone reserves! Construction may be impacted.\n";
    }

    // Update population
    population.updatePopulation();

    // Update social classes and collect contributions
    int totalTaxes = 0;
    for (int i = 0; i < numSocialClasses; i++)
    {
        socialClasses[i]->update();
        totalTaxes += socialClasses[i]->generateTax();

        if (socialClasses[i]->getName() == "Peasants")
        {
            int foodProduced = static_cast<int>(socialClasses[i]->contribute());
            getResource("Food").setAmount(getResource("Food").getAmount() + foodProduced);
            cout << "Peasants produced " << foodProduced << " food.\n";
        }
        else if (socialClasses[i]->getName() == "Merchants")
        {
            int goldProduced = static_cast<int>(socialClasses[i]->contribute());
            economy.setTreasury(economy.getTreasury() + goldProduced);
            cout << "Merchants generated " << goldProduced << " gold.\n";
        }
        else if (socialClasses[i]->getName() == "Nobles")
        {
            int influence = static_cast<int>(socialClasses[i]->contribute());
            leadership.changePopularity(influence);
            military.changeMorale(influence);
            cout << "Nobles increased popularity and morale by " << influence << ".\n";
        }
    }

    leadership.changeCorruptionLevel(1); // Increase corruption level by 1 for each social class update
    // Update resources
    for (int i = 0; i < numResources; i++)
    {
        resources[i].produce();
        resources[i].consume();
    }

    // Collect taxes and check for corruption due to high taxes
    economy.collectTaxes(totalTaxes);
    if (economy.getTaxRate() > 30)
    {
        leadership.changeCorruptionLevel((economy.getTaxRate() - 30) / 5); // +1 corruption for every 5% tax above 30
    }

    // Pay military
    int militaryCost = military.getCost();
    if (economy.spendGold(militaryCost))
    {
        military.paySoldiers(militaryCost);
    }
    else
    {
        military.paySoldiers(0);
        cout << "WARNING: Insufficient funds to pay military!\n";
    }

    // Update economy
    economy.updateInflation();
    economy.updateServicesCost();

    // Update bank
    bank.updateInterest();

    // Check for special conditions
    bool revolt = population.checkForRevolt();
    bool coup = leadership.checkForCoup();

    if (revolt)
    {
        cout << "WARNING: The people are revolting!\n";
        economy.spendGold(economy.getTreasury() / 4);
        military.changeMorale(-20);
        for (int i = 0; i < numSocialClasses; i++)
        {
            socialClasses[i]->setPopulation(socialClasses[i]->getPopulation() * 3 / 4);
            socialClasses[i]->changeHappiness(-10);
        }
        // Recalculate total population
        int newTotalPop = 0;
        for (int i = 0; i < numSocialClasses; i++)
        {
            newTotalPop += socialClasses[i]->getPopulation();
        }
        population.setPopulation(newTotalPop);
        cout << "Population reduced to " << newTotalPop << " after revolt.\n";
    }

    if (coup)
    {
        cout << "WARNING: A coup has occurred!\n";
        string newRuler = "New Ruler occurred!";
        leadership.setRuler(newRuler);
        leadership.changeLeadershipAbility(-10);
        leadership.changeCorruptionLevel(15);
        leadership.changePopularity(30);
    }

    // Random events (10% chance)
    if (rand() % 100 < 10)
    {
        string eventNames[] = {"Plague", "Good Harvest", "Drought", "Foreign Merchants", "Noble's Wedding"};
        string descriptions[] = {
            "A plague has struck your kingdom!",
            "The harvest this year was bountiful!",
            "A severe drought has damaged crops.",
            "Foreign merchants have arrived bringing exotic goods.",
            "A noble's wedding has brought festivities to the kingdom."};
        string systems[] = {"population", "economy", "economy", "economy", "leadership"};
        int impacts[] = {-30, 500, -300, 200, 15};

        int eventIndex = rand() % 5;
        Event randomEvent(eventNames[eventIndex], descriptions[eventIndex], impacts[eventIndex], systems[eventIndex]);
        handleEvent(randomEvent);

        if (eventNames[eventIndex] == "Drought")
        {
            getResource("Food").changeConsumptionRate(100);
            cout << "Drought increases food consumption by 100!\n";
        }
    }
}

void Kingdom::handleEvent(const Event &event)
{
    // cout << "Event triggered: " << event.getName() << endl;
    // cout << event.getDescription() << endl;

    // string targetSystem = event.getTargetSystem();
    // int impact = event.getImpact();

    // if (targetSystem == "population")
    // {
    //     population.changeHappiness(impact);
    //     if (impact > 0)
    //     {
    //         cout << "Population happiness increased by " << impact << endl;
    //     }
    //     else
    //     {
    //         cout << "Population happiness decreased by " << -impact << endl;
    //     }
    // }
    // else if (targetSystem == "military")
    // {
    //     military.changeMorale(impact);
    //     if (impact > 0)
    //     {
    //         cout << "Military morale increased by " << impact << endl;
    //     }
    //     else
    //     {
    //         cout << "Military morale decreased by " << -impact << endl;
    //     }
    // }
    // else if (targetSystem == "economy")
    // {
    //     economy.setTreasury(economy.getTreasury() + impact);
    //     if (impact > 0)
    //     {
    //         cout << "Treasury increased by " << impact << " gold" << endl;
    //     }
    //     else
    //     {
    //         cout << "Treasury decreased by " << -impact << " gold" << endl;
    //     }
    // }
    // else if (targetSystem == "leadership")
    // {
    //     leadership.changePopularity(impact);
    //     if (impact > 0)
    //     {
    //         cout << "Leader popularity increased by " << impact << endl;
    //     }
    //     else
    //     {
    //         cout << "Leader popularity decreased by " << -impact << endl;
    //     }
    // }
    // else if (targetSystem == "bank")
    // {
    //     bank.setReserves(bank.getReserves() + impact);
    //     if (impact > 0)
    //     {
    //         cout << "Bank reserves increased by " << impact << endl;
    //     }
    //     else
    //     {
    //         cout << "Bank reserves decreased by " << -impact << endl;
    //     }
    // }
    // else
    // {
    //     cout << "Event had no specific effect." << endl;
    // }

    event.triggerEvent(*this);
}

void Kingdom::displayStatus() const
{
    cout << "\n=== STATUS OF " << name << " ===\n";
    cout << "Population: " << population.getTotal() << " (Happiness: " << population.getHappiness() << "%, Health: " << population.getHealth() << "%)\n";
    cout << "Treasury: " << economy.getTreasury() << " gold (Tax Rate: " << economy.getTaxRate() << "%, Inflation: " << economy.getInflation() << "%)\n";
    cout << "Military: " << military.getSoldiers() << " soldiers (Morale: " << military.getMorale() << "%, Strength: " << military.calculateStrength() << ")\n";
    cout << "Ruler: " << leadership.getCurrentRuler() << " (Popularity: " << leadership.getPopularity() << "%, Corruption: " << leadership.getCorruptionLevel() << "%)\n";
    cout << "Bank: " << bank.getReserves() << " gold (Interest Rate: " << bank.getInterestRate() * 100 << "%)\n";

    cout << "\nRESOURCES:\n";
    for (int i = 0; i < numResources; i++)
    {
        resources[i].displayStatus();
    }

    cout << "\nSOCIAL CLASSES:\n";
    for (int i = 0; i < numSocialClasses; i++)
    {
        cout << "- " << socialClasses[i]->getName() << ": " << socialClasses[i]->getPopulation()
             << " (Happiness: " << socialClasses[i]->getHappiness() << "%, Productivity: " << socialClasses[i]->getProductivity() << "%)\n";
    }
}

bool Kingdom::saveGame(const string &filename) const
{
    ofstream file(filename.c_str());
    if (file.fail())
    {
        return false;
    }

    file << name << endl;
    file << population.getTotal() << " "
         << population.getGrowthRate() << " "
         << population.getHappiness() << " "
         << population.getHealth() << endl;
    file << military.getSoldiers() << " "
         << military.getTraining() << " "
         << military.getMorale() << " "
         << military.getEquipment() << endl;
    file << economy.getTreasury() << " "
         << economy.getTaxRate() << " "
         << economy.getInflation() << " "
         << economy.getServicesCost() << endl;
    file << leadership.getCurrentRuler() << endl;
    file << leadership.getPopularity() << " "
         << leadership.getLeadershipAbility() << " "
         << leadership.getCorruptionLevel() << endl;
    file << bank.getReserves() << " "
         << bank.getInterestRate() << " "
         << bank.getLoans() << " "
         << bank.getCorruption() << endl;

    file << numSocialClasses << endl;
    for (int i = 0; i < numSocialClasses; i++)
    {
        file << socialClasses[i]->getName() << endl;
        file << socialClasses[i]->getPopulation() << " "
             << socialClasses[i]->getTaxRate() << " "
             << socialClasses[i]->getHappiness() << " "
             << socialClasses[i]->getProductivity() << endl;
    }

    file << numResources << endl;
    for (int i = 0; i < numResources; i++)
    {
        file << resources[i].getName() << endl;
        file << resources[i].getAmount() << " "
             << resources[i].getProductionRate() << " "
             << resources[i].getConsumptionRate() << endl;
    }

    file.close();
    return true;
}

bool Kingdom::loadGame(const string &filename)
{
    ifstream file(filename.c_str());
    if (file.fail())
    {
        return false;
    }

    for (int i = 0; i < numSocialClasses; i++)
    {
        delete socialClasses[i];
    }
    delete[] socialClasses;
    delete[] resources;

    getline(file, name);

    int popTotal, popGrowth, popHappiness, popHealth;
    file >> popTotal >> popGrowth >> popHappiness >> popHealth;
    population = Population(popTotal);
    population.setGrowthRate(popGrowth);
    population.changeHappiness(popHappiness - population.getHappiness());
    population.changeHealth(popHealth - population.getHealth());

    int soldiers, training, morale, equipment;
    file >> soldiers >> training >> morale >> equipment;
    military = Military(soldiers);
    military.train(training - military.getTraining());
    military.changeMorale(morale - military.getMorale());
    military.equip(equipment - military.getEquipment());
    military.setSoldiers(soldiers); // Updates cost

    int treasury, taxRate, inflation, servicesCost;
    file >> treasury >> taxRate >> inflation >> servicesCost;
    economy = Economy(treasury);
    economy.setTaxRate(taxRate);

    string ruler;
    file.ignore();
    getline(file, ruler);
    int popularity, leadershipAbility, corruptionLevel;
    file >> popularity >> leadershipAbility >> corruptionLevel;
    leadership = Leadership(ruler);
    leadership.changePopularity(popularity - leadership.getPopularity());
    leadership.changeLeadershipAbility(leadershipAbility - leadership.getLeadershipAbility());
    leadership.changeCorruptionLevel(corruptionLevel - leadership.getCorruptionLevel());

    int reserves, loans, corruption;
    float interestRate;
    file >> reserves >> interestRate >> loans >> corruption;
    bank = Bank(reserves);
    bank.setInterestRate(interestRate);

    file >> numSocialClasses;
    file.ignore();
    socialClasses = new SocialClass *[numSocialClasses];
    for (int i = 0; i < numSocialClasses; i++)
    {
        string className;
        getline(file, className);
        int population, taxRate, happiness, productivity;
        file >> population >> taxRate >> happiness >> productivity;
        file.ignore();
        if (className == "Nobles")
        {
            socialClasses[i] = new Noble(population);
        }
        else if (className == "Merchants")
        {
            socialClasses[i] = new Merchant(population);
        }
        else if (className == "Peasants")
        {
            socialClasses[i] = new Peasant(population);
        }
        else
        {
            socialClasses[i] = new Peasant(population);
        }
        socialClasses[i]->setTaxRate(taxRate);
        socialClasses[i]->changeHappiness(happiness - socialClasses[i]->getHappiness());
    }

    file >> numResources;
    file.ignore();
    resources = new Resource[numResources];
    for (int i = 0; i < numResources; i++)
    {
        string resourceName;
        getline(file, resourceName);
        int amount, productionRate, consumptionRate;
        file >> amount >> productionRate >> consumptionRate;
        file.ignore();
        resources[i] = Resource(resourceName, amount, productionRate, consumptionRate);
    }

    file.close();
    return true;
}