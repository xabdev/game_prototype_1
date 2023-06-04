#include "player.h"



std::vector<sf::RectangleShape> Player::createPlayer() {
    std::vector<sf::RectangleShape> playerCharacter;
    sf::RectangleShape player;
    player.setSize(sf::Vector2f(76, 135));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(2500, 0);
    playerCharacter.push_back(player);
    return playerCharacter;
}

std::vector<sf::RectangleShape> Player::createPlayerWeapon() {
    sf::RectangleShape weapon;
    sf::Vector2f weaponSize = {180, 100};
    weapon.setSize(weaponSize);
    weapon.setScale(0, 0);
    weapon.setFillColor(sf::Color::Magenta);
    playerCharacter.push_back(weapon);
    return playerCharacter;
}


void Player::weaponAttack() {

    if (!attackBOOL && !attacking) {
        attackBOOL = true;
        attackDurationTimer.restart();
    }

}


