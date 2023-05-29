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
    //std::cout << imageDimension.x << "\n";
    imageDimension.y = image.getSize().y;
    //std::cout << imageDimension.y << "\n";
    return imageDimension;
}


std::vector<std::vector<int>> Levels::image2Grid() {
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


std::vector<std::vector<sf::Color>> Levels::grid2shapes() {
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
    std::vector<std::vector<sf::Color>> resultGrid = grid2shapes();
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