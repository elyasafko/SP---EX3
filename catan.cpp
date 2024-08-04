#include "catan.hpp"

using namespace std;

namespace ariel
{

    /**
     * Constructs a Catan game with three players.
     *
     * @param p1 The first player.
     * @param p2 The second player.
     * @param p3 The third player.
     */
    Catan::Catan(Player &p1, Player &p2, Player &p3) : currentPlayerIndex(0)
    {
        // Initialize the vector of players with the given players.
        players = {p1, p2, p3};

        // Initialize the number of knights left to 3.
        knightsLeft = 3;
        VPleft = 4;
    }

    Board &Catan::getBoard()
    {
        return board;
    }

    /**
     * Ends the current player's turn and proceeds to the next player.
     *
     * This function calls the `nextPlayer` function to move the current player index to the next player in the list.
     * Therefore, the current player's turn is ended and the next player's turn begins.
     */
    void Catan::endTurn()
    {
        // Move to the next player in the list
        nextPlayer();
    }

    Player *Catan::findPlayerByName(string name)
    {
        for (auto &player : players)
        {
            if (player.getName() == name)
            {
                return &player;
            }
        }
        return nullptr;
    }

    Player &Catan::getCurrentPlayer()
    {
        return players[(size_t)currentPlayerIndex];
    }

    /**
     * Checks if any player has achieved 10 points.
     *
     * @return true if any player has achieved 10 points, false otherwise
     */
    bool Catan::isGameEnded()
    {
        // Iterate over all players
        for (auto &player : players)
        {
            // Check if the current player has achieved 10 points
            if (player.getPoints() >= 10)
            {
                return true;
            }
        }
        // No player has achieved 10 points, return false
        return false;
    }

    /**
     * Chooses a random starting player for the game.
     *
     * This function shuffles the list of players and sets the current player index to 0.
     * It then prints the order of the players to the console.
     *
     * @throws None
     */
    void Catan::ChooseStartingPlayer()
    {
        // Create a random device and use it to seed a random number generator
        random_device rd;
        mt19937 g(rd());

        // Shuffle the list of players using the random number generator
        shuffle(players.begin(), players.end(), g);

        // Set the current player index to 0
        currentPlayerIndex = 0;

        // Print the order of the players to the console
        cout << "The order of the players is: " << endl;
        for (auto &player : players)
        {
            cout << player.getName() << endl;
        }
    }

    /**
     * Sets the current player index to the index of the next player in the list.
     *
     * This function calculates the index of the next player in the list by adding 1 to the current player index
     * and taking the remainder when dividing by the size of the players list. It then sets the current player index
     * to the calculated value.
     */
    void Catan::nextPlayer()
    {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    /**
     * Sets the current player index to the index of the previous player in the list.
     *
     * This function calculates the index of the previous player in the list by subtracting 1
     * from the current player index and taking the remainder when dividing by the size of the
     * players list. It then sets the current player index to the calculated value.
     */
    void Catan::previousPlayer()
    {
        currentPlayerIndex = (currentPlayerIndex + players.size() - 1) % players.size();
    }

    /**
     * Prints the name of the winner if one of the players has reached 10 points.
     *
     * This function iterates over the players vector and checks if each player has reached 10 points.
     * If a player has reached 10 points, the function updates the winner pointer to point to that player
     * and prints their name to the console. If no player has reached 10 points, the function prints "No winner yet."
     *
     * @throws None
     */
    void Catan::printWinner()
    {
        // Initialize the winner pointer to the first player in the players vector
        Player *winner = &players[0];

        // Iterate over each player
        for (auto &player : players)
        {
            // Check if the player has reached 10 points
            if (player.getPoints() >= 10)
            {
                // Update the winner pointer to point to the current player
                winner = &player;

                // Print the name of the winner to the console
                cout << "The winner is: " << winner->getName() << endl;

                // Exit the loop since the winner has been found
                return;
            }
        }

        // If no player has reached 10 points, print "No winner yet." to the console
        cout << "No winner yet." << endl;
    }

    /**
     * Rolls the dice and gives the corresponding resources to each player.
     *
     * This function rolls the dice by generating a random number between 2 and 12.
     * The result is then printed to the console. If the result is 7, the function
     * calls the `itsSeven` function for each player. Otherwise, the function
     * gives the corresponding resources to each player by calling the `giveResources`
     * function of the `Board` class.
     *
     * @param board The game board
     */
    void Catan::rollDice(Board &board)
    {
        // Generate a random number between 2 and 12
        srand(time(0));
        int result = rand() % 6 + 1 + rand() % 6 + 1;

        // Print the dice result to the console
        cout << "Dice result is: " << result << endl;

        // If the result is 7, call the `itsSeven` function for each player
        if (result == 7)
        {
            for (auto &player : players)
            {
                player.itsSeven();
            }
            return;
        }

        // Give the corresponding resources to each player
        for (auto &player : players)
        {
            board.giveResources(player, result);
        }
    }

    /**
     * Places a settlement on the game board.
     *
     * This function prompts the player to enter a location for the settlement.
     * If the player has less than 2 settlements, the location is validated and
     * the settlement is placed on the board. If the player has 2 or more settlements,
     * the function checks if the player has enough resources to place the settlement.
     * If the player has enough resources, the location is validated and the settlement
     * is placed on the board. If the player does not have enough resources, an error
     * message is printed to the console.
     *
     * @param player The player placing the settlement
     * @param board The game board
     *
     * @throws None
     */
    void Catan::placeSettelemnt(Player &player, Board &board)
    {
        int location;

        // Check if the player has less than 2 settlements
        if (player.getNumOfSettlementsAndCities() < 2)
        {
            // Prompt the player to enter a location for the settlement
            cout << player.getName() << ", enter where you want to place your settlement: ";
            while (!(cin >> location) || !board.isValidSettlementLocation(location))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid location. Please enter a valid location for your settlement: ";
            }
            if (location < 0 || location > 53)
            {
                cout << "Invalid vertex ID." << endl;
                return;
            }
            // Place the settlement on the board
            if (board.placeSettlement(location, player, true))
            {
                player.increaseNumOfSettlements();
                return;
            }
        }
        else
        {
            // Check if the player has enough resources to place the settlement
            if (player.hasEnoughResources("settlement"))
            {
                // Prompt the player to enter a location for the settlement
                cout << player.getName() << ", enter where you want to place your settlement: ";
                while (!(cin >> location) || !board.isValidSettlementLocation(location))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid location. Please enter a valid location for your settlement: ";
                }
                if (location < 0 || location > 53)
                {
                    cout << "Invalid vertex ID." << endl;
                    return;
                }
                // Place the settlement on the board
                if (board.placeSettlement(location, player, false))
                {
                    player.increaseNumOfSettlements();
                    player.deductResources("settlement");
                    return;
                }
            }
            else
            {
                // Print an error message if the player does not have enough resources
                cout << "Insufficient resources to place settlement." << endl;
                return;
            }
        }
    }

    /**
     * Upgrades a settlement to a city for the given player.
     *
     * @param player The player upgrading the settlement
     * @param board The game board
     */
    void Catan::upgradeSettlement(Player &player, Board &board)
    {
        int location;
        // Check if the player has enough resources to upgrade the settlement
        if (player.hasEnoughResources("city"))
        {
            // Prompt the player to enter a location for the settlement
            cout << player.getName() << ", enter where you want to upgrade your settlement: ";
            while (!(cin >> location))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid location. Please enter a valid location for your city: ";
            }
            // Upgrade the settlement to a city
            if (board.upgradeSettlement(location, player))
            {
                player.deductResources("city");
                player.increaseNumOfCities();
                return;
            }
        }
        else
        {
            // Print an error message if the player does not have enough resources
            cout << "Insufficient resources to upgrade settlement." << endl;
            return;
        }
    }

    /**
     * Places a road on the game board for the given player.
     *
     * This function prompts the player to enter a location for the road.
     * If the player has enough resources to place the road, the location is validated and
     * the road is placed on the board. If the player does not have enough resources, an error
     * message is printed to the console.
     *
     * @param player The player placing the road
     * @param board The game board
     *
     * @throws None
     */
    void Catan::placeRoad(Player &player, Board &board)
    {
        int location;

        // Check if the player has enough resources to place the road
        if (player.hasEnoughResources("road"))
        {
            // Prompt the player to enter a location for the road
            cout << player.getName() << ", enter where you want to place your road: ";

            // Validate the location and place the road on the board
            while (!(cin >> location) || !board.isValidRoadLocation(location))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid location. Please enter a valid location for your road: ";
            }

            // Check if the edge ID is valid
            if (location < 0 || location > 71)
            {
                cout << "Invalid edge ID." << endl;
                return;
            }

            // Continue attempting to place the road until a valid location is chosen
            while (!board.placeRoad(location, player))
            {
                cout << "Invalid location. Please enter a valid location for your road: ";
                cin >> location;
            }

            // Once a valid location is found, deduct the resources
            player.deductResources("road");
        }
        else
        {
            // Print an error message if the player does not have enough resources
            cout << "Insufficient resources to place road." << endl;
            return;
        }
    }

    /**
     * @brief Function to handle trading
     *
     * @param player The player object
     * @return true if the trade is successful
     * @return false if the trade is not successful
     */
    bool Catan::trade(Player &player)
    {
        // Variables to store the trading information
        string name, giveResource, receiveResource;
        char choice;

        // Prompt for trading a Knight card
        cout << "Would you like to trade a Knight card? (y/n): ";
        cin >> choice;

        // If the player wants to trade a Knight card
        if (choice == 'y')
        {
            cout << "Would you like to sell or buy a Knight card? (s/b): ";
            cin >> choice;

            // If the player does not have any Knight cards
            if (choice == 's' && player.amountOfKnights() == 0)
            {
                cout << "You don't have any Knight cards." << endl;
                return false;
            }

            cout << "Enter the name of the player you want to trade with: ";
            cin >> name;

            // Find the player with the given name
            Player *other = findPlayerByName(name);
            if (other == nullptr)
            {
                cout << "Player not found." << endl;
                return false;
            }

            // Check if the player is trading with themselves
            if (other->getName() == player.getName())
            {
                cout << "You cannot trade with yourself." << endl;
                return false;
            }

            // Check if the player exists
            if (&other == nullptr)
            {
                cout << "Player not found." << endl;
                return false;
            }

            // If the player wants to sell a Knight card
            if (choice == 's')
            {
                sellKnight(player, *other);
            }
            // If the player wants to buy a Knight card
            else if (choice == 'b')
            {
                return buyKnight(player, *other);
            }
            else
            {
                cout << "Invalid choice." << endl;
                return false;
            }
        }
        // If the player wants to trade resources
        else
        {
            cout << "Enter the name of the player you want to trade with: ";
            cin >> name;

            // Find the player with the given name
            Player *other = findPlayerByName(name);

            // Check if the player is trading with themselves
            if (other->getName() == player.getName())
            {
                cout << "You cannot trade with yourself." << endl;
                return false;
            }

            // Check if the player exists
            if (&other == nullptr)
            {
                cout << "Player not found." << endl;
                return false;
            }

            cout << "Enter the resource you want to give: ";
            cin >> giveResource;
            cout << "Enter the resource you want to receive: ";
            cin >> receiveResource;
            cout << "Enter the amount you want to give: ";
            int giveAmount;
            cin >> giveAmount;
            cout << "Enter the amount you want to receive: ";
            int receiveAmount;
            cin >> receiveAmount;

            // Perform the trade
            player.trade(*other, giveResource, receiveResource, giveAmount, receiveAmount);
        }

        return false;
    }

    /**
     * Buys a development card for the player if they have enough resources.
     *
     * @param player The player who is buying the development card.
     */
    void Catan::buyDevelopmentCard(Player &player)
    {
        // Check if the player has enough resources to buy a development card.
        if (player.hasEnoughResources("development card"))
        {
            // Deduct the cost of the development card from the player's resources.
            player.deductResources("development card");

            // Pick a random number between 1 and 5 to determine which development card to give the player.
            srand(time(0));
            int card = rand() % 5 + 1;
            // If the random number is 1, the player gets a knight card.
            while (knightsLeft == 0 && card == 1 || VPleft == 0 && card == 5)
            {
                card = rand() % 5 + 1;
            }

            // Determine the type of development card to give the player based on the random number.
            if (card == 1)
            {
                player.addDevelopmentCard("knight");
                knightsLeft--;
                cout << "You have bought a knight card." << endl;
            }
            else if (card == 2)
            {
                player.addDevelopmentCard("year of plenty");
                cout << "You have bought a year of plenty card." << endl;
            }
            else if (card == 3)
            {
                player.addDevelopmentCard("monopoly");
                cout << "You have bought a monopoly card." << endl;
            }
            else if (card == 4)
            {
                player.addDevelopmentCard("road building");
                cout << "You have bought a road building card." << endl;
            }
            else if (card == 5)
            {
                player.addDevelopmentCard("victory point");
                cout << "You have bought a victory point card." << endl;
                VPleft--;
            }

            cout << "You have bought a development card." << endl;
        }
        // If the player does not have enough resources to buy a development card, inform them.
        else
        {
            cout << "Insufficient resources to buy development card." << endl;
        }
    }

    /**
     * Play a development card for the current player.
     *
     * Prompts the player to choose a development card from the available
     * cards and plays the chosen card.
     *
     * @param player The current player
     */
    void Catan::playDevelopmentCard(Player &player)
    {
        if (player.getAmountOfDevCards() == 0)
        {
            cout << "You do not have any development cards." << endl;
            return;
        }
        int choosenCard;
        cout << "Which development card do you want to play? (1-3): " << endl;
        // Display available development cards
        cout << "1. Year of Plenty" << endl;
        cout << "2. Monopoly" << endl;
        cout << "3. Road Building" << endl;
        cout << "Enter your choice: ";
        // Validate user input
        while (!(cin >> choosenCard) || choosenCard < 1 || choosenCard > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 3: ";
        }
        // Play the chosen development card
        switch (choosenCard)
        {
        case 1:
            playYearOfPlenty(player);
            break;
        case 2:
            playMonopoly(player);
            break;
        case 3:
            playRoadBuilding(player);
            break;
        }
    }

    /**
     * Sell Knight cards to another player.
     *
     * Prompts the player to enter the number of Knight cards they want to sell,
     * the resource they want in return, and the amount of that resource they want
     * in return. If the other player has enough resources, the cards are sold and
     * the transaction is completed.
     *
     * @param player The player selling the Knight cards
     * @param other The player receiving the Knight cards and paying in resources
     * @return True if the transaction is successful, false otherwise
     */
    bool Catan::sellKnight(Player &player, Player &other)
    {
        cout << "Enter the number of Knight cards you want to sell: ";
        // Get number of Knight cards to sell
        int numOfCards;
        cin >> numOfCards;
        if (numOfCards > player.amountOfKnights())
        {
            cout << "You don't have that many Knight cards." << endl;
            return false;
        }
        cout << "What resource do you want in return? ";
        // Get resource to receive in return
        string resource;
        cin >> resource;
        cout << "How many " << resource << " do you want in return? ";
        // Get amount of that resource to receive in return
        int amount;
        cin >> amount;
        if (other.haveResources(resource, amount))
        {
            // Deduct resources from other player
            other.deductResources(resource, amount);
            // Add resources to player
            player.addResource(resource, amount);
            // Transfer Knight cards
            player.addKnights(-numOfCards);
            other.addKnights(numOfCards);
            return true;
        }
        else
        {
            cout << "The other player doesn't have that many " << resource << "." << endl;
            return false;
        }
    }

    /**
     * Buy Knight cards from another player.
     *
     * Prompts the player to enter the number of Knight cards they want to buy,
     * the resource they are willing to pay, and the amount of that resource
     * they are willing to pay. If the other player has enough resources,
     * the cards are bought and the transaction is completed.
     *
     * @param player The player buying the Knight cards
     * @param other The player selling the Knight cards and receiving payment
     * @return True if the transaction is successful, false otherwise
     */
    bool Catan::buyKnight(Player &player, Player &other)
    {
        // Check if the other player has any Knight cards
        int numOfKnights = other.amountOfKnights();
        if (numOfKnights == 0)
        {
            cout << "The other player doesn't have any Knight cards." << endl;
            return false;
        }

        // Prompt for the number of Knight cards to buy
        cout << "Enter the number of Knight cards you want to buy: ";
        int numOfCards;
        cin >> numOfCards;

        // Check if the other player has enough Knight cards
        if (numOfCards > numOfKnights)
        {
            cout << "The other player doesn't have that many Knight cards." << endl;
            return false;
        }

        // Prompt for the resource to pay and the amount to pay
        cout << "What resource are you willing to pay? " << endl;
        string resource;
        cin >> resource;
        cout << "How many " << resource << " do you want to pay? ";
        int amount;
        cin >> amount;

        // Check if the player has enough resources
        if (player.haveResources(resource, amount))
        {
            // Deduct resources from player
            player.deductResources(resource, amount);

            // Add resources to other player
            other.addResource(resource, amount);

            // Transfer Knight cards
            player.addKnights(numOfCards);
            other.addKnights(-numOfCards);

            return true;
        }
        else
        {
            cout << "You don't have that many " << resource << "." << endl;
            return false;
        }
    }

    /**
     * Play the year of plenty development card.
     *
     * Allows the player to gain one of two resources of their choice.
     *
     * @param player The player playing the year of plenty card.
     */
    void Catan::playYearOfPlenty(Player &player)
    {
        // Check if the player has enough resources to play the card
        if (player.hasEnoughResources("year of plenty"))
        {
            // Prompt the player for the two resources they want
            string resource1, resource2;
            cout << "Enter the first resource: ";
            cin >> resource1;
            cout << "Enter the second resource: ";
            cin >> resource2;

            // Give the player one of each resource
            player.addResource(resource1, 1);
            player.addResource(resource2, 1);

            // Deduct the resources used to play the card
            player.deductResources("year of plenty");
        }
        else
        {
            // Notify the player that they don't have enough resources
            cout << "Insufficient resources to play year of plenty." << endl;
            return;
        }
    }

    /**
     * Play the monopoly development card.
     *
     * Allows the player to take all the resources of a specific type from all
     * other players.
     *
     * @param player The player playing the monopoly card.
     */
    void Catan::playMonopoly(Player &player)
    {
        // Check if the player has enough resources to play the card
        if (player.hasEnoughResources("monopoly"))
        {
            // Prompt the player for the resource they want
            string resource;
            cout << "Enter the resource: ";
            cin >> resource;

            // Take all resources of the specified type from all other players
            for (auto &other : players)
            {
                if (other.getName() != player.getName())
                {
                    // Calculate the amount of the specified resource held by the other player
                    int amount = other.amountOfResources(resource);

                    // Give the player the specified amount of resources
                    player.addResource(resource, amount);

                    // Take the specified amount of resources from the other player
                    other.deductResources(resource, amount);

                    // Notify the player that they got the specified amount of resources
                    cout << "You got " << amount << " " << resource << " from " << other.getName() << "." << endl;
                }
            }
            // Deduct the resources used to play the card
            player.deductResources("monopoly");

            cout << "Resources taken successfully." << endl;
        }
        else
        {
            // Notify the player that they don't have enough resources
            cout << "Insufficient resources to play monopoly." << endl;
            return;
        }
    }

    /**
     * Plays the road building card and gives the player 2 brick and 2 lumber resources.
     * Then, it places two roads on the board.
     *
     * @param player The player playing the road building card.
     */
    void Catan::playRoadBuilding(Player &player)
    {
        // Give the player 2 brick and 2 lumber resources
        player.addResource("brick", 2);
        player.addResource("lumber", 2);

        // Place two roads on the board
        placeRoad(player, board);
        placeRoad(player, board);

        // Deduct the resources used to play the card
        player.deductResources("road building");

        cout << "Roads placed successfully." << endl;
    }

}