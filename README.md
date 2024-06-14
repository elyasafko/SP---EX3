# Simplified Settlers of Catan

## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Getting Started](#getting-started)
4. [Classes and Methods](#classes-and-methods)
5. [Usage](#usage)
6. [Testing](#testing)
7. [Future Enhancements](#future-enhancements)
8. [Contributing](#contributing)
9. [License](#license)

## Introduction
This project is a simplified version of the popular board game "The Settlers of Catan". It is implemented in C++ and is designed to accommodate three players. The game involves building settlements, roads, and cities, collecting resources, and earning points to win the game. 

## Project Structure
The project consists of several files:

- `board.cpp`: Implementation of the board class, which manages the game board.
- `board.hpp`: Header file for the board class.
- `catan.cpp`: Implementation of the Catan game class, which controls the game flow.
- `catan.hpp`: Header file for the Catan game class.
- `player.cpp`: Implementation of the player class, which manages player-related actions.
- `player.hpp`: Header file for the player class.
- `startgame.cpp`: The main file that initializes and starts the game.
- `test_catan.cpp`: Contains various tests to verify the functionality of the game components.

## Getting Started
To get started with this project, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/simplified-catan.git
    ```

2. Navigate to the project directory:
    ```bash
    cd simplified-catan
    ```

3. Compile the project using the provided Makefile:
    ```bash
    make all
    ```

4. Run the game:
    ```bash
    ./startgame
    ```

## Classes and Methods
### Board Class (`board.cpp`, `board.hpp`)
- **initialize**: Sets up the game board with initial configurations.
- **shuffleResources**: Randomly shuffles the resources on the board.
- **placeSettlement**: Places a settlement on the board for a player.
- **placeRoad**: Places a road on the board.
- **upgradeSettlement**: Upgrades a settlement to a city.
- **getVertex**: Retrieves a vertex on the board.
- **getTile**: Retrieves a tile on the board.
- **isVertexOccupied**: Checks if a vertex is occupied.
- **hasAdjacentSettlement**: Checks if there are adjacent settlements to a vertex.

### Catan Class (`catan.cpp`, `catan.hpp`)
- **initialize**: Initializes the game.
- **chooseStartingPlayer**: Randomly selects the starting player.
- **nextPlayer**: Advances to the next player's turn.
- **previousPlayer**: Reverts to the previous player's turn.
- **getCurrentPlayer**: Retrieves the current player.
- **rollDice**: Simulates rolling dice.
- **endTurn**: Ends the current player's turn.
- **findPlayerByName**: Finds a player by their name.
- **buyDevelopmentCard**: Allows a player to buy a development card.

### Player Class (`player.cpp`, `player.hpp`)
- **getName**: Returns the player's name.
- **addResource**: Adds resources to the player's inventory.
- **deductResourcesAmount**: Deducts a specified amount of resources.
- **printResources**: Prints the player's resources.
- **increaseNumOfSettlements**: Increases the number of settlements owned by the player.
- **increaseNumOfCities**: Increases the number of cities owned by the player.
- **addDevelopmentCard**: Adds a development card to the player's inventory.
- **removeDevelopmentCard**: Removes a development card from the player's inventory.
- **getNumOfDevelopmentCards**: Returns the number of development cards owned by the player.
- **getNumOfKnights**: Returns the number of knights owned by the player.
- **getNumOfVictoryPoints**: Returns the number of victory points earned by the player.

## Usage
After compiling the project, you can start a new game by running the `startgame` executable. The game will prompt you to enter player names and then proceed with the game flow, including rolling dice, placing settlements, and building roads.

## Testing
The project includes a comprehensive set of tests in `test_catan.cpp` to ensure the functionality of the game components. To run the tests, compile the test file and execute it:

```bash
g++ -o test_catan test_catan.cpp -std=c++11
./test_catan
