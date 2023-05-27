#include "gridmanager.h"

GridManager::GridManager(int gridWidth, int gridHeight) : grid(gridHeight, std::vector<int>(gridWidth)) {

    // Constructor implementation...
}

bool GridManager::gridEdge(int gridWidth, int gridHeight, int cellSize, sf::Vector2f& position) {
    // Calculate the maximum valid coordinates
    float maxX = (gridWidth - 1) * cellSize;
    float maxY = (gridHeight - 1) * cellSize;

    // Check if the position is within the grid boundaries
    bool withinGrid = (position.x >= 0 && position.x <= maxX && position.y >= 0 && position.y <= maxY);

    return withinGrid;
}
