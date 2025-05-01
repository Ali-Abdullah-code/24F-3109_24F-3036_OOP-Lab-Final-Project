#include "Stronghold.h"

Peasant::Peasant(int pop) : SocialClass("Peasants", pop, 15)
{
    farmingEfficiency = 1.0; // Base efficiency for food production
}

void Peasant::update()
{
    updateProductivity();
    // Peasants' happiness affects farming efficiency
    farmingEfficiency = 0.5 + (getHappiness() / 100.0);
}

double Peasant::contribute() const
{
    return getPopulation() * farmingEfficiency * 2.0; // 2 food per peasant, modified by efficiency
}

SocialClass *Peasant::clone() const
{
    Peasant *copy = new Peasant(getPopulation());
    copy->setTaxRate(getTaxRate());
    copy->changeHappiness(getHappiness() - copy->getHappiness());
    copy->farmingEfficiency = farmingEfficiency;
    return copy;
}

Merchant::Merchant(int pop) : SocialClass("Merchants", pop, 10)
{
    tradingEfficiency = 1.0; // Base efficiency for gold production
}

void Merchant::update()
{
    updateProductivity(); // Merchants' happiness affects trading efficiency
    tradingEfficiency = 0.5 + (getHappiness() / 100.0);
}

double Merchant::contribute() const
{
    // Merchants contribute gold based on population and efficiency
    return getPopulation() * tradingEfficiency * 5.0;
}

SocialClass *Merchant::clone() const
{
    Merchant *copy = new Merchant(getPopulation());
    copy->setTaxRate(getTaxRate());
    copy->changeHappiness(getHappiness() - copy->getHappiness());
    copy->tradingEfficiency = tradingEfficiency;
    return copy;
}

Noble::Noble(int pop) : SocialClass("Nobles", pop, 5)
{
    influencePower = 1.0;
}

void Noble::update()
{
    updateProductivity();
    // Nobles' happiness affects influence power
    influencePower = 0.5 + (getHappiness() / 100.0);
}

double Noble::contribute() const
{
    // Nobles contribute influence (affects leadership popularity and military morale)
    return getPopulation() * influencePower * 0.1;
}

SocialClass *Noble::clone() const
{
    Noble *copy = new Noble(getPopulation());
    copy->setTaxRate(getTaxRate());
    copy->changeHappiness(getHappiness() - copy->getHappiness());
    copy->influencePower = influencePower; // Fixed typo from 'influenceallarPower'
    return copy;
}

int SocialClass::consume(Resource *resource, int amount)
{
    // Consume implementation
    if (resource->consume(amount))
    {
        return amount;
    }
    return 0;
}