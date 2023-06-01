#include "items.h"


std::vector<sf::RectangleShape> Items::createExpItem() {
    sf::RectangleShape expShape;
    int item_num = 2000;

    for (int i = 0; i < item_num; i++) {
        expShape.setSize(sf::Vector2f(14.5, 25));
        expShape.setFillColor(sf::Color::Transparent);
        expShape.setPosition(-500, 200);
        expShapes.push_back(expShape);
    }

    return expShapes;
}

std::vector<sf::Vector2f> Items::setItemsVelocity() {
    sf::Vector2f itemVelocity = {0, 0};
    for (int i = 0; i < expShapes.size(); i++) {
        itemVelocities.push_back(itemVelocity);
    }
    return itemVelocities;
}