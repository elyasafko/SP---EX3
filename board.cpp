#include "board.hpp"

namespace ariel
{

    /**
     * Constructor for the Board class.
     *
     * This constructor initializes the game board by calling the initialize()
     * function.
     */
    Board::Board()
    {
        // Initialize the game board
        initialize();
    }

    /**
     * Initializes and returns a vector of resources.
     *
     * @return A vector of strings representing the resources.
     */
    vector<string> Board::initializeResources()
    {
        // Initialize the vector of resources
        vector<string> resources = {
            "Desert",
            "wool", "wool", "wool", "wool",
            "brick", "brick", "brick",
            "grain", "grain", "grain", "grain",
            "lumber", "lumber", "lumber", "lumber",
            "ore", "ore", "ore"};

        return resources;
    }

    /**
     * Shuffles the resources vector using a random number generator.
     *
     * @param resources The vector of resources to be shuffled.
     *
     * @return None.
     */
    void Board::shuffleResources(vector<string> &resources)
    {
        // Create a random device and use it to seed a random number generator
        random_device rd;
        mt19937 g(rd());

        // Shuffle the resources vector using the random number generator
        shuffle(resources.begin(), resources.end(), g);
    }

    /**
     * Initializes the game board by creating tiles and vertices,
     * and assigning neighbors to vertices and edges.
     *
     * @return None.
     */
    void Board::initialize()
    {
        // Initialize the vector of numbers
        vector<int> numbers = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};

        // Initialize the vector of resources and shuffle it
        vector<string> resources = initializeResources();
        shuffleResources(resources);

        // Initialize the 2D vector of tiles with the appropriate layer sizes
        tiles = vector<vector<Tile>>(5);
        vector<int> layerSizes = {3, 4, 5, 4, 3};
        for (size_t i = 0; i < 5; ++i)
        {
            tiles[i].resize(static_cast<size_t>(layerSizes[i]));
        }

        // Initialize the tiles with the appropriate resources and numbers
        size_t resourceIndex = 0;
        size_t numberIndex = 0;
        for (size_t i = 0; i < 5; ++i)
        {
            for (size_t j = 0; j < layerSizes[i]; ++j)
            {
                if (resources[resourceIndex] == "Desert")
                {
                    tiles[i][j] = Tile("Desert", 7);
                    resourceIndex++;
                }
                else
                {
                    tiles[i][j] = Tile(resources[resourceIndex++], numbers[numberIndex++]);
                }
                // Print the tile details for debugging purposes
                // removed for tests
                //cout << "Tile " << i << " " << j << " " << tiles[i][j].type << " " << tiles[i][j].number << endl;
            }
        }

        // Initialize the vertices and assign neighbors to them
        for (int i = 0; i < 54; i++)
        {
            vertices.push_back(Vertex(i));
        }
        initializeVerticesNeighbors();

        // Initialize the edges and assign neighbors to them
        for (int i = 0; i < 72; i++)
        {
            edges.push_back(Edge(i));
        }
        initializeEdgesNeighbors();

        // Assign vertices and edges to the tiles
        assignVerticesAndEdgesToTiles();
    }

    void Board::initializeVerticesNeighbors()
    {
        // Manually setting neighbors based on a Catan-like hexagonal layout
        vertices[0].neighbors_vertice = {1, 8};
        vertices[1].neighbors_vertice = {0, 2};
        vertices[2].neighbors_vertice = {1, 3, 10};
        vertices[3].neighbors_vertice = {2, 4};
        vertices[4].neighbors_vertice = {3, 5, 12};
        vertices[5].neighbors_vertice = {4, 6};
        vertices[6].neighbors_vertice = {5, 14};
        vertices[7].neighbors_vertice = {8, 17};
        vertices[8].neighbors_vertice = {0, 7, 9};
        vertices[9].neighbors_vertice = {8, 10, 19};
        vertices[10].neighbors_vertice = {2, 9, 11};
        vertices[11].neighbors_vertice = {10, 12, 21};
        vertices[12].neighbors_vertice = {4, 11, 13};
        vertices[13].neighbors_vertice = {12, 14, 23};
        vertices[14].neighbors_vertice = {6, 13, 15};
        vertices[15].neighbors_vertice = {14, 25};
        vertices[16].neighbors_vertice = {17, 27};
        vertices[17].neighbors_vertice = {7, 16, 18};
        vertices[18].neighbors_vertice = {17, 19, 29};
        vertices[19].neighbors_vertice = {9, 18, 20};
        vertices[20].neighbors_vertice = {19, 21, 31};
        vertices[21].neighbors_vertice = {11, 20, 22};
        vertices[22].neighbors_vertice = {21, 23, 33};
        vertices[23].neighbors_vertice = {13, 22, 24};
        vertices[24].neighbors_vertice = {23, 25, 35};
        vertices[25].neighbors_vertice = {15, 24, 26};
        vertices[26].neighbors_vertice = {25, 37};
        vertices[27].neighbors_vertice = {16, 28};
        vertices[28].neighbors_vertice = {27, 29, 38};
        vertices[29].neighbors_vertice = {18, 28, 30};
        vertices[30].neighbors_vertice = {29, 31, 40};
        vertices[31].neighbors_vertice = {20, 30, 32};
        vertices[32].neighbors_vertice = {31, 33, 42};
        vertices[33].neighbors_vertice = {22, 32, 34};
        vertices[34].neighbors_vertice = {33, 35, 44};
        vertices[35].neighbors_vertice = {24, 34, 36};
        vertices[36].neighbors_vertice = {35, 37, 46};
        vertices[37].neighbors_vertice = {26, 36};
        vertices[38].neighbors_vertice = {28, 39};
        vertices[39].neighbors_vertice = {38, 40, 47};
        vertices[40].neighbors_vertice = {30, 39, 41};
        vertices[41].neighbors_vertice = {40, 42, 49};
        vertices[42].neighbors_vertice = {32, 41, 43};
        vertices[43].neighbors_vertice = {42, 44, 51};
        vertices[44].neighbors_vertice = {34, 43, 45};
        vertices[45].neighbors_vertice = {44, 46, 53};
        vertices[46].neighbors_vertice = {36, 45};
        vertices[47].neighbors_vertice = {39, 48};
        vertices[48].neighbors_vertice = {47, 49};
        vertices[49].neighbors_vertice = {41, 48, 50};
        vertices[50].neighbors_vertice = {49, 51};
        vertices[51].neighbors_vertice = {43, 50, 52};
        vertices[52].neighbors_vertice = {51, 53};
        vertices[53].neighbors_vertice = {45, 52};

        vertices[0].neighbors_edges = {0, 6};
        vertices[1].neighbors_edges = {0, 1};
        vertices[2].neighbors_edges = {1, 2, 7};
        vertices[3].neighbors_edges = {2, 3};
        vertices[4].neighbors_edges = {3, 4, 8};
        vertices[5].neighbors_edges = {4, 5};
        vertices[6].neighbors_edges = {5, 9};
        vertices[7].neighbors_edges = {10, 18};
        vertices[8].neighbors_edges = {6, 10, 11};
        vertices[9].neighbors_edges = {11, 12, 19};
        vertices[10].neighbors_edges = {7, 12, 13};
        vertices[11].neighbors_edges = {13, 14, 20};
        vertices[12].neighbors_edges = {8, 14, 15};
        vertices[13].neighbors_edges = {15, 16, 21};
        vertices[14].neighbors_edges = {9, 16, 17};
        vertices[15].neighbors_edges = {17, 22};
        vertices[16].neighbors_edges = {23, 33};
        vertices[17].neighbors_edges = {18, 23, 24};
        vertices[18].neighbors_edges = {24, 25, 34};
        vertices[19].neighbors_edges = {19, 25, 26};
        vertices[20].neighbors_edges = {26, 27, 35};
        vertices[21].neighbors_edges = {20, 27, 28};
        vertices[22].neighbors_edges = {28, 29, 36};
        vertices[23].neighbors_edges = {21, 29, 30};
        vertices[24].neighbors_edges = {30, 31, 37};
        vertices[25].neighbors_edges = {22, 31, 32};
        vertices[26].neighbors_edges = {32, 38};
        vertices[27].neighbors_edges = {33, 39};
        vertices[28].neighbors_edges = {39, 40, 49};
        vertices[29].neighbors_edges = {34, 40, 41};
        vertices[30].neighbors_edges = {41, 42, 50};
        vertices[31].neighbors_edges = {35, 42, 43};
        vertices[32].neighbors_edges = {43, 44, 51};
        vertices[33].neighbors_edges = {36, 44, 45};
        vertices[34].neighbors_edges = {45, 46, 52};
        vertices[35].neighbors_edges = {37, 46, 47};
        vertices[36].neighbors_edges = {47, 48, 53};
        vertices[37].neighbors_edges = {38, 48};
        vertices[38].neighbors_edges = {49, 54};
        vertices[39].neighbors_edges = {54, 55, 62};
        vertices[40].neighbors_edges = {50, 55, 56};
        vertices[41].neighbors_edges = {56, 57, 63};
        vertices[42].neighbors_edges = {51, 57, 58};
        vertices[43].neighbors_edges = {58, 59, 64};
        vertices[44].neighbors_edges = {52, 59, 60};
        vertices[45].neighbors_edges = {60, 61, 65};
        vertices[46].neighbors_edges = {53, 61};
        vertices[47].neighbors_edges = {62, 66};
        vertices[48].neighbors_edges = {66, 67};
        vertices[49].neighbors_edges = {63, 67, 68};
        vertices[50].neighbors_edges = {68, 69};
        vertices[51].neighbors_edges = {64, 69, 70};
        vertices[52].neighbors_edges = {70, 71};
        vertices[53].neighbors_edges = {65, 71};
    }

    void Board::initializeEdgesNeighbors()
    {
        // Manually setting neighbors based on a Catan-like hexagonal layout
        edges[0].neighbors_vertice = {0, 1};
        edges[1].neighbors_vertice = {1, 2};
        edges[2].neighbors_vertice = {2, 3};
        edges[3].neighbors_vertice = {3, 4};
        edges[4].neighbors_vertice = {4, 5};
        edges[5].neighbors_vertice = {5, 6};
        edges[6].neighbors_vertice = {0, 8};
        edges[7].neighbors_vertice = {2, 10};
        edges[8].neighbors_vertice = {4, 12};
        edges[9].neighbors_vertice = {6, 14};
        edges[10].neighbors_vertice = {7, 8};
        edges[11].neighbors_vertice = {8, 9};
        edges[12].neighbors_vertice = {9, 10};
        edges[13].neighbors_vertice = {10, 11};
        edges[14].neighbors_vertice = {11, 12};
        edges[15].neighbors_vertice = {12, 13};
        edges[16].neighbors_vertice = {13, 14};
        edges[17].neighbors_vertice = {14, 15};
        edges[18].neighbors_vertice = {7, 17};
        edges[19].neighbors_vertice = {9, 19};
        edges[20].neighbors_vertice = {11, 21};
        edges[21].neighbors_vertice = {13, 23};
        edges[22].neighbors_vertice = {15, 25};
        edges[23].neighbors_vertice = {16, 17};
        edges[24].neighbors_vertice = {17, 18};
        edges[25].neighbors_vertice = {18, 19};
        edges[26].neighbors_vertice = {19, 20};
        edges[27].neighbors_vertice = {20, 21};
        edges[28].neighbors_vertice = {21, 22};
        edges[29].neighbors_vertice = {22, 23};
        edges[30].neighbors_vertice = {23, 24};
        edges[31].neighbors_vertice = {24, 25};
        edges[32].neighbors_vertice = {25, 26};
        edges[33].neighbors_vertice = {16, 27};
        edges[34].neighbors_vertice = {18, 29};
        edges[35].neighbors_vertice = {20, 31};
        edges[36].neighbors_vertice = {22, 33};
        edges[37].neighbors_vertice = {24, 35};
        edges[38].neighbors_vertice = {26, 37};
        edges[39].neighbors_vertice = {27, 28};
        edges[40].neighbors_vertice = {28, 29};
        edges[41].neighbors_vertice = {29, 30};
        edges[42].neighbors_vertice = {30, 31};
        edges[43].neighbors_vertice = {31, 32};
        edges[44].neighbors_vertice = {32, 33};
        edges[45].neighbors_vertice = {33, 34};
        edges[46].neighbors_vertice = {34, 35};
        edges[47].neighbors_vertice = {35, 36};
        edges[48].neighbors_vertice = {36, 37};
        edges[49].neighbors_vertice = {28, 38};
        edges[50].neighbors_vertice = {30, 40};
        edges[51].neighbors_vertice = {32, 42};
        edges[52].neighbors_vertice = {34, 44};
        edges[53].neighbors_vertice = {36, 46};
        edges[54].neighbors_vertice = {38, 39};
        edges[55].neighbors_vertice = {39, 40};
        edges[56].neighbors_vertice = {40, 41};
        edges[57].neighbors_vertice = {41, 42};
        edges[58].neighbors_vertice = {42, 43};
        edges[59].neighbors_vertice = {43, 44};
        edges[60].neighbors_vertice = {44, 45};
        edges[61].neighbors_vertice = {45, 46};
        edges[62].neighbors_vertice = {39, 47};
        edges[63].neighbors_vertice = {41, 49};
        edges[64].neighbors_vertice = {43, 51};
        edges[65].neighbors_vertice = {45, 53};
        edges[66].neighbors_vertice = {47, 48};
        edges[67].neighbors_vertice = {48, 49};
        edges[68].neighbors_vertice = {49, 50};
        edges[69].neighbors_vertice = {50, 51};
        edges[70].neighbors_vertice = {51, 52};
        edges[71].neighbors_vertice = {52, 53};

        edges[0].neighbors_edges = {1, 6};
        edges[1].neighbors_edges = {0, 2, 7};
        edges[2].neighbors_edges = {1, 3, 7};
        edges[3].neighbors_edges = {2, 4, 8};
        edges[4].neighbors_edges = {3, 5, 8};
        edges[5].neighbors_edges = {4, 9};
        edges[6].neighbors_edges = {0, 10, 11};
        edges[7].neighbors_edges = {1, 2, 11, 12};
        edges[8].neighbors_edges = {3, 4, 14, 15};
        edges[9].neighbors_edges = {5, 16, 17};
        edges[10].neighbors_edges = {6, 11, 18};
        edges[11].neighbors_edges = {6, 10, 12, 19};
        edges[12].neighbors_edges = {7, 11, 13, 19};
        edges[13].neighbors_edges = {7, 12, 14, 20};
        edges[14].neighbors_edges = {8, 13, 15, 20};
        edges[15].neighbors_edges = {8, 14, 16, 21};
        edges[16].neighbors_edges = {9, 15, 17, 21};
        edges[17].neighbors_edges = {9, 16, 22};
        edges[18].neighbors_edges = {10, 23, 24};
        edges[19].neighbors_edges = {11, 12, 25, 26};
        edges[20].neighbors_edges = {13, 14, 27, 28};
        edges[21].neighbors_edges = {15, 16, 29, 30};
        edges[22].neighbors_edges = {17, 31, 32};
        edges[23].neighbors_edges = {18, 24, 33};
        edges[24].neighbors_edges = {18, 23, 25, 34};
        edges[25].neighbors_edges = {19, 24, 26, 34};
        edges[26].neighbors_edges = {19, 25, 27, 35};
        edges[27].neighbors_edges = {20, 26, 28, 35};
        edges[28].neighbors_edges = {20, 27, 29, 36};
        edges[29].neighbors_edges = {21, 28, 30, 36};
        edges[30].neighbors_edges = {21, 29, 31, 37};
        edges[31].neighbors_edges = {22, 30, 32, 37};
        edges[32].neighbors_edges = {22, 31, 38};
        edges[33].neighbors_edges = {23, 39};
        edges[34].neighbors_edges = {24, 25, 40, 41};
        edges[35].neighbors_edges = {26, 27, 42, 43};
        edges[36].neighbors_edges = {28, 29, 44, 45};
        edges[37].neighbors_edges = {30, 31, 46, 47};
        edges[38].neighbors_edges = {32, 48};
        edges[39].neighbors_edges = {33, 40, 49};
        edges[40].neighbors_edges = {34, 39, 41, 49};
        edges[41].neighbors_edges = {34, 40, 42, 50};
        edges[42].neighbors_edges = {35, 41, 43, 50};
        edges[43].neighbors_edges = {35, 42, 44, 51};
        edges[44].neighbors_edges = {36, 43, 45, 51};
        edges[45].neighbors_edges = {36, 44, 46, 52};
        edges[46].neighbors_edges = {37, 45, 47, 52};
        edges[47].neighbors_edges = {37, 46, 48, 53};
        edges[48].neighbors_edges = {38, 47, 53};
        edges[49].neighbors_edges = {39, 40, 54};
        edges[50].neighbors_edges = {41, 42, 55, 56};
        edges[51].neighbors_edges = {43, 44, 57, 58};
        edges[52].neighbors_edges = {45, 46, 59, 60};
        edges[53].neighbors_edges = {47, 48, 61};
        edges[54].neighbors_edges = {49, 55, 62};
        edges[55].neighbors_edges = {50, 54, 56, 62};
        edges[56].neighbors_edges = {50, 55, 57, 63};
        edges[57].neighbors_edges = {51, 56, 58, 63};
        edges[58].neighbors_edges = {51, 57, 59, 64};
        edges[59].neighbors_edges = {52, 58, 60, 64};
        edges[60].neighbors_edges = {52, 59, 61, 65};
        edges[61].neighbors_edges = {53, 60, 65};
        edges[62].neighbors_edges = {54, 55, 66};
        edges[63].neighbors_edges = {56, 57, 67, 68};
        edges[64].neighbors_edges = {58, 59, 69, 70};
        edges[65].neighbors_edges = {60, 61, 71};
        edges[66].neighbors_edges = {62, 67};
        edges[67].neighbors_edges = {63, 66, 68};
        edges[68].neighbors_edges = {63, 67, 69};
        edges[69].neighbors_edges = {64, 68, 70};
        edges[70].neighbors_edges = {64, 69, 71};
        edges[71].neighbors_edges = {65, 70};
    }

    void Board::assignVerticesAndEdgesToTiles()
    {
        // Manually assigning vertices to each tile based on a hexagonal layout
        tiles[0][0].vertices = {0, 1, 2, 8, 9, 10};
        tiles[0][1].vertices = {2, 3, 4, 10, 11, 12};
        tiles[0][2].vertices = {4, 5, 6, 12, 13, 14};
        tiles[1][0].vertices = {7, 8, 9, 17, 18, 19};
        tiles[1][1].vertices = {9, 10, 11, 19, 20, 21};
        tiles[1][2].vertices = {11, 12, 13, 21, 22, 23};
        tiles[1][3].vertices = {13, 14, 15, 23, 24, 25};
        tiles[2][0].vertices = {16, 17, 18, 27, 28, 29};
        tiles[2][1].vertices = {18, 19, 20, 29, 30, 31};
        tiles[2][2].vertices = {20, 21, 22, 31, 32, 33};
        tiles[2][3].vertices = {22, 23, 24, 33, 34, 35};
        tiles[2][4].vertices = {24, 25, 26, 35, 36, 37};
        tiles[3][0].vertices = {28, 29, 30, 38, 39, 40};
        tiles[3][1].vertices = {30, 31, 32, 40, 41, 42};
        tiles[3][2].vertices = {32, 33, 34, 42, 43, 44};
        tiles[3][3].vertices = {34, 35, 36, 44, 45, 46};
        tiles[4][0].vertices = {39, 40, 41, 47, 48, 49};
        tiles[4][1].vertices = {41, 42, 43, 49, 50, 51};
        tiles[4][2].vertices = {43, 44, 45, 51, 52, 53};

        // Manually assigning edges to each tile based on a hexagonal layout
        tiles[0][0].edges = {0, 1, 6, 7, 11, 12};
        tiles[0][1].edges = {2, 3, 7, 8, 13, 14};
        tiles[0][2].edges = {4, 5, 8, 9, 15, 16};
        tiles[1][0].edges = {10, 11, 18, 19, 24, 25};
        tiles[1][1].edges = {12, 13, 19, 20, 26, 27};
        tiles[1][2].edges = {14, 15, 20, 21, 28, 29};
        tiles[1][3].edges = {16, 17, 21, 22, 30, 31};
        tiles[2][0].edges = {23, 24, 33, 34, 39, 40};
        tiles[2][1].edges = {25, 26, 34, 35, 41, 42};
        tiles[2][2].edges = {27, 28, 35, 36, 43, 44};
        tiles[2][3].edges = {29, 30, 36, 37, 45, 46};
        tiles[2][4].edges = {31, 32, 37, 38, 47, 48};
        tiles[3][0].edges = {40, 41, 49, 50, 54, 55};
        tiles[3][1].edges = {42, 43, 50, 51, 56, 57};
        tiles[3][2].edges = {44, 45, 51, 52, 58, 59};
        tiles[3][3].edges = {46, 47, 52, 53, 60, 61};
        tiles[4][0].edges = {55, 56, 62, 63, 66, 67};
        tiles[4][1].edges = {57, 58, 63, 64, 68, 69};
        tiles[4][2].edges = {59, 60, 64, 65, 70, 71};
    }

    /**
     * Places a settlement at the specified vertex ID.
     *
     * @param vertexId The ID of the vertex to place the settlement
     * @param player The player placing the settlement
     * @param firstRound Indicates if it is the first round of placing settlements
     * @return True if the settlement is placed successfully, false otherwise
     */
    bool Board::placeSettlement(int vertexId, Player &player, bool firstRound)
    {
        // Iterate through all vertices
        for (auto &vertex : vertices)
        {
            // Check if the current vertex is the specified vertex
            if (vertex.id == vertexId)
            {
                // Check if the vertex is already occupied
                if (isVertexOccupied(vertex))
                {
                    cout << "Vertex already occupied." << endl;
                    return false;
                }

                // Check if it is not the first round and the vertex is not connected to a player's road
                if (!firstRound && !isConnectedToPlayerRoad(vertex, player))
                {
                    cout << "No road connected to this vertex." << endl;
                    return false;
                }

                // Check if the vertex has an adjacent settlement
                if (hasAdjacentSettlement(vertex))
                {
                    cout << "Settlement already connected to an adjacent vertex." << endl;
                    return false;
                }

                // Place the settlement at the vertex
                placeSettlementAtVertex(vertex, player);
                cout << "Settlement placed successfully." << endl;
                return true;
            }
        }

        // If the specified vertex is not found, return false
        return false;
    }

    /**
     * Checks if a vertex is occupied by any player.
     *
     * @param vertex The vertex to check
     * @return True if the vertex is occupied, false otherwise
     */
    bool Board::isVertexOccupied(const Vertex &vertex) const
    {
        // Check if the vertex is occupied by any player
        // A vertex is considered occupied if its owner is not empty
        return !vertex.owner.empty();
    }

    /**
     * Checks if a vertex is connected to a player's road.
     *
     * @param vertex The vertex to check
     * @param player The player whose road to check
     * @return True if the vertex is connected to the player's road, false otherwise
     */
    bool Board::isConnectedToPlayerRoad(const Vertex &vertex, Player &player) const
    {
        // Iterate through all the edges the vertex is connected to
        for (auto &edgeId : vertex.neighbors_edges)
        {
            // Iterate through all the edges to find the one with the given edgeId
            for (auto &edge : edges)
            {
                // Check if the edge has the given edgeId and the player's name
                if (edge.id == edgeId && edge.owner == player.getName())
                {
                    // Return true if the edge is found
                    return true;
                }
            }
        }
        // Return false if the edge is not found
        return false;
    }

    /**
     * Checks if the given vertex has an adjacent settlement.
     *
     * @param vertex The vertex to check
     * @return True if the vertex has an adjacent settlement, false otherwise
     */
    bool Board::hasAdjacentSettlement(const Vertex &vertex) const
    {
        // Iterate through all neighboring vertices
        for (auto &neighborId : vertex.neighbors_vertice)
        {
            // Check if the neighboring vertex is occupied by a player
            if (vertices[(size_t)neighborId].owner != "")
            {
                // Return true if an adjacent settlement is found
                return true;
            }
        }
        // Return false if no adjacent settlement is found
        return false;
    }

    /**
     * Places a settlement at the given vertex.
     *
     * @param vertex The vertex where the settlement will be placed
     * @param player The player who owns the settlement
     */
    void Board::placeSettlementAtVertex(Vertex &vertex, Player &player)
    {
        // Set the type of the vertex to "settlement"
        vertex.setType("settlement");
        // Set the owner of the vertex to the player's name
        vertex.setOwner(player.getName());
    }

    /**
     * Places a road on the given edge ID.
     *
     * @param edgeId The ID of the edge to place the road on
     * @param player The player who owns the road
     * @return True if the road is placed successfully, false otherwise
     */
    bool Board::placeRoad(int edgeId, Player &player)
    {
        // Iterate through all edges to find the one with the given edgeId
        for (auto &edge : edges)
        {
            // Check if the current edge is the one with the given edgeId
            if (edge.id == edgeId)
            {
                // Check if the edge is already occupied
                if (isEdgeOccupied(edge))
                {
                    // Print an error message if the edge is already occupied
                    cout << "Edge already occupied." << endl;
                    return false;
                }
                // Check if the edge is connected to a player's road or settlement
                if (!isConnectedToPlayerRoad(edge, player) && !isConnectedToPlayerSettlement(edge, player))
                {
                    // Print an error message if the edge is not connected to a player's road or settlement
                    cout << "No road and settlement connected to this edge." << endl;
                    return false;
                }

                // If all checks are passed, place the road
                placeRoadAtEdge(edge, player);
                // Print a success message
                cout << "Road placed successfully." << endl;
                return true;
            }
        }
        // If the edge with the given edgeId is not found, return false
        return false;
    }

    /**
     * Checks if an edge is occupied by any player.
     *
     * @param edge The edge to check
     * @return True if the edge is occupied, false otherwise
     */
    bool Board::isEdgeOccupied(const Edge &edge) const
    {
        // Check if the owner name of the edge is empty, indicating that the edge is not occupied
        return edge.owner != "";
    }

    /**
     * Checks if an edge is connected to a player's road.
     *
     * @param edge The edge to check
     * @param player The player whose road to check
     * @return True if the edge is connected to the player's road, false otherwise
     */
    bool Board::isConnectedToPlayerRoad(const Edge &edge, Player &player) const
    {
        // Iterate through all the vertices connected to the edge
        for (auto &vertexId : edge.neighbors_vertice)
        {
            // Iterate through all the vertices to find the one with the given vertexId
            for (auto &v : vertices)
            {
                // Check if the current vertex is the one with the given vertexId
                // and is owned by the player and has type "road"
                if (v.id == vertexId && v.owner == player.getName() && v.type == "road")
                {
                    // Return true if the vertex is found
                    return true;
                }
            }
        }
        // Return false if the vertex is not found
        return false;
    }

    /**
     * Places a road at the specified edge.
     *
     * This function sets the owner of the edge to the player's name.
     *
     * @param edge The edge to place the road on
     * @param player The player who owns the road
     */
    void Board::placeRoadAtEdge(Edge &edge, Player &player)
    {
        edge.owner = player.getName();
    }

    /**
     * Checks if an edge is connected to a player's settlement.
     *
     * @param edge The edge to check
     * @param player The player whose settlement to check
     * @return True if the edge is connected to the player's settlement, false otherwise
     */
    bool Board::isConnectedToPlayerSettlement(const Edge &edge, Player &player) const
    {
        // Iterate through all the vertices connected to the edge
        for (auto &vertexId : edge.neighbors_vertice)
        {
            // Iterate through all the vertices to find the one with the given vertexId
            for (auto &v : vertices)
            {
                // Check if the current vertex is the one with the given vertexId
                // and is owned by the player and has type "settlement"
                if (v.id == vertexId && v.owner == player.getName() && v.type == "settlement")
                {
                    // Return true if the vertex is found
                    return true;
                }
            }
        }
        // Return false if the vertex is not found
        return false;
    }

    /**
     * Upgrades a settlement to a city.
     *
     * @param vertexId The ID of the vertex containing the settlement to upgrade
     * @param player The player whose settlement to upgrade
     * @return True if the settlement is upgraded successfully, false otherwise
     */
    bool Board::upgradeSettlement(int vertexId, Player &player)
    {
        // Iterate through all vertices
        for (auto &vertex : vertices)
        {
            // Check if the current vertex is the specified vertex
            // and is owned by the player and has type "settlement"
            if (vertex.id == vertexId && vertex.owner == player.getName() && vertex.isSettlement())
            {
                // Upgrade the settlement to a city
                vertex.type = "city";
                cout << "Settlement upgraded to city successfully." << endl;
                return true;
            }
        }
        return false;
    }

    Tile &Board::getTile(int a)
    {
        size_t i = (size_t)a;
        if (i < 0 || i >= 19)
        {
            throw invalid_argument("Invalid tile index");
        }
        if (i < 3)
        {
            return tiles[0][i];
        }
        else if (i < 7)
        {
            return tiles[1][i - 3];
        }
        else if (i < 12)
        {
            return tiles[2][i - 7];
        }
        else if (i < 16)
        {
            return tiles[3][i - 12];
        }
        else
        {
            return tiles[4][i - 16];
        }
    }

    Vertex &Board::getVertex(int vertexId)
    {
        if (vertexId < 0 || vertexId >= vertices.size())
        {
            throw invalid_argument("Invalid vertex index");
        }
        return vertices[(size_t)vertexId];
    }

    Edge &Board::getEdge(int edgeId)
    {
        if (edgeId < 0 || edgeId >= edges.size())
        {
            throw invalid_argument("Invalid edge index");
        }
        return edges[(size_t)edgeId];
    }

    /**
     * Gives resources to a player based on the dice result.
     * Checks if the player has a settlement or city on a tile with the number rolled.
     * If so, gets the resource from the tile.
     *
     * @param player The player to give resources to.
     * @param result The number rolled on the dice.
     * @throws invalid_argument If the player name is invalid.
     */
    void Board::giveResources(Player &player, int result)
    {
        // Iterate over all tiles
        for (int i = 0; i < 19; i++)
        {
            // Get the tile at index i
            Tile &tile = getTile(i);

            // Check if the tile has the rolled number
            if (tile.number == result)
            {
                // Iterate over all vertices of the tile
                for (int vertexId : tile.vertices)
                {
                    // Get the vertex at vertexId
                    Vertex &vertex = getVertex(vertexId);

                    // Check if the vertex is owned by the player
                    if (vertex.owner == player.getName())
                    {
                        // Check if the vertex is a city or a settlement
                        if (vertex.isCity())
                        {
                            // Add two resources of the tile type to the player's resources
                            player.addResource(tile.type, 2);
                            cout << player.getName() << " got 2 " << tile.type << " from a city." << endl;
                        }
                        else if (vertex.isSettlement())
                        {
                            // Add one resource of the tile type to the player's resources
                            player.addResource(tile.type, 1);
                            cout << player.getName() << " got 1 " << tile.type << " from a settlement." << endl;
                        }
                    }
                }
            }
        }
    }

    /**
     * Checks if a given location is a valid location for placing a settlement.
     *
     * @param location The location to check
     * @return True if the location is valid for placing a settlement, false otherwise
     */
    bool Board::isValidSettlementLocation(int location)
    {
        if (location < 0 || location >= vertices.size())
        {
            cout << "Invalid location, location is out of range, you chose: " << location << "" << endl;
            return false;
        }
        // Check if the vertex is not occupied by any player
        if (isVertexOccupied(vertices[(size_t)location]))
        {
            cout << "Invalid location, vertex is occupied, you chose: " << location << "" << endl;
            return false;
        }
        // Check if the vertex has an adjacent settlement
        if (hasAdjacentSettlement(vertices[(size_t)location]))
        {
            cout << "Invalid location, vertex has an adjacent settlement, you chose: " << location << "" << endl;
            return false;
        }
        // If the vertex is not occupied and does not have an adjacent settlement, it is a valid location
        return true;
    }

    /**
     * Checks if a given location is a valid location for placing a road.
     *
     * @param location The location to check
     * @return True if the location is valid for placing a road, false otherwise
     */
    bool Board::isValidRoadLocation(int location)
    {
        // Check if the given location is within the valid range of edge locations
        if (location < 0 || location >= edges.size())
        {
            return false;
        }

        // Check if the edge at the given location is not occupied by any player
        return !isEdgeOccupied(edges[(size_t)location]);
    }

    /**
     * Prints the current state of the game board.
     * For each edge and vertex, it prints the owner and its type if it is a settlement or city.
     */
    void Board::printBoard()
    {
        cout << "-------------------" << endl;
        // Iterate over each edge
        for (auto &edge : edges)
        {
            // Check if the edge is occupied by a player
            if (edge.owner != "")
            {
                // Print the owner and the edge ID
                cout << edge.owner << " road at edge " << edge.id << endl;
            }
        }
        // Iterate over each vertex
        for (auto &vertex : vertices)
        {
            // Check if the vertex is occupied by a player
            if (vertex.owner != "")
            {
                // Check if the vertex is a settlement
                if (vertex.isSettlement())
                {
                    // Print the owner, "settlement", and the vertex ID
                    cout << vertex.owner << " settlement at vertex " << vertex.id << endl;
                }
                else
                {
                    // Print the owner, "city", and the vertex ID
                    cout << vertex.owner << " city at vertex " << vertex.id << endl;
                }
            }
        }
        cout << "-------------------" << endl;
    }


    int Board::getTilesSize() const
    {
        return tiles.size();
    }

    int Board::getEdgesSize() const
    {
        return edges.size();
    }

    int Board::getVerticesSize() const
    {
        return vertices.size();
    }


}
