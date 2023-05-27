#include "player.h"



std::vector<sf::RectangleShape> Player::createPlayer() {
    std::vector<sf::RectangleShape> playerCharacter;
    sf::RectangleShape player;
    player.setSize(sf::Vector2f(50, 135));
    player.setFillColor(sf::Color::Magenta);
    player.setPosition(500, 0);
    playerCharacter.push_back(player);
    return playerCharacter;
}