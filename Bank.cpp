// Bank.cpp
#include "Stronghold.h"

Bank::Bank() : reserves(0), interestRate(0.05), loans(0), corruption(0)
{
}

Bank::Bank(int initialReserves) : reserves(initialReserves), interestRate(0.05f), loans(0), corruption(0)
{
}

int Bank::getReserves() const
{
    return reserves;
}

float Bank::getInterestRate() const
{
    return interestRate;
}

int Bank::getLoans() const
{
    return loans;
}

int Bank::getCorruption() const
{
    return corruption;
}

void Bank::setReserves(int amount)
{
    reserves = amount;
    if (reserves < 0)
    {
        reserves = 0;
    }
}

void Bank::setInterestRate(float rate)
{
    interestRate = rate;
    if (interestRate < 0.01)
    {
        interestRate = 0.01;
    }
    else if (interestRate > 0.2)
    {
        interestRate = 0.2;
    }
}

int Bank::provideLoan(int amount)
{
    int maxLoan = (reserves / 2) * (100 - corruption) / 100; // Corruption reduces loan availability
    if (amount <= maxLoan)
    {
        loans += amount;
        reserves -= amount;
        corruption += 5;
        if (corruption > 100)
        {
            corruption = 100;
        }
        cout << "Bank corruption increased by 5 to " << corruption << "% due to loan.\n";
        return amount;
    }
    return 0;
}

void Bank::collectLoanPayment(int amount)
{
    loans -= amount;
    if (loans < 0)
    {
        loans = 0;
    }
    reserves += amount;
}

void Bank::updateInterest()
{
    int interestEarned = static_cast<int>(loans * interestRate);
    reserves += interestEarned;
    corruption += 1;
    if (corruption > 100)
    {
        corruption = 100;
    }
    if (interestEarned > 0 || corruption < 100)
    {
        cout << "Bank corruption increased by 1 to " << corruption << "% over time.\n";
    }
}

void Bank::conductAudit()
{
    corruption -= 10;
    if (corruption < 0)
    {
        corruption = 0;
    }
}