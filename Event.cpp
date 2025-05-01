// Event.cpp
#include "Stronghold.h"

Event::Event() : name(""), description(""), impact(0), targetSystem("") {}

Event::Event(string name, string description, int impact, string targetSystem) : name(name), description(description), impact(impact), targetSystem(targetSystem) {}

string Event::getName() const
{
    return name;
}

string Event::getDescription() const
{
    return description;
}

int Event::getImpact() const
{
    return impact;
}

string Event::getTargetSystem() const
{
    return targetSystem;
}

void Event::triggerEvent(Kingdom &kingdom) const
{
    cout << "EVENT: " << name << " - " << description << "\n";

    if (targetSystem == "population")
    {
        kingdom.getPopulation().changeHappiness(impact);
        int newTotalPop = 0;
        for (int i = 0; i < kingdom.getNumSocialClasses(); i++)
        {
            SocialClass &socialClass = kingdom.getSocialClass(i);
            int classPop = socialClass.getPopulation();
            int newClassPop = classPop + (classPop * impact / 100);
            if (newClassPop < 0)
                newClassPop = 0;
            socialClass.setPopulation(newClassPop);
            newTotalPop += newClassPop;
        }
        kingdom.getPopulation().setPopulation(newTotalPop);
        cout << "Population changed to " << newTotalPop << " due to event.\n";
    }
    else if (targetSystem == "military" && name != "War")
    {

        kingdom.getMilitary().changeMorale(impact);
        if (impact > 0)
        {
            cout << "Military morale increased by " << impact << endl;
        }
        else
        {
            cout << "Military morale decreased by " << -impact << endl;
        }
    }
    else if (targetSystem == "military" && name == "War")
    {

        kingdom.getMilitary().changeMorale(impact);
        kingdom.getMilitary().setSoldiers(kingdom.getMilitary().getSoldiers() + impact);
        if (impact > 0)
        {
            cout << "Military soldiers increased by " << impact << endl;
        }
        else
        {
            cout << "Military soldiers decreased by " << -impact << endl;
        }
    }

    else if (targetSystem == "economy")
    {
        if (impact > 0)
        {
            kingdom.getEconomy().setTreasury(kingdom.getEconomy().getTreasury() + impact);
        }
        else
        {
            kingdom.getEconomy().spendGold(-impact);
        }
        if (impact < 0 && name == "Drought")
        {
            kingdom.getResource("Food").changeConsumptionRate(100);
            cout << "Drought increases food consumption by 100!\n";
        }
    }
    else if (targetSystem == "leadership")
    {
        if (name == "Corrupt Advisor")
        {
            kingdom.getLeadership().changeCorruptionLevel(impact);
        }
        else
        {
            kingdom.getLeadership().changePopularity(impact);
        }
    }
    else if (targetSystem == "bank")
    {
        kingdom.getBank().setReserves(kingdom.getBank().getReserves() + impact);
        if (impact > 0)
        {
            cout << "Bank reserves increased by " << impact << endl;
        }
        else
        {
            cout << "Bank reserves decreased by " << -impact << endl;
        }
    }
    else
    {
        cout << "Event had no specific effect." << endl;
    }
}