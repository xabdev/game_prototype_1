#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class GridManager {
public:
    GridManager(int gridWidth, int gridHeight);
    bool gridEdge(int gridWidth, int gridHeight, int cellSize, sf::Vector2f& position);

    // Other member functions and variables...
    std::vector<std::vector<int>> grid;

private:
    
};
