#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <stdexcept>

#include "player.hpp"

using namespace std;

namespace ariel
{

    // Represents a Tile in the game board
    class Tile
    {
    public:
        string type;          // Resource type of the tile (e.g., wood, brick)
        int number;           // Dice number associated with the tile
        vector<int> vertices; // Indices of the vertices adjacent to the tile
        vector<int> edges;    // Indices of the edges adjacent to the tile

        Tile() = default;
        Tile(const string &type, int number) : type(type), number(number) {}
    };

    // Represents a Vertex in the game board
    class Vertex
    {
    public:
        int id;                        // Unique identifier for the vertex
        string owner;                  // Player who owns the vertex
        string type;                   // Type of structure at the vertex (e.g., settlement, city)
        vector<int> neighbors_vertice; // Indices of neighboring vertices
        vector<int> neighbors_edges;   // Indices of neighboring edges

        Vertex(int id) : id(id), owner(""), type("") {}

        bool hasSettlement() const { return !owner.empty(); }
        bool isCity() const { return type == "city"; }
        bool isSettlement() const { return type == "settlement"; }
        void setOwner(const string &player) { owner = player; }
        void setType(const string &type) { this->type = type; }
        string getOwner() const { return owner; }
        string getType() const { return type; }
    };

    // Represents an Edge in the game board
    class Edge
    {
    public:
        int id;                        // Unique identifier for the edge
        string owner;                  // Player who owns the edge
        vector<int> neighbors_vertice; // Indices of neighboring vertices
        vector<int> neighbors_edges;   // Indices of neighboring edges

        Edge(int id) : id(id), owner("") {}
    };

    // Represents the game board
    class Board
    {
    private:
        vector<vector<Tile>> tiles; // 2D grid of tiles
        vector<Vertex> vertices;    // List of all vertices
        vector<Edge> edges;         // List of all edges
        void initializeVerticesNeighbors();
        void initializeEdgesNeighbors();

    public:
        vector<string> initializeResources();

        void shuffleResources(vector<string> &resources);

        Board();

        // Initializes the board with tiles, vertices, and edges
        void initialize();

        // Places a settlement on the specified vertex
        bool placeSettlement(int vertexId, Player &player, bool firstTurn);

        // Checks if a vertex is occupied by any player
        bool isVertexOccupied(const Vertex &vertex) const;

        // Checks if a vertex is connected to a player's road
        bool isConnectedToPlayerRoad(const Vertex &vertex, Player &player) const;

        // Checks if a vertex has an adjacent settlement
        bool hasAdjacentSettlement(const Vertex &vertex) const;

        // Places a settlement at the specified vertex
        void placeSettlementAtVertex(Vertex &vertex, Player &player);

        // Places a road on the specified edge
        bool placeRoad(int edgeId, Player &player);

        // Checks if an edge is occupied by any player
        bool isEdgeOccupied(const Edge &edge) const;

        // Checks if an edge is connected to a player's road
        bool isConnectedToPlayerRoad(const Edge &edge, Player &player) const;

        // Places a road at the specified edge
        void placeRoadAtEdge(Edge &edge, Player &player);

        // Upgrades a settlement to a city
        bool upgradeSettlement(int vertexId, Player &player);

        // Gets a tile by index
        Tile &getTile(int i);

        // Gets a vertex by index
        Vertex &getVertex(int i);

        // Gets an edge by index
        Edge &getEdge(int i);

        // Gives resources to a player based on the dice result
        void giveResources(Player &player, int result);

        // Assigns vertices to tiles
        void assignVerticesAndEdgesToTiles();

        // Checks if a player has a valid settlement location
        bool isValidSettlementLocation(int vertexId);

        // Checks if a player has a valid road location
        bool isValidRoadLocation(int edgeId);

        // Prints the board
        void printBoard();

        // Checks if an edge is connected to a player's settlement
        bool isConnectedToPlayerSettlement(const Edge &edge, Player &player) const;

        int getTilesSize() const;

        int getVerticesSize() const;

        int getEdgesSize() const;

    };
}

#endif // BOARD_HPP
