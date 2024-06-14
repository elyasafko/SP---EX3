#include <iostream>
#include <stdexcept>
#include <vector>

#include "player.hpp"
#include "board.hpp"
#include "catan.hpp"

using namespace std;
using namespace ariel;

/**
 * This function places initial structures (settlement and road) for a player on the game board.
 *
 * @param catan A reference to the Catan game.
 * @param player A reference to the player.
 * @param board A reference to the game board.
 */
void placeInitialStructures(Catan &catan, Player &player, Board &board)
{
    // Place a settlement on the board for the player
    catan.placeSettelemnt(player, board);

    // Place a road on the board for the player
    catan.placeRoad(player, board);
}

/**
 * This function is called when it's the player's turn.
 *
 * @param catan A reference to the Catan game.
 * @param board A reference to the game board.
 */
void playerTurn(Catan &catan, Board &board)
{
    int choice, location;
    string name, giveResource, receiveResource;
    Player &player = catan.getCurrentPlayer();

    // Loop until the player has ended their turn.
    do
    {
        // Display the menu of options.
        cout << "1. End turn" << endl;
        cout << "2. Build road" << endl;
        cout << "3. Build settlement" << endl;
        cout << "4. Build city" << endl;
        cout << "5. Buy development card" << endl;
        cout << "6. Play development card" << endl;
        cout << "7. Trade resources or Knights" << endl;
        cout << "8. Print board data" << endl;
        cout << "9. Print my resources" << endl;

        // Prompt the player to choose an option.
        cout << "Enter your choice: ";

        // Validate the user input.
        while (!(cin >> choice) || choice < 1 || choice > 8)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 8: ";
        }

        // Execute the chosen option.
        switch (choice)
        {
        case 1:
            // End the turn.
            catan.endTurn();
            cout << "--------------------------" << endl;
            break;

        case 2:
            // Build a road.
            catan.placeRoad(player, board);
            break;

        case 3:
            // Build a settlement.
            catan.placeSettelemnt(player, board);
            break;

        case 4:
            // Upgrade a settlement to a city.
            catan.upgradeSettlement(player, board);
            break;

        case 5:
            // Buy a development card.
            catan.buyDevelopmentCard(player);
            break;

        case 6:
            // Play a development card.
            catan.playDevelopmentCard(player);
            break;

        case 7:
            // Trade resources with another player.
            catan.trade(player);
            break;

        case 8:
            // Print the board data.
            board.printBoard();
            break;
        case 9:
            // Print the player's resources.
            player.printResources();
            break;
        default:
            break;
        }

    } while (choice != 1);
}

/**
 * Main function that starts the Catan game.
 *
 * @return 0 upon successful completion of the game.
 */
int main()
{
    cout << "Welcome to Catan!" << endl;

    // Get names of the players
    cout << "Please enter the name of the first player: ";
    string name1;
    cin >> name1;

    cout << "Please enter the name of the second player: ";
    string name2;
    cin >> name2;

    cout << "Please enter the name of the third player: ";
    string name3;
    cin >> name3;

    // Create players
    Player p1(name1);
    Player p2(name2);
    Player p3(name3);

    // Create Catan game
    Catan catan(p1, p2, p3);
    catan.ChooseStartingPlayer();
    Board board = catan.getBoard();

    // Display game instructions and board
    string commanda = "xdg-open edges-8.jpg";
    string commandb = "xdg-open vertices-7.jpg";
    system(commanda.c_str());
    system(commandb.c_str());

    cout << "Starting of the game. Every player places two settlements and two roads." << endl;

    // Place initial structures
    // order of the players: p1 -> p2 -> p3 -> p3 -> p2 -> p1 (p1 as a starting player)
    placeInitialStructures(catan, catan.getCurrentPlayer(), board);
    catan.nextPlayer();
    placeInitialStructures(catan, catan.getCurrentPlayer(), board);
    catan.nextPlayer();
    placeInitialStructures(catan, catan.getCurrentPlayer(), board);
    placeInitialStructures(catan, catan.getCurrentPlayer(), board);
    catan.previousPlayer();
    placeInitialStructures(catan, catan.getCurrentPlayer(), board);
    catan.previousPlayer();
    placeInitialStructures(catan, catan.getCurrentPlayer(), board);

    // Start the game
    cout << endl;
    cout << "=============================================" << endl;
    cout << "             Game started" << endl;
    cout << "=============================================" << endl;
    cout << endl;

    while (!catan.isGameEnded())
    {
        // Print current player's turn information
        cout << "*** It's " << catan.getCurrentPlayer().getName() << "'s turn. ***" << endl << endl;
        catan.rollDice(board);
        cout << "Your resources: " << endl;
        catan.getCurrentPlayer().printResources();

        // Perform player's turn
        playerTurn(catan, board);
    }

    // Print the winner
    catan.printWinner();
    return 0;
}
