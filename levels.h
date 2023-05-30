#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Levels {

    public:

        const int gridWidth = 320; // Number of grid cells horizontally
        const int gridHeight = 18; // Number of grid cells vertically
        const int cellSize = 40; // Size of each grid cell in pixels

        sf::Image loadImage();
        sf::Vector2f getImageDimensions(sf::Image image);
        std::vector<std::vector<int>> translateImage();
        std::vector<std::vector<int>> image2Grid();
        std::vector<std::vector<sf::Color>> grid2shapes();
        std::vector<sf::RectangleShape> createLevel();
        std::vector<sf::RectangleShape> createLevelShapes();
        
        std::vector<sf::RectangleShape> createRectangles(const std::vector<std::vector<int>>& resultGrid);

        std::vector<sf::RectangleShape> level;
        std::vector<sf::RectangleShape> levelShapes;
        std::vector<std::vector<int>> levelGrid;

        Levels() {


            levelGrid = image2Grid();

            levelShapes = createLevelShapes();
            
            level = createLevel();


        }



    private:





};