#include "player.hpp"

using namespace std;

namespace ariel
{
    /**
     * Player constructor.
     *
     * @param name The name of the player.
     */
    Player::Player(const string &name) : name(name)
    {
        // Initialize resources.
        // For each resource, set the initial amount.
        resources = {
            {"wool", 0},   // Wool has an initial amount of 0.
            {"brick", 2},  // Brick has an initial amount of 2.
            {"grain", 0},  // Grain has an initial amount of 0.
            {"lumber", 2}, // Lumber has an initial amount of 2.
            {"ore", 0}     // Ore has an initial amount of 0.
        };

        // Initialize development cards.
        // For each development card, set the initial amount.
        devCards = {
            {"knight", 0},         // Knight card has an initial amount of 0.
            {"victory point", 0},  // Victory point card has an initial amount of 0.
            {"year of plenty", 0}, // Year of plenty card has an initial amount of 0.
            {"monopoly", 0},       // Monopoly card has an initial amount of 0.
            {"road building", 0}   // Road building card has an initial amount of 0.
        };

        // Initialize other variables.
        points = 0;           // Start with no points.
        someOfResources = 4;  // Start with 4 resources.
        numOfSettlements = 0; // Start with no settlements.
        numOfCities = 0;      // Start with no cities.
    }

    const string &Player::getName() const
    {
        return name;
    }

    /**
     * Adds a specified amount of a resource to the player's resources.
     *
     * @param resource The name of the resource to add.
     * @param amount The amount of the resource to add.
     */
    void Player::addResource(const string &resource, int amount)
    {
        // Increase the amount of the specified resource by the given amount.
        resources[resource] += amount;

        // Increase the total amount of resources by the given amount.
        someOfResources += amount;
    }

    /**
     * Executes a trade between two players.
     *
     * @param other The player with whom the trade is being made.
     * @param giveResource The resource being given away.
     * @param receiveResource The resource being received.
     * @param giveAmount The amount of the giving resource being traded.
     * @param receiveAmount The amount of the receiving resource being traded.
     */
    void Player::trade(Player &other, const string &giveResource, const string &receiveResource, int giveAmount, int receiveAmount)
    {
        // Check if the resources being traded are the same.
        if (giveResource == receiveResource)
        {
            cout << "Cannot trade resources of the same type." << endl;
            return;
        }

        // Check if the trade amounts are valid.
        if (giveAmount <= 0 || receiveAmount <= 0)
        {
            cout << "Invalid trade amount." << endl;
            return;
        }

        // Check if the trader has enough resources to complete the trade.
        if (giveAmount > resources[giveResource] || receiveAmount > other.resources[receiveResource])
        {
            cout << "Insufficient resources to complete trade." << endl;
            return;
        }

        // Deduct resources from both players.
        if (resources[giveResource] >= giveAmount && other.resources[receiveResource] >= receiveAmount)
        {
            resources[giveResource] -= giveAmount;
            other.resources[giveResource] += giveAmount;
            resources[receiveResource] += receiveAmount;
            other.resources[receiveResource] -= receiveAmount;

            // Update the total amount of resources.
            someOfResources -= giveAmount;
            other.someOfResources -= receiveAmount;
            cout << "Trade completed successfully." << endl;
            cout << "your updated resources: " << endl;
            printResources();
        }
        else
        {
            cout << "Trade cannot be completed due to insufficient resources." << endl;
        }
    }


    /**
     * Calculates and returns the total number of points for the player.
     *
     * The calculation is based on the number of settlements, cities, the presence of
     * three knights, and the existence of a Victory Point card.
     *
     * @return The total number of points for the player.
     */
    int Player::getPoints()
    {
        // Calculate the sum of points = settlements + cities*2 + (if have 3 knights) + (if have Victory Point card)
        int sumOfPoints = 0;

        // Add the number of settlements to the sum of points
        sumOfPoints += numOfSettlements;

        // Multiply the number of cities by 2 and add it to the sum of points
        sumOfPoints += numOfCities * 2;

        // Check if the player has three knights and add the result to the sum of points
        sumOfPoints += haveAllKnights();

        // Check if the player has a Victory Point card and add the result to the sum of points
        sumOfPoints += amountOfVictoryPoint();

        return sumOfPoints;
    }

    /**
     * Checks if the player has enough resources to purchase a specific type.
     *
     * @param type The type of resource to check.
     * @return True if the player has enough resources, false otherwise.
     */
    bool Player::hasEnoughResources(const string &type)
    {
        // Check resource type and return false if any resource is insufficient
        if (type == "settlement")
        {
            if (resources["wool"] < 1 || resources["brick"] < 1 || resources["grain"] < 1 || resources["lumber"] < 1)
            {
                return false;
            }
        }
        else if (type == "city")
        {
            if (resources["ore"] < 3 || resources["grain"] < 2)
            {
                return false;
            }
        }
        else if (type == "road")
        {
            if (resources["lumber"] < 1 || resources["brick"] < 1)
            {
                return false;
            }
        }
        else if (type == "development card")
        {
            if (resources["ore"] < 1 || resources["grain"] < 1 || resources["wool"] < 1)
            {
                return false;
            }
        }
        else if (type == "knight")
        {
            if (devCards["knight"] < 1)
            {
                return false;
            }
        }
        else if (type == "year of plenty")
        {
            if (devCards["year of plenty"] < 1)
            {
                return false;
            }
        }
        else if (type == "monopoly")
        {
            if (devCards["monopoly"] < 1)
            {
                return false;
            }
        }
        else if (type == "road building")
        {
            if (devCards["road building"] < 1)
            {
                return false;
            }
        }
        else
        {
            return false; // Handle unknown type
        }

        return true;
    }

    /**
     * Deducts the specified resource type from the player's resources.
     *
     * @param type The type of resource to deduct.
     *             Valid types are: settlement, city, road, development card,
     *                             knight, year of plenty, monopoly, road building.
     *
     * @throws None
     */
    void Player::deductResources(const string &type)
    {
        // Deduct settlement resources
        if (type == "settlement")
        {
            resources["wool"]--;
            resources["brick"]--;
            resources["grain"]--;
            resources["lumber"]--;
            someOfResources -= 4;
            cout << "Settlement purchased." << endl;
        }
        // Deduct city resources
        else if (type == "city")
        {
            resources["ore"] -= 3;
            resources["grain"] -= 2;
            someOfResources -= 5;
            cout << "City purchased." << endl;
        }
        // Deduct road resources
        else if (type == "road")
        {
            resources["lumber"]--;
            resources["brick"]--;
            someOfResources -= 2;
            cout << "Road purchased." << endl;
        }
        // Deduct development card resources
        else if (type == "development card")
        {
            resources["ore"]--;
            resources["grain"]--;
            resources["wool"]--;
            someOfResources -= 3;
            cout << "Development card purchased." << endl;
        }
        // Deduct knight card
        else if (type == "knight")
        {
            devCards["knight"]--;
            cout << "Knight card purchased." << endl;
        }
        // Deduct year of plenty card
        else if (type == "year of plenty")
        {
            devCards["year of plenty"]--;
            cout << "Year of plenty card purchased." << endl;
        }
        // Deduct monopoly card
        else if (type == "monopoly")
        {
            devCards["monopoly"]--;
            cout << "Monopoly card purchased." << endl;
        }
        // Deduct road building card
        else if (type == "road building")
        {
            devCards["road building"]--;
            cout << "Road building card purchased." << endl;
        }
        // Handle unknown type
        else
        {
            cout << "Unknown type." << endl;
        }
    }

    /**
     * Deducts a specified amount of a resource from the player's resources.
     *
     * @param type The type of resource to deduct.
     * @param amount The amount of the resource to deduct.
     */
    void Player::deductResources(const string &type, int amount)
    {
        // Check if the amount is valid.
        if (amount > 0)
        {
            // Deduct the specified amount of the resource.
            if (type == "wool")
            {
                resources["wool"] -= amount;
                someOfResources -= amount;
            }
            else if (type == "brick")
            {
                resources["brick"] -= amount;
                someOfResources -= amount;
            }
            else if (type == "grain")
            {
                resources["grain"] -= amount;
                someOfResources -= amount;
            }
            else if (type == "lumber")
            {
                resources["lumber"] -= amount;
                someOfResources -= amount;
            }
            else if (type == "ore")
            {
                resources["ore"] -= amount;
                someOfResources -= amount;
            }
        }
    }

    /**
     * When the player has more than 7 resources, this method is called.
     * It deducts half of the resources from the player.
     * It selects resources randomly and discards one unit of the chosen resource.
     *
     * @throws None
     */
    void Player::itsSeven()
    {
        // Check if the player has more than 7 resources.
        if (someOfResources > 7)
        {
            // Calculate half the resources.
            int half = someOfResources / 2;

            // Iterate for half the resources.
            for (int i = 0; i < half; i++)
            {
                // Vector to hold the resources that the player has.
                vector<string> availableResources;

                // Iterate over the resources that the player has.
                for (const auto &entry : resources)
                {
                    // Check if the resource count is greater than 0.
                    if (entry.second > 0)
                    {
                        // Add the resource type to the vector.
                        availableResources.push_back(entry.first);
                    }
                }

                // Check if there are available resources.
                if (!availableResources.empty())
                {
                    // Pick a random resource from the available resources.
                    size_t index = static_cast<size_t>(rand()) % availableResources.size();
                    string resource = availableResources[index];

                    // Discard one unit of the chosen resource.
                    resources[resource]--;
                    someOfResources--;
                }
            }
        }
    }

    /**
     * @brief Print the resources held by the player.
     *
     * This function iterates over the resources held by the player and prints
     * each resource type along with its count.
     */
    void Player::printResources()
    {
        // Iterate over the resources held by the player.
        for (const auto &entry : resources)
        {
            // Print the resource type and count.
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    /**
     * @brief Get the total number of settlements and cities owned by the player.
     */
    int Player::getNumOfSettlementsAndCities()
    {
        return numOfSettlements + numOfCities;
    }
    /**
     * @brief Increase the number of settlements owned by the player.
     *
     * This function increments the number of settlements owned by the player by 1.
     *
     */
    void Player::increaseNumOfSettlements()
    {
        // Increment the number of settlements owned by the player
        numOfSettlements++;
    }

   
    /**
     * @brief Increase the number of cities owned by the player.
     *
     * This function increments the number of cities owned by the player by 1.
     * It also decreases the number of settlements by 1.
     *
     */
    void Player::increaseNumOfCities()
    {
        numOfCities++;
        numOfSettlements--;
    }

    void Player::addDevelopmentCard(string card)
    {
        devCards[card]++;
    }

    /**
     * @brief Get the number of Knight development cards.
     *
     * This function returns the number of Knight development cards in the
     * player's collection.
     *
     * @return The number of Knight development cards.
     */
    int Player::amountOfKnights()
    {
        return devCards["knight"];
    }

    /**
     * @brief Check if the player has a specified amount of a resource.
     *
     * This function checks if the player has a specified amount of a
     * resource. It takes the name of the resource and the amount as
     * parameters and returns true if the player has at least the specified
     * amount of the resource. Otherwise, it returns false.
     *
     * @param type The name of the resource to check.
     * @param amount The amount of the resource.
     *
     * @return True if the player has at least the specified amount of the
     * resource, false otherwise.
     */
    bool Player::haveResources(string type, int amount)
    {
        // Check if the player has at least the specified amount of the resource.
        return resources[type] >= amount;
    }

    /**
     * Adds a specified number of Knight development cards to the player's collection.
     *
     * @param amount The number of Knight cards to add.
     */
    void Player::addKnights(int amount)
    {
        // Increase the number of Knight cards in the devCards map by the specified amount.
        devCards["knight"] += amount;
    }

    /**
     * Returns the amount of a specific resource held by the player.
     *
     * @param type The type of resource to retrieve.
     * @return The amount of the specified resource held by the player.
     */
    int Player::amountOfResources(string type)
    {
        // Retrieve the amount of the specified resource from the resources map.
        return resources[type];
    }

    /**
     * Checks if the player has all the Knight cards.
     *
     * @return True if the player has all the Knight cards, false otherwise.
     */
    bool Player::haveAllKnights()
    {
        // Check if the player has at least 3 Knight cards.
        return devCards["knight"] >= 3;
    }

    /**
     * Returns the number of victory point development cards the player has.
     *
     * @return The number of victory point development cards.
     */
    int Player::amountOfVictoryPoint()
    {
        return devCards["victory point"];
    }

    int Player::getAmountOfDevCards()
    {
        int sum = 0;
        for (auto &card : devCards)
        {
            sum += card.second;
        }
        return sum;
    }

    map<string, int> Player::getDevelopmentCards()
    {
        return devCards;
    }
}