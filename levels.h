#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Levels {

    public:

        const int gridWidth = 160; // Number of grid cells horizontally
        const int gridHeight = 18; // Number of grid cells vertically
        const int cellSize = 40; // Size of each grid cell in pixels

        sf::Image loadImage();
        sf::Vector2f getImageDimensions(sf::Image image);
        std::vector<std::vector<int>> translateImage();
        std::vector<std::vector<int>> translateImage2();
        std::vector<std::vector<sf::Color>> translateImage3();
        std::vector<sf::RectangleShape> createLevel();
        //std::vector<sf::RectangleShape> mergeCellsToRectangles(const std::vector<std::vector<int>>& grid);
        std::vector<sf::RectangleShape> createRectangles(const std::vector<std::vector<int>>& resultGrid);

        std::vector<sf::RectangleShape> level;
        std::vector<std::vector<int>> levelGrid;

        Levels() {

            //levelGrid = translateImage();
            levelGrid = translateImage2();
            //level = createRectangles(levelGrid);
            level = createLevel();
            //level = mergeCellsToRectangles(levelGrid);

        }



    private:





};