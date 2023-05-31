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

std::vector<bool> Enemies::setEnemiesHitStatus() {

    bool hit = false;
    for (int i = 0; i < enemies.size(); i++) {
        hitStatus.push_back(hit);
    }

    return hitStatus;
}

std::vector<sf::Clock> Enemies::setEnemiesHitCooldown() {
    sf::Clock timer;
    for (int i = 0; i < enemies.size(); i++) {
        sf::Clock timer;
        hitCooldown.push_back(timer);
    }

    return hitCooldown;
}


std::vector<sf::RectangleShape> Enemies::createEnemies() {
    sf::RectangleShape enemy;
    for (int i = 0; i < numEnemies; i++) {
        enemy.setSize(sf::Vector2f(90, 180));
        enemy.setFillColor(sf::Color::Transparent);
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

void Enemies::enemyDamaged(int index) {

    if (hitCooldown[index].getElapsedTime().asSeconds() > 0.05) {
        hitStatus[index] = false;
    }

    if (enemiesHealth[index] <= 0) {
        enemies[index].setPosition(-200, 0);
        enemiesHealth[index] = 100;
        //levelUP(50);
    }

    if (hitCooldown[index].getElapsedTime().asSeconds() > 0.06 && !hitStatus[index]) {
        hitStatus[index] = true;
        std::cout << "Enemy: " << index << " health: " << enemiesHealth[index] << "\n";
        enemiesHealth[index] -= 50;
        std::cout << "Enemy: " << index << " health: " << enemiesHealth[index] << "\n";
        std::cout << hitCooldown[index].getElapsedTime().asSeconds() << "\n";
        hitCooldown[index].restart();
    }


    
}