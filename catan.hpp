#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()

#include "player.hpp"
#include "board.hpp"

using namespace std;

namespace ariel
{

    class Catan
    {
    private:
        Board board;
        vector<Player> players;
        size_t currentPlayerIndex;
        int knightsLeft;
        int VPleft;

    public:
        Catan(Player &p1, Player &p2, Player &p3);
        void ChooseStartingPlayer();
        void nextPlayer();
        void previousPlayer();
        Board &getBoard();
        void printWinner();
        void rollDice(Board &board);
        void endTurn();
        Player &getCurrentPlayer();
        bool isGameEnded();
        Player *findPlayerByName(string name);
        void placeSettelemnt(Player &palyer, Board &board);
        void upgradeSettlement(Player &player, Board &board);
        void placeRoad(Player &player, Board &board);
        void playDevelopmentCard(Player &player);
        bool trade(Player &player);
        void buyDevelopmentCard(Player &player);
        bool sellKnight(Player &player, Player &otherPlayer);
        bool buyKnight(Player &player, Player &otherPlayer);
        void playYearOfPlenty(Player &player);
        void playMonopoly(Player &player);
        void playRoadBuilding(Player &player);
    };
}

#endif
