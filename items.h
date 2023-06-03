#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Items {

    public:

        std::vector<sf::RectangleShape> createExpItem();
        std::vector<sf::Vector2f> setItemsVelocity();
        void restartItems();
        std::vector<sf::RectangleShape> expShapes;
        std::vector<sf::Vector2f> itemVelocities;

        Items() {
            expShapes = createExpItem();
            itemVelocities = setItemsVelocity();
        }


};