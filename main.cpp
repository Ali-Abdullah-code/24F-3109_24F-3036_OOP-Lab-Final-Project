#include "Stronghold.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>

// Color codes for Windows console
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_CYAN 11
#define COLOR_WHITE 15

#ifdef _WIN32
#include <windows.h>
#define ENABLE_COLOR
#else
#define COLOR_RED ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_CYAN ""
#define COLOR_WHITE ""
#endif

void printColored(const string &text, int colorCode);
void printHeader(const string &title);
void pressAnyKey();

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Title Screen
    system("cls");
    printColored(R"(
        _____  _____  _____   _____  _   _   _____  _   _   _____  _      _____ 
       /  ___||_   _||  _  \ /  _  \| \ | | /  ___|| | | | /  _  \| |    |  _  \
       | |___   | |  | |_| | | | | ||  \| | | |  _ | |_| | | | | || |    | | | |
       \___  \  | |  |  _  / | | | || . ` | | | | ||  _  | | | | || |    | | | |
        ___| |  | |  | | \ \ | |_| || |\  | | |_| || | | | | |_| || |___ | |_| |
       /_____/  |_|  |_|  \_\/____/ |_| \_| \_____||_| |_| \____/ |_____||_____/
       )",
                 COLOR_CYAN);
    cout << "\n\n";
    printColored("Press any key to start your reign...", COLOR_YELLOW);
    _getch();

    // Kingdom Setup
    system("cls");
    printHeader("KINGDOM SETUP");
    cout << "Enter kingdom's Ruler name: ";
    string kingdomName;
    getline(cin, kingdomName);
    Kingdom kingdom(kingdomName);
    printColored("Welcome " + kingdomName + "! Rule wisely!\n", COLOR_GREEN);
    pressAnyKey();

    // Pre-load events
    Event events[9];
    events[0] = Event("Plague", "A terrible plague has struck your kingdom!", -20, "population");
    events[1] = Event("Bountiful Harvest", "The farmers report an excellent harvest!", 15, "economy");
    events[2] = Event("Foreign Invasion", "A neighboring kingdom has attacked your borders!", -30, "military");
    events[3] = Event("Trade Agreement", "You've secured a profitable trade agreement!", 300, "economy");
    events[4] = Event("Royal Wedding", "The royal wedding has boosted your popularity!", 25, "leadership");
    events[5] = Event("Gold Mine Discovery", "A new gold mine has been discovered!", 500, "economy");
    events[6] = Event("Military Victory", "Your troops have won a decisive victory!", 20, "military");
    events[7] = Event("Diplomatic Mission", "A diplomatic mission has improved relations!", 10, "leadership");
    events[8] = Event("War", "A war has occurred!", -12, "military");

    // Game Loop
    bool running = true;
    while (running)
    {
        system("cls");
        printHeader("KINGDOM OF " + kingdom.getName());
        kingdom.displayStatus();

        printColored("\n=== ROYAL DECREES ===\n", COLOR_CYAN);
        cout << "[1] Boost Farms (+10 Food Production, 50 gold)\n"
             << "[2] Expand Logging (+10 Wood Production, 30 gold)\n"
             << "[3] Improve Mining (+10 Stone Production, 40 gold)\n"
             << "[4] Recruit Soldiers (2 gold each)\n"
             << "[5] Train Troops (50 gold, 20 wood)\n"
             << "[6] Upgrade Armory (100 gold, 50 wood, 30 stone)\n"
             << "[7] Change Tax Rate\n"
             << "[8] Request Loan\n"
             << "[9] Repay Loan\n"
             << "[A] Conduct Bank Audit\n"
             << "[B] Trigger Event\n"
             << "[C] Let Your Kingdom run...\n"
             << "[S] Save Game\n"
             << "[L] Load Game\n"
             << "[Q] Quit Game\n\n"
             << "Your decree: ";

        char choice = _getch();
        system("cls");
        printHeader("ACTION");

        switch (toupper(choice))
        {
        case '1': // Boost Farms
        {
            if (kingdom.getEconomy().spendGold(50))
            {
                kingdom.getResource("Food").changeProductionRate(10);
                printColored("Farms upgraded! Food production increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 50 gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '2': // Expand Logging
        {
            if (kingdom.getEconomy().spendGold(30))
            {
                kingdom.getResource("Wood").changeProductionRate(10);
                printColored("Logging expanded! Wood production increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 30 gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '3': // Improve Mining
        {
            if (kingdom.getEconomy().spendGold(40))
            {
                kingdom.getResource("Stone").changeProductionRate(10);
                printColored("Mines improved! Stone production increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 40 gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '4': // Recruit Soldiers
        {
            cout << "How many soldiers to recruit? ";
            int amount;
            bool validInput = false;
            while (!validInput)
            {
                if (cin >> amount && amount >= 0)
                {
                    validInput = true;
                }
                else
                {
                    cout << "Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cin.ignore();
            int cost = amount * 2;
            if (kingdom.getEconomy().spendGold(cost))
            {
                kingdom.getMilitary().recruit(amount);
                printColored(to_string(amount) + " soldiers recruited!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need " + to_string(cost) + " gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '5': // Train Troops
        {
            if (kingdom.getEconomy().spendGold(50) && kingdom.getResource("Wood").consume(20))
            {
                kingdom.getMilitary().train(1);
                printColored("Troops trained! Training level increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 50 gold and 20 wood!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '6': // Upgrade Armory
        {
            if (kingdom.getEconomy().spendGold(100) && kingdom.getResource("Wood").consume(50) && kingdom.getResource("Stone").consume(30))
            {
                kingdom.getMilitary().equip(1);
                printColored("Armory upgraded! Equipment level increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 100 gold, 50 wood, 30 stone!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '7': // Change Tax Rate
        {
            cout << "Enter new tax rate (0-50%): ";
            int amount;
            bool validInput = false;
            while (!validInput)
            {
                if (cin >> amount && amount >= 0 && amount <= 50)
                {
                    validInput = true;
                }
                else
                {
                    cout << "Please enter a number between 0 and 50: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cin.ignore();
            kingdom.getEconomy().setTaxRate(amount);
            printColored("Tax rate set to " + to_string(amount) + "%!\n", COLOR_GREEN);
            pressAnyKey();
            break;
        }

        case '8': // Request Loan
        {
            cout << "Enter loan amount: ";
            int amount;
            bool validInput = false;
            while (!validInput)
            {
                if (cin >> amount && amount >= 0)
                {
                    validInput = true;
                }
                else
                {
                    cout << "Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cin.ignore();
            int approved = kingdom.getBank().provideLoan(amount);
            if (approved > 0)
            {
                kingdom.getEconomy().setTreasury(kingdom.getEconomy().getTreasury() + approved);
                printColored("Loan of " + to_string(approved) + " gold approved!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Loan request denied!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case '9': // Repay Loan
        {
            cout << "Enter repayment amount: ";
            int amount;
            bool validInput = false;
            while (!validInput)
            {
                if (cin >> amount && amount >= 0)
                {
                    validInput = true;
                }
                else
                {
                    cout << "Please enter a valid number: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cin.ignore();
            if (kingdom.getEconomy().spendGold(amount))
            {
                kingdom.getBank().collectLoanPayment(amount);
                printColored("Repaid " + to_string(amount) + " gold!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Insufficient funds!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case 'A': // Conduct Bank Audit
        {
            kingdom.getBank().conductAudit();
            printColored("Bank audit conducted! Corruption reduced.\n", COLOR_GREEN);
            pressAnyKey();
            break;
        }

        case 'B': // Trigger Event
        {
            printHeader("TRIGGER EVENT");
            cout << "[0] Plague (-20 population happiness)\n"
                 << "[1] Bountiful Harvest (+15 economy)\n"
                 << "[2] Foreign Invasion (-30 military morale)\n"
                 << "[3] Trade Agreement (+300 gold)\n"
                 << "[4] Royal Wedding (+25 leadership popularity)\n"
                 << "[5] Gold Mine Discovery (+500 gold)\n"
                 << "[6] Military Victory (+20 military morale)\n"
                 << "[7] Diplomatic Mission (+10 leadership popularity)\n"
                 << "[8] Custom Event\n"
                 << "Choose an event: ";

            char eventChoice = _getch();
            if (eventChoice >= '0' && eventChoice <= '7')
            {
                int eventIndex = eventChoice - '0';
                kingdom.handleEvent(events[eventIndex]);
            }
            else if (eventChoice == '8')
            {
                system("cls");
                printHeader("CUSTOM EVENT");
                string name, description, targetSystem;
                int impact;
                cout << "Event name: ";
                getline(cin, name);
                cout << "Event description: ";
                getline(cin, description);
                cout << "Target system (population/military/economy/leadership/bank): ";
                getline(cin, targetSystem);
                cout << "Impact value (positive/negative): ";
                bool validInput = false;
                while (!validInput)
                {
                    if (cin >> impact)
                    {
                        validInput = true;
                    }
                    else
                    {
                        cout << "Please enter a valid number: ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                cin.ignore();
                Event customEvent(name, description, impact, targetSystem);
                kingdom.handleEvent(customEvent);
            }
            else
            {
                printColored("Invalid event!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case 'C': // Advance Turn
        {
            printHeader("Kingdom Status");
            kingdom.advanceTurn();
            pressAnyKey();
            break;
        }

        case 'S': // Save Game
        {
            string filename;
            printHeader("SAVE KINGDOM");
            cout << "Enter save file name: ";
            getline(cin, filename);
            if (kingdom.saveGame(filename))
            {
                printColored("Kingdom saved successfully!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Failed to save kingdom!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case 'L': // Load Game
        {
            string filename;
            printHeader("LOAD KINGDOM");
            cout << "Enter save file name: ";
            getline(cin, filename);
            if (kingdom.loadGame(filename))
            {
                printColored("Kingdom loaded successfully!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Failed to load kingdom!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case 'Q': // Quit Game
        {
            running = false;
            break;
        }

        default:
        {
            printColored("Invalid decree!\n", COLOR_RED);
            pressAnyKey();
            break;
        }
        }
    }

    system("cls");
    printHeader("END OF REIGN");
    printColored("Your legacy will be remembered, ruler of " + kingdom.getName() + "!\n", COLOR_YELLOW);
    pressAnyKey();
    return 0;
}

void printHeader(const string &title)
{
    system("cls");
    printColored("========================================\n", COLOR_CYAN);
    printColored("  " + title + "\n", COLOR_CYAN);
    printColored("========================================\n\n", COLOR_CYAN);
}

void printColored(const string &text, int colorCode)
{
#ifdef ENABLE_COLOR
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
#endif
    cout << text;
#ifdef ENABLE_COLOR
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
#endif
}

void pressAnyKey()
{
    cout << "\n";
    printColored("Press any key to continue...", COLOR_YELLOW);
    _getch();
}