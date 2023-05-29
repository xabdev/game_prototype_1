#include "enemies.h"


std::vector<sf::Vector2f> Enemies::setEnemiesVelocity() {
    sf::Vector2f enemyVelocity = {0, 0};
    for (int i = 0; i < numEnemies; i++) {
        enemiesVelocities.push_back(enemyVelocity);
    }
    return enemiesVelocities;
}

std::vector<int> Enemies::setEnemiesHealth() {
    int enemyHealth = 100;
    for (int i = 0; i < numEnemies; i++) {
        enemiesHealth.push_back(enemyHealth);
    }
    return enemiesHealth;
}


std::vector<sf::RectangleShape> Enemies::createEnemies() {
    sf::RectangleShape enemy;
    for (int i = 0; i < numEnemies; i++) {
        enemy.setSize(sf::Vector2f(50, 110));
        enemy.setFillColor(sf::Color::Red);
        enemy.setOutlineColor(sf::Color::Black);
        enemy.setOutlineThickness(1.0f);
        enemy.setPosition(-200, 200);
        enemies.push_back(enemy);
    }
    return enemies;
}

void Enemies::restartEnemies() {

    enemies = createEnemies();
    enemiesVelocities = setEnemiesVelocity();
    enemiesHealth = setEnemiesHealth();
}