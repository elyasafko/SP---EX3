#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace ariel
{

    class Player
    {
    private:
        string name;
        map<string, int> resources;
        map<string, int> devCards;
        int sumeOfResources;
        int numOfSettlements;
        int numOfCities;
        int points;

    public:
        Player(const string &name);
        const string &getName() const;
        void addResource(const string &resource, int amount);
        void trade(Player &other, const string &giveResource, const string &receiveResource, int giveAmount, int receiveAmount);
        int getPoints();
        bool hasEnoughResources(const string &type);
        void deductResources(const string &type);
        void deductResources(const string &type, int amount);
        void itsSeven();
        void printResources();
        int getNumOfSettlementsAndCities();
        void increaseNumOfSettlements();
        void increaseNumOfCities();
        void addDevelopmentCard(string card);
        int amountOfKnights();
        bool haveResources(string type, int amount);
        void addKnights(int amount);
        int amountOfResources(string type);
        bool haveAllKnights();
        int amountOfVictoryPoint();
        map <string, int> getDevelopmentCards();
        int getAmountOfDevCards();
    };
}

#endif
