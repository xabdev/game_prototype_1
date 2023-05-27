#include "levels.h"


sf::Image Levels::loadImage() {

    sf::Image image;
    if (!image.loadFromFile("img/test.png")) {
        std::cout << "Failed to load image \n";
    }
    return image;
}


sf::Vector2f Levels::getImageDimensions(sf::Image image) {

    sf::Vector2f imageDimension;
    imageDimension.x = image.getSize().x;
    std::cout << imageDimension.x << "\n";
    imageDimension.y = image.getSize().y;
    std::cout << imageDimension.y << "\n";
    return imageDimension;
}


std::vector<std::vector<int>> Levels::translateImage() {
    sf::Image image = loadImage();
    sf::Vector2f imageDimension = getImageDimensions(image);

    float cellWidth = imageDimension.x / static_cast<float>(gridWidth);
    float cellHeight = imageDimension.y / static_cast<float>(gridHeight);

    std::vector<std::vector<int>> resultGrid(gridHeight, std::vector<int>(gridWidth));

    for (int row = 0; row < gridHeight; ++row) {
        for (int col = 0; col < gridWidth; ++col) {
            bool hasColoredPixel = false;

            // Calculate the pixel range for the current cell
            int startX = col * cellWidth;
            int startY = row * cellHeight;
            int endX = static_cast<int>((col + 1) * cellWidth);
            int endY = static_cast<int>((row + 1) * cellHeight);

            // Check each pixel within the current cell range
            for (int y = startY; y < endY; ++y) {
                for (int x = startX; x < endX; ++x) {
                    sf::Color pixelColor = image.getPixel(x, y);

                    // Check if the pixel color is not transparent (alpha > 0)
                    if (pixelColor.a > 0) {
                        hasColoredPixel = true;
                        break;
                    }
                }
                if (hasColoredPixel) {
                    break;
                }
            }

            // Mark the corresponding cell in the result grid
            resultGrid[row][col] = hasColoredPixel ? 1 : 0;
        }
    }

    return resultGrid;
}

std::vector<std::vector<int>> Levels::translateImage2() {
    sf::Image image = loadImage();
    sf::Vector2f imageDimension = getImageDimensions(image);

    float cellWidth = imageDimension.x / static_cast<float>(gridWidth);
    float cellHeight = imageDimension.y / static_cast<float>(gridHeight);

    std::vector<std::vector<int>> resultGrid(gridHeight, std::vector<int>(gridWidth));

    for (int row = 0; row < gridHeight; ++row) {
        for (int col = 0; col < gridWidth; ++col) {
            sf::Color cellColor; // Store the RGB color code for non-transparent cells

            // Calculate the pixel range for the current cell
            int startX = col * cellWidth;
            int startY = row * cellHeight;
            int endX = static_cast<int>((col + 1) * cellWidth);
            int endY = static_cast<int>((row + 1) * cellHeight);

            bool hasColoredPixel = false;

            // Check each pixel within the current cell range
            for (int y = startY; y < endY; ++y) {
                for (int x = startX; x < endX; ++x) {
                    sf::Color pixelColor = image.getPixel(x, y);

                    // Check if the pixel color is not transparent (alpha > 0)
                    if (pixelColor.a > 0) {
                        hasColoredPixel = true;
                        cellColor = sf::Color(pixelColor.r, pixelColor.g, pixelColor.b);
                        std::cout << cellColor.r << " " << cellColor.g << " " << cellColor.b << "\n"; 
                        break;
                    }
                }

                if (hasColoredPixel) {
                    break;
                }
            }

            // Store either the RGB code or 0 for transparent cells in the result grid
            if (hasColoredPixel) {
                resultGrid[row][col] = cellColor.toInteger(); // Store RGB code
            } else {
                resultGrid[row][col] = 0; // Transparent cell
            }
        }
    }

    return resultGrid;
}

std::vector<std::vector<sf::Color>> Levels::translateImage3() {
    sf::Image image = loadImage();
    sf::Vector2f imageDimension = getImageDimensions(image);

    float cellWidth = imageDimension.x / static_cast<float>(gridWidth);
    float cellHeight = imageDimension.y / static_cast<float>(gridHeight);

    std::vector<std::vector<sf::Color>> resultGrid(gridHeight, std::vector<sf::Color>(gridWidth));

    for (int row = 0; row < gridHeight; ++row) {
        for (int col = 0; col < gridWidth; ++col) {
            sf::Color cellColor; // Store the RGB color code for non-transparent cells

            // Calculate the pixel range for the current cell
            int startX = col * cellWidth;
            int startY = row * cellHeight;
            int endX = static_cast<int>((col + 1) * cellWidth);
            int endY = static_cast<int>((row + 1) * cellHeight);

            bool hasColoredPixel = false;

            // Check each pixel within the current cell range
            for (int y = startY; y < endY; ++y) {
                for (int x = startX; x < endX; ++x) {
                    sf::Color pixelColor = image.getPixel(x, y);

                    // Check if the pixel color is not transparent (alpha > 0)
                    if (pixelColor.a == 255) {
                        hasColoredPixel = true;
                        cellColor = pixelColor;
                        break;
                    }
                }

                if (hasColoredPixel) {
                    break;
                }
            }

            // Store either the RGB code or transparent value in the result grid
            if (hasColoredPixel) {
                resultGrid[row][col] = cellColor; // Store RGB color
            } else {
                resultGrid[row][col] = sf::Color::Transparent; // Transparent cell
            }
        }
    }

    return resultGrid;
}






std::vector<sf::RectangleShape> Levels::createLevel() {
    std::vector<std::vector<sf::Color>> resultGrid = translateImage3();
    std::vector<sf::RectangleShape> level;

    for (int row = 0; row < gridHeight; ++row) {
        int startCol = 0;
        int endCol = 0;

        while (endCol < gridWidth) {
            // Find the start and end columns of a series of adjacent marked cells
            while (startCol < gridWidth && resultGrid[row][startCol] == sf::Color::Transparent) {
                startCol++;
            }
            endCol = startCol;

            bool hasAdjacentVertical = false;
            for (int i = startCol; i < endCol; ++i) {
                if (row > 0 && resultGrid[row - 1][i] != sf::Color::Transparent) {
                    hasAdjacentVertical = true;
                    break;
                }
            }

            while (endCol < gridWidth && resultGrid[row][endCol] != sf::Color::Transparent && !hasAdjacentVertical) {
                endCol++;
            }

            // Create a rectangle shape for the series of adjacent cells
            if (startCol < gridWidth && !hasAdjacentVertical) {
                sf::RectangleShape cellShape(sf::Vector2f((endCol - startCol) * cellSize, cellSize));
                cellShape.setFillColor(resultGrid[row][startCol]);
                cellShape.setPosition(startCol * cellSize, row * cellSize);

                level.push_back(cellShape);
            }

            startCol = endCol;
        }
    }

    return level;
}






/*
std::vector<sf::RectangleShape> Levels::createLevel() {
    std::vector<std::vector<int>> resultGrid = translateImage();
    std::vector<sf::RectangleShape> level;

    for (int row = 0; row < gridHeight; ++row) {
        int startCol = 0;
        int endCol = 0;

        while (endCol < gridWidth) {
            // Find the start and end columns of a series of adjacent marked cells
            while (startCol < gridWidth && resultGrid[row][startCol] != 1) {
                startCol++;
            }
            endCol = startCol;

            bool hasAdjacentVertical = false;
            for (int i = startCol; i < endCol; ++i) {
                if (row > 0 && resultGrid[row - 1][i] == 1) {
                    hasAdjacentVertical = true;
                    break;
                }
            }

            while (endCol < gridWidth && resultGrid[row][endCol] == 1 && !hasAdjacentVertical) {
                endCol++;
            }

            // Create a rectangle shape for the series of adjacent cells
            if (startCol < gridWidth && !hasAdjacentVertical) {
                sf::RectangleShape cellShape(sf::Vector2f((endCol - startCol) * cellSize, cellSize));
                cellShape.setOutlineThickness(2.f);
                cellShape.setFillColor(sf::Color::Transparent);
                cellShape.setOutlineColor(sf::Color::Magenta);
                cellShape.setPosition(startCol * cellSize, row * cellSize);

                level.push_back(cellShape);
            }

            startCol = endCol;
        }
    }

    return level;
}
*/








/*
std::vector<sf::RectangleShape> Levels::mergeCellsToRectangles(const std::vector<std::vector<int>>& grid) {
    int gridWidth = grid[0].size();
    int gridHeight = grid.size();

    std::vector<sf::RectangleShape> rectangles;

    // Check if the grid is empty
    if (gridWidth == 0 || gridHeight == 0) {
        return rectangles;
    }

    std::vector<std::vector<bool>> visited(gridHeight, std::vector<bool>(gridWidth, false));

    for (int row = 0; row < gridHeight; ++row) {
        for (int col = 0; col < gridWidth; ++col) {
            // If the cell is occupied and not visited, start forming a rectangle
            if (grid[row][col] == 1 && !visited[row][col]) {
                int rectWidth = 1;
                int rectHeight = 1;

                // Expand horizontally to find the width of the rectangle
                while (col + rectWidth < gridWidth && grid[row][col + rectWidth] == 1) {
                    ++rectWidth;
                }

                // Expand vertically to find the height of the rectangle
                while (row + rectHeight < gridHeight) {
                    bool validRow = true;
                    for (int i = col; i < col + rectWidth; ++i) {
                        if (grid[row + rectHeight][i] != 1) {
                            validRow = false;
                            break;
                        }
                    }
                    if (validRow) {
                        ++rectHeight;
                    } else {
                        break;
                    }
                }

                // Create the rectangle shape
                sf::RectangleShape rectangle(sf::Vector2f(rectWidth * cellSize, rectHeight * cellSize));
                rectangle.setFillColor(sf::Color::Blue);
                rectangle.setPosition(col * cellSize, row * cellSize);

                // Mark the cells as visited
                for (int i = row; i < row + rectHeight; ++i) {
                    for (int j = col; j < col + rectWidth; ++j) {
                        visited[i][j] = true;
                    }
                }

                // Add the rectangle shape to the vector
                rectangles.push_back(rectangle);
            }
        }
    }

    return rectangles;
}
*/

std::vector<sf::RectangleShape> Levels::createRectangles(const std::vector<std::vector<int>>& resultGrid) {
    int gridWidth = resultGrid[0].size();
    int gridHeight = resultGrid.size();

    std::vector<sf::RectangleShape> rectangles;

    // Check if the grid is empty
    if (gridWidth == 0 || gridHeight == 0) {
        return rectangles;
    }

    std::vector<std::vector<bool>> visited(gridHeight, std::vector<bool>(gridWidth, false));

    for (int row = 0; row < gridHeight; ++row) {
        for (int col = 0; col < gridWidth; ++col) {
            // If the cell is occupied and not visited, start forming a rectangle
            if (resultGrid[row][col] == 1 && !visited[row][col]) {
                int rectWidth = 1;
                int rectHeight = 1;

                // Expand horizontally to find the width of the rectangle
                while (col + rectWidth < gridWidth && resultGrid[row][col + rectWidth] == 1) {
                    ++rectWidth;
                }

                // Expand vertically to find the height of the rectangle
                while (row + rectHeight < gridHeight) {
                    bool validRow = true;
                    for (int i = col; i < col + rectWidth; ++i) {
                        if (resultGrid[row + rectHeight][i] != 1) {
                            validRow = false;
                            break;
                        }
                    }
                    if (validRow) {
                        ++rectHeight;
                    } else {
                        break;
                    }
                }

                // Create the rectangle shape
                sf::RectangleShape rectangle(sf::Vector2f(rectWidth * cellSize, rectHeight * cellSize));
                rectangle.setFillColor(sf::Color::Blue);
                rectangle.setPosition(col * cellSize, row * cellSize);

                // Mark the cells as visited
                for (int i = row; i < row + rectHeight; ++i) {
                    for (int j = col; j < col + rectWidth; ++j) {
                        visited[i][j] = true;
                    }
                }

                // Add the rectangle shape to the vector
                rectangles.push_back(rectangle);
            }
        }
    }

    return rectangles;
}