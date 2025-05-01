# Stronghold: Kingdom Management Simulator

## Project Overview

Stronghold is a C++-based console application that simulates the management of a medieval kingdom. Players act as the ruler, making strategic decisions to balance resources, population, military, economy, leadership, and banking systems. The game features dynamic interactions between subsystems, random events, and a turn-based progression system, offering a complex and engaging simulation of kingdom governance.

The project is designed to demonstrate object-oriented programming (OOP) principles, including inheritance, polymorphism, encapsulation, and abstraction, while providing an interactive and immersive gaming experience.

## Project Division

The codebase is organized into multiple C++ files, each handling specific components of the game. Below is a breakdown of the project structure:

### 1. Header File
- **Stronghold.h**: Defines all classes, their attributes, and method signatures. It serves as the central header file, including forward declarations and class definitions for `Resource`, `Population`, `SocialClass` (with derived classes `Peasant`, `Merchant`, `Noble`), `Military`, `Economy`, `Leadership`, `Bank`, `Event`, and `Kingdom`.

### 2. Implementation Files
- **Resource.cpp**: Manages resources (e.g., Gold, Food, Wood, Stone) with methods for production, consumption, and status display.
- **Population.cpp**: Handles population dynamics, including growth rate, happiness, health, and revolt checks.
- **SocialClass.cpp**: Implements the base `SocialClass` with methods for tax generation, happiness, and productivity. Includes a virtual destructor.
- **socialClassDerived.cpp**: Contains implementations for derived classes `Peasant`, `Merchant`, and `Noble`, each with unique contributions (e.g., food for peasants, gold for merchants, influence for nobles).
- **Military.cpp**: Manages the kingdom's army, including soldier recruitment, training, equipment, morale, and strength calculations.
- **Economy.cpp**: Oversees the kingdom's treasury, tax collection, inflation, and services cost, with methods to spend gold and update economic conditions.
- **Leadership.cpp**: Manages the ruler's attributes, such as popularity, leadership ability, and corruption, with mechanics for coups and elections.
- **Bank.cpp**: Handles banking operations, including loans, interest rates, reserves, and corruption management through audits.
- **Event.cpp**: Implements random and user-triggered events that impact various kingdom systems (e.g., population, military, economy).
- **Kingdom.cpp**: The core class that integrates all subsystems, managing the kingdom's state, turn progression, event handling, and game saving/loading.
- **main2.cpp**: Contains the main game loop, user interface, and input handling. It provides a menu-driven interface with colored console output for an enhanced user experience.

## Technologies Used

- **C++**: The primary programming language, leveraging OOP principles for modular and maintainable code.
- **Windows API**: Utilized for colored console output on Windows systems (via `windows.h` and `SetConsoleTextAttribute`).
- **Random Number Generation**: Employed `cstdlib` and `ctime` for random events and dynamic outcomes (e.g., coups, revolts, elections).
- **Console Input/Output**: Used `iostream`, `conio.h` (for `_getch`), and `string` for user interaction and display.

## Code Explanation

### Core Mechanics
- **Kingdom Management**: The `Kingdom` class serves as the central hub, coordinating subsystems (`Population`, `Military`, `Economy`, `Leadership`, `Bank`, `Resource`, `SocialClass`). It handles turn progression (`advanceTurn`), event processing (`handleEvent`), and game state persistence (`saveGame`, `loadGame`).
- **Resources**: The `Resource` class manages quantities, production, and consumption of resources like Gold, Food, Wood, and Stone. Resources are critical for actions like upgrading farms or training troops.
- **Population and Social Classes**: The `Population` class tracks total population, happiness, health, and growth. Social classes (`Peasant`, `Merchant`, `Noble`) contribute resources or influence based on their productivity and happiness, which are affected by taxes and events.
- **Military**: The `Military` class manages soldiers, training, equipment, and morale. Strength is calculated based on these factors, and unpaid soldiers may desert if morale drops.
- **Economy**: The `Economy` class handles the treasury, tax rates, inflation, and service costs. High taxes increase inflation, impacting spending and tax collection.
- **Leadership**: The `Leadership` class tracks the ruler’s popularity, ability, and corruption. Low popularity and high corruption can trigger coups or election losses.
- **Bank**: The `Bank` class manages loans, interest, and reserves, with corruption affecting loan availability. Audits reduce corruption.
- **Events**: The `Event` class introduces dynamic challenges or benefits (e.g., plagues, bountiful harvests) that affect specific subsystems, adding unpredictability to the game.

### Key Features
- **Turn-Based Gameplay**: Each turn updates resources, population, economy, and military, with random events occurring 10% of the time.
- **User Interface**: A menu-driven interface in `main.cpp` allows players to issue decrees (e.g., recruit soldiers, change tax rates, trigger events). Colored console output enhances readability.
- **Dynamic Interactions**: Subsystems are interconnected. For example, low food reserves reduce population health, high taxes increase corruption, and unpaid soldiers lower military morale.
- **Save/Load System**: The game supports saving and loading kingdom states to/from text files, preserving all subsystem data.
- **Event System**: Players can trigger predefined or custom events, impacting population, military, economy, leadership, or bank systems.

### Notable Code Details
- **OOP Principles**:
  - **Inheritance**: `Peasant`, `Merchant`, and `Noble` inherit from `SocialClass`, overriding `update` and `contribute` methods.
  - **Polymorphism**: Virtual methods in `SocialClass` allow dynamic behavior based on the social class type.
  - **Encapsulation**: Private attributes with public getters/setters ensure controlled access to data.
- **Error Handling**: Input validation in `main.cpp` prevents invalid user inputs (e.g., negative numbers). Resource and population values are capped to avoid negative quantities.

## My Contributions

As the developers, Me and my Peer:
- **Designed the Game Concept**: Created a simulation that balances multiple interconnected systems, inspired by strategy and management games.
- **Structured the Codebase**: Organized the project into modular files, ensuring clear separation of concerns and maintainability.
- **Implemented Core Mechanics**: Wrote all classes and their interactions, focusing on realistic kingdom dynamics (e.g., inflation from high taxes, revolts from low happiness).
- **Developed the User Interface**: Built an intuitive console interface with colored output and a menu system for player decisions.
- **Added Persistence**: Implemented save/load functionality to allow players to resume their game.
- **Ensured Robustness**: Included input validation, boundary checks, and error handling to prevent crashes and ensure a smooth experience.
- **Tested and Debugged**: Extensively tested the game to ensure subsystems interacted correctly and events produced expected outcomes.

## How to Play

 **Gameplay**:
   - Enter your ruler’s name to start.
   - Use the menu (1-9, A-C, S, L, Q) to issue decrees, advance turns, or manage the kingdom.
   - Save/load games to persist progress.

## Future Improvements

**Waiting for Phase 2**
