#include "player.h"



std::vector<sf::RectangleShape> Player::createPlayer() {
    std::vector<sf::RectangleShape> playerCharacter;
    sf::RectangleShape player;
    player.setSize(sf::Vector2f(76, 135));
    player.setFillColor(sf::Color::Transparent);
    player.setPosition(2500, 0);
    playerCharacter.push_back(player);
    return playerCharacter;
}

std::vector<sf::RectangleShape> Player::createPlayerWeapon() {
    sf::RectangleShape weapon;
    sf::Vector2f weaponSize = {200, 40};
    weapon.setSize(weaponSize);
    weapon.setScale(0, 0);
    weapon.setFillColor(sf::Color::Transparent);
    playerCharacter.push_back(weapon);
    return playerCharacter;
}

/*void Player::weaponAttack() {
    
    static sf::Clock attackTimer;
    static sf::Clock cooldownTimer;
    sf::Vector2f weaponScaleX = playerCharacter[1].getScale();
    int reverseWeapon = weaponScaleX.x * 2.f;

    // Check if the attack cooldown is over
    if (onCooldown && cooldownTimer.getElapsedTime().asSeconds() > attackCD) {
        onCooldown = false;
    }

    // Start the attack if the player is not attacking and not on cooldown
    
    if (!attacking && !onCooldown) {
        if (velocity.x > 0 || lastVelocity == 1) {

            attacking = true;
            attackAnimation = true;
            attackTiming.restart();
            
            attackTimer.restart();
            playerCharacter[1].setScale(sf::Vector2f(1, 1));
        }

        if (velocity.x < 0 || lastVelocity == -1) {
            attacking = true;
            attackTimer.restart();
            playerCharacter[1].setScale(sf::Vector2f(-1, 1));
        }
    }
    // End the attack after 1 second
    else if (attacking && attackTimer.getElapsedTime().asSeconds() > attackTime) {
        attacking = false;
        playerCharacter[1].setScale(sf::Vector2f(0, 0));
        cooldownTimer.restart();
        onCooldown = true;
    }
}*/


void Player::weaponAttack() {

    if (!attackBOOL && !attacking) {
        attackBOOL = true;
    }

}

