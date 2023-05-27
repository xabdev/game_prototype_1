#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "logic.h"
#include "player.h"
#include "levels.h"


class Graphics {

    public:

        Graphics(Logic& logic, Player& players);

        void render(sf::RenderWindow& window);
        void cameraView(sf::RenderWindow& window, sf::View& view);
        sf::Image loadImage();
        sf::Vector2f getImageDimensions(sf::Image image);
        std::vector<std::vector<int>> translateImage();







    private:
        
        Logic& logic;
        Player& player;
        Levels levels;




};