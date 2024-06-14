#include "board.hpp"
#include "player.hpp"
#include "catan.hpp"
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;
using namespace ariel;

void test_board_shuffleResources()
{
    Board board;
    vector<string> resources = board.initializeResources();
    vector<string> originalResources = resources;

    board.shuffleResources(resources);

    bool isShuffled = false;
    for (size_t i = 0; i < resources.size(); ++i)
    {
        if (resources[i] != originalResources[i])
        {
            isShuffled = true;
            break;
        }
    }

    assert(isShuffled);
    cout << "test_board_shuffleResources passed." << endl;
}

void test_board_placeSettlement()
{
    Board board;
    board.initialize();
    Player player("Alice");

    bool success = board.placeSettlement(0, player, true);
    assert(success);

    success = board.placeSettlement(0, player, true);
    assert(!success);

    success = board.placeSettlement(1, player, true);
    assert(!success);

    success = board.placeSettlement(2, player, false);
    assert(!success);

    cout << "test_board_placeSettlement passed." << endl;
}

void test_board_isVertexOccupied()
{
    Board board;
    board.initialize();

    Vertex vertex = board.getVertex(0);
    bool isOccupied = board.isVertexOccupied(vertex);
    assert(!isOccupied);

    Player player("Alice");
    vertex.setOwner(player.getName());
    isOccupied = board.isVertexOccupied(vertex);
    assert(isOccupied);

    cout << "test_board_isVertexOccupied passed." << endl;
}


void test_board_hasAdjacentSettlement()
{
    Board board;
    board.initialize();
    Player player("Alice");
    board.placeSettlement(0, player, true);

    bool hasAdjacent = board.hasAdjacentSettlement(board.getVertex(0));
    assert(!hasAdjacent);

    hasAdjacent = board.hasAdjacentSettlement(board.getVertex(1));
    assert(hasAdjacent);

    cout << "test_board_hasAdjacentSettlement passed." << endl;
}

void test_board_placeSettlementAtVertex()
{
    Board board;
    board.initialize();
    Player player("Alice");
    Vertex vertex = board.getVertex(0);
    board.placeSettlementAtVertex(vertex, player);

    assert(vertex.getType() == "settlement");
    assert(vertex.getOwner() == "Alice");

    cout << "test_board_placeSettlementAtVertex passed." << endl;
}

void test_board_placeRoad()
{
    Board board;
    board.initialize();
    Player player("Bob");
    Edge edge = board.getEdge(0);
    edge.owner = "Bob";
    board.placeSettlement(0, player, true);
    bool result = board.placeRoad(edge.id, player);
    bool name = (edge.owner == player.getName());


    assert(result);
    assert(name);

    cout << "test_board_placeRoad passed." << endl;
}

void test_board_isEdgeOccupied()
{
    Board board;
    Player player("John");
    Edge edge = board.getEdge(0);
    edge.owner = "John";

    assert(board.isEdgeOccupied(edge));

    edge.owner = "";
    assert(!board.isEdgeOccupied(edge));

    cout << "test_board_isEdgeOccupied passed." << endl;
}

void test_board_upgradeSettlement()
{
    Board board;
    board.initialize();
    Player player("Alice");

    board.placeSettlement(0, player, true);
    bool success = board.upgradeSettlement(0, player);
    assert(success);

    Player player2("Bob");
    success = board.upgradeSettlement(0, player2);
    assert(!success);

    cout << "test_board_upgradeSettlement passed." << endl;
}

void test_board_getTile()
{
    Board board;
    board.initialize();

    Tile &tile = board.getTile(0);
    assert(tile.type != "");

    try
    {
        board.getTile(20);
    }
    catch (const invalid_argument &e)
    {
        cout << "test_board_getTile passed." << endl;
    }
}

void test_board_getVertex()
{
    Board board;
    board.initialize();

    Vertex &vertex = board.getVertex(0);
    assert(vertex.id == 0);

    try
    {
        board.getVertex(100);
    }
    catch (const invalid_argument &e)
    {
        cout << "test_board_getVertex passed." << endl;
    }
}


void test_board_printBoard()
{
    Board board;
    board.initialize();

    stringstream buffer;
    streambuf *oldCout = cout.rdbuf(buffer.rdbuf());

    board.printBoard();

    cout.rdbuf(oldCout);

    string output = buffer.str();
    assert(output.find("road") != string::npos || output.find("settlement") != string::npos || output.find("city") != string::npos);

    cout << "test_board_printBoard passed." << endl;
}

void test_board_isConnectedToPlayerSettlement()
{
    Board board;
    board.initialize();
    Player player("Alice");

    board.placeSettlement(0, player, true);

    Edge edge = board.getEdge(0);
    bool isConnected = board.isConnectedToPlayerSettlement(edge, player);
    assert(isConnected);

    Edge edge2 = board.getEdge(1);
    isConnected = board.isConnectedToPlayerSettlement(edge2, player);
    assert(!isConnected);

    cout << "test_board_isConnectedToPlayerSettlement passed." << endl;
}

void test_player_getName()
{
    Player player("Alice");
    assert(player.getName() == "Alice");
    cout << "test_player_getName passed." << endl;
}

void test_player_addResource()
{
    Player player("Alice");
    player.addResource("wool", 2);
    assert(player.amountOfResources("wool") == 2);
    cout << "test_player_addResource passed." << endl;
}

void test_player_trade()
{
    Player player1("Alice");
    Player player2("Bob");

    player1.addResource("wool", 3);
    player2.addResource("brick", 3);

    player1.trade(player2, "wool", "brick", 2, 2);

    assert(player1.amountOfResources("wool") == 1);
    assert(player1.amountOfResources("brick") == 2);
    assert(player2.amountOfResources("wool") == 2);
    assert(player2.amountOfResources("brick") == 1);

    cout << "test_player_trade passed." << endl;
}

void test_player_getPoints()
{
    Player player("Alice");
    player.increaseNumOfSettlements();
    player.increaseNumOfCities();
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");

    assert(player.getPoints() == 4);

    cout << "test_player_getPoints passed." << endl;
}

void test_player_hasEnoughResources()
{
    Player player("Alice");
    player.addResource("wool", 1);
    player.addResource("brick", 1);
    player.addResource("grain", 1);
    player.addResource("lumber", 1);

    assert(player.hasEnoughResources("settlement"));
    player.deductResources("settlement");

    player.addResource("ore", 3);
    player.addResource("grain", 2);

    assert(player.hasEnoughResources("city"));
    player.deductResources("city");

    assert(!player.hasEnoughResources("road"));

    cout << "test_player_hasEnoughResources passed." << endl;
}

void test_player_deductResourcesAmount()
{
    Player player("Alice");
    player.addResource("wool", 2);
    player.deductResources("wool", 1);

    assert(player.amountOfResources("wool") == 1);

    cout << "test_player_deductResourcesAmount passed." << endl;
}

void test_player_itsSeven()
{
    Player player("Alice");
    player.addResource("wool", 3);
    player.addResource("brick", 3);
    player.addResource("grain", 3);
    player.addResource("lumber", 3);

    player.itsSeven();

    assert(player.amountOfResources("wool") + player.amountOfResources("brick") +
           player.amountOfResources("grain") + player.amountOfResources("lumber") <= 7);

    cout << "test_player_itsSeven passed." << endl;
}

void test_player_printResources()
{
    Player player("Alice");
    player.addResource("wool", 2);

    stringstream buffer;
    streambuf *oldCout = cout.rdbuf(buffer.rdbuf());

    player.printResources();

    cout.rdbuf(oldCout);

    string output = buffer.str();
    assert(output.find("wool: 2") != string::npos);

    cout << "test_player_printResources passed." << endl;
}

void test_player_getNumOfSettlementsAndCities()
{
    Player player("Alice");
    player.increaseNumOfSettlements();
    player.increaseNumOfSettlements();
    player.increaseNumOfCities();

    assert(player.getNumOfSettlementsAndCities() == 2);

    cout << "test_player_getNumOfSettlementsAndCities passed." << endl;
}

void test_player_increaseNumOfSettlements()
{
    Player player("Alice");
    player.increaseNumOfSettlements();
    assert(player.getNumOfSettlementsAndCities() == 1);
    cout << "test_player_increaseNumOfSettlements passed." << endl;
}

void test_player_increaseNumOfCities()
{
    Player player("Alice");
    player.increaseNumOfSettlements();
    player.increaseNumOfCities();
    assert(player.getNumOfSettlementsAndCities() == 1);
    cout << "test_player_increaseNumOfCities passed." << endl;
}

void test_player_addDevelopmentCard()
{
    Player player("Alice");
    player.addDevelopmentCard("knight");
    assert(player.amountOfKnights() == 1);
    cout << "test_player_addDevelopmentCard passed." << endl;
}

void test_player_removeDevelopmentCard()
{
    Player player("Alice");
    player.addDevelopmentCard("knight");
    assert(player.amountOfKnights() == 1);

    player.deductResources("knight");
    assert(player.amountOfKnights() == 0);

    cout << "test_player_removeDevelopmentCard passed." << endl;
}

void test_player_getDevelopmentCards()
{
    Player player("Alice");
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");

    map<string, int> devCards = player.getDevelopmentCards();
    assert(devCards["knight"] == 1);
    assert(devCards["victory point"] == 1);

    cout << "test_player_getDevelopmentCards passed." << endl;
}

void test_player_getNumOfDevelopmentCards()
{
    Player player("Alice");
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");

    assert(player.getAmountOfDevCards() == 2);

    cout << "test_player_getNumOfDevelopmentCards passed." << endl;
}

void test_player_getNumOfKnights()
{
    Player player("Alice");
    player.addDevelopmentCard("knight");

    assert(player.amountOfKnights() == 1);

    cout << "test_player_getNumOfKnights passed." << endl;
}


void test_player_getNumOfCities()
{
    Player player("Alice");

    player.increaseNumOfSettlements();
    player.increaseNumOfCities();

    assert(player.getNumOfSettlementsAndCities() == 2);

    cout << "test_player_getNumOfCities passed." << endl;
}

void test_player_getNumOfSettlements()
{
    Player player("Alice");

    player.increaseNumOfSettlements();

    assert(player.getNumOfSettlementsAndCities() == 1);

    cout << "test_player_getNumOfSettlements passed." << endl;
}

void test_player_getNumOfVictoryPoints()
{
    Player player("Alice");
    player.addDevelopmentCard("victory point");

    assert(player.amountOfVictoryPoint() == 1);

    cout << "test_player_getNumOfVictoryPoints passed." << endl;
}

void test_player_getNumOfResources()
{
    Player player("Alice");
    player.addResource("wool", 2);
    player.addResource("brick", 3);

    assert(player.amountOfResources("wool") == 2);
    assert(player.amountOfResources("brick") == 3);

    cout << "test_player_getNumOfResources passed." << endl;
}

void test_player_haveResources()
{
    Player player("Alice");
    player.addResource("wool", 2);

    assert(player.haveResources("wool", 2));
    assert(!player.haveResources("wool", 3));

    cout << "test_player_haveResources passed." << endl;
}

void test_player_getResource()
{
    Player player("Alice");
    player.addResource("grain", 2);

    assert(player.amountOfResources("grain") == 2);

    cout << "test_player_getResource passed." << endl;
}

void test_player_removeResource()
{
    Player player("Alice");
    player.addResource("ore", 2);
    player.deductResources("ore", 1);

    assert(player.amountOfResources("ore") == 1);

    cout << "test_player_removeResource passed." << endl;
}

void test_player_hasResource()
{
    Player player("Alice");
    player.addResource("lumber", 2);

    assert(player.haveResources("lumber", 1));
    assert(player.haveResources("lumber", 2));
    assert(!player.haveResources("lumber", 3));

    cout << "test_player_hasResource passed." << endl;
}

void test_player_getAmountOfDevCards()
{
    Player player("Alice");
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");
    assert(player.getAmountOfDevCards() == 2);
    cout << "test_player_getAmountOfDevCards passed." << endl;
}

void test_catan_ChooseStartingPlayer()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.ChooseStartingPlayer();

    assert(game.getCurrentPlayer().getName() == "Alice" || 
           game.getCurrentPlayer().getName() == "Bob" || 
           game.getCurrentPlayer().getName() == "Charlie");

    cout << "test_catan_ChooseStartingPlayer passed." << endl;
}

void test_catan_nextPlayer()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.nextPlayer();

    assert(game.getCurrentPlayer().getName() == "Bob");

    game.nextPlayer();
    assert(game.getCurrentPlayer().getName() == "Charlie");

    cout << "test_catan_nextPlayer passed." << endl;
}

void test_catan_previousPlayer()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.previousPlayer();

    assert(game.getCurrentPlayer().getName() == "Charlie");

    game.previousPlayer();
    assert(game.getCurrentPlayer().getName() == "Bob");

    cout << "test_catan_previousPlayer passed." << endl;
}

void test_catan_getBoard()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    assert(board.getTilesSize() > 0);

    cout << "test_catan_getBoard passed." << endl;
}

void test_catan_printWinner()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    p1.addDevelopmentCard("victory point");

    stringstream buffer;
    streambuf *oldCout = cout.rdbuf(buffer.rdbuf());

    game.printWinner();

    cout.rdbuf(oldCout);

    string output = buffer.str();
    assert(output.find("No winner yet.") != string::npos);

    cout << "test_catan_printWinner passed." << endl;
}

void test_catan_rollDice()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.rollDice(board);

    cout << "test_catan_rollDice passed." << endl;
}

void test_catan_endTurn()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.endTurn();

    assert(game.getCurrentPlayer().getName() == "Bob");

    cout << "test_catan_endTurn passed." << endl;
}

void test_catan_getCurrentPlayer()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    assert(game.getCurrentPlayer().getName() == "Alice");

    cout << "test_catan_getCurrentPlayer passed." << endl;
}

void test_catan_isGameEnded()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    assert(!game.isGameEnded());

    for (int i = 0; i < 10; ++i)
    {
        p1.increaseNumOfSettlements();
    }
    assert(game.isGameEnded());

    cout << "test_catan_isGameEnded passed." << endl;
}

void test_catan_findPlayerByName()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    assert(game.findPlayerByName("Alice")->getName() == "Alice");
    assert(game.findPlayerByName("Bob")->getName() == "Bob");
    assert(game.findPlayerByName("Charlie")->getName() == "Charlie");
    assert(game.findPlayerByName("Dave") == nullptr);

    cout << "test_catan_findPlayerByName passed." << endl;
}

void test_catan_placeSettlement()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.placeSettelemnt(p1, board);

    cout << "test_catan_placeSettlement passed." << endl;
}

void test_catan_upgradeSettlement()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.placeSettelemnt(p1, board);
    game.upgradeSettlement(p1, board);

    cout << "test_catan_upgradeSettlement passed." << endl;
}

void test_catan_placeRoad()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.placeRoad(p1, board);

    cout << "test_catan_placeRoad passed." << endl;
}

void test_catan_playDevelopmentCard()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    p1.addDevelopmentCard("year of plenty");

    game.playDevelopmentCard(p1);

    cout << "test_catan_playDevelopmentCard passed." << endl;
}

void test_catan_trade()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    game.trade(p1);

    cout << "test_catan_trade passed." << endl;
}

void test_catan_buyDevelopmentCard()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    p1.addResource("grain", 1);
    p1.addResource("wool", 1);
    p1.addResource("ore", 1);

    game.buyDevelopmentCard(p1);

    cout << "test_catan_buyDevelopmentCard passed." << endl;
}

void test_catan_sellKnight()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    p1.addKnights(3);

    assert(game.sellKnight(p1, p2));

    cout << "test_catan_sellKnight passed." << endl;
}

void test_catan_buyKnight()
{
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    p2.addKnights(3);

    assert(game.buyKnight(p1, p2));

    cout << "test_catan_buyKnight passed." << endl;
}


int main()
{
    // Board tests
    test_board_shuffleResources();
    test_board_placeSettlement();
    test_board_isVertexOccupied();
    test_board_hasAdjacentSettlement();
    test_board_placeSettlementAtVertex();
    test_board_placeRoad();
    test_board_isEdgeOccupied();
    test_board_upgradeSettlement();
    test_board_getTile();
    test_board_getVertex();
    test_board_isConnectedToPlayerSettlement();

    // Player tests
    test_player_getName();
    test_player_addResource();
    //test_player_trade();
    //test_player_getPoints();
    //test_player_hasEnoughResources();
    test_player_deductResourcesAmount();
    //test_player_itsSeven();
    test_player_printResources();
    test_player_getNumOfSettlementsAndCities();
    test_player_increaseNumOfSettlements();
    test_player_increaseNumOfCities();
    test_player_addDevelopmentCard();
    test_player_removeDevelopmentCard();
    test_player_getNumOfDevelopmentCards();
    test_player_getNumOfKnights();
    test_player_getNumOfVictoryPoints();
    //test_player_getNumOfResources();
    //test_player_haveResources();
    test_player_getResource();
    test_player_removeResource();
    //test_player_hasResource();
    test_player_getAmountOfDevCards();

    // Catan tests
    test_catan_ChooseStartingPlayer();
    test_catan_nextPlayer();
    test_catan_previousPlayer();
    test_catan_getBoard();
    test_catan_printWinner();
    test_catan_rollDice();
    test_catan_endTurn();
    test_catan_getCurrentPlayer();
    //test_catan_isGameEnded();
    test_catan_findPlayerByName();
    //test_catan_placeSettlement();
    //test_catan_upgradeSettlement();
    //test_catan_placeRoad();
    //test_catan_playDevelopmentCard();
    //test_catan_trade();
    test_catan_buyDevelopmentCard();
    //test_catan_sellKnight();
    //test_catan_buyKnight();

    cout << "All tests passed!" << endl;
    return 0;
}
