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



std::vector<bool> Enemies::setEnemiesMass() {

    bool solid = false;
    for (int i = 0; i < enemies.size(); i++) {
        isEnemySolid.push_back(solid);
    }

    return isEnemySolid;
}


std::vector<bool> Enemies::isEnemyHittingThePlayer() {

    bool hit = false;
    for (int i = 0; i < enemies.size(); i++) {
        isEnemyHittingPlayer.push_back(hit);
    }

    return isEnemyHittingPlayer;
}



std::vector<sf::Clock> Enemies::setEnemiesHitCooldown() {
    sf::Clock timer;
    for (int i = 0; i < enemies.size(); i++) {
        sf::Clock timer;
        hitCooldown.push_back(timer);
    }

    return hitCooldown;
}

std::vector<sf::Clock> Enemies::setEnemiesAnimationTimer() {
    sf::Clock timer;
    for (int i = 0; i < enemies.size(); i++) {
        sf::Clock timer;
        enemyAnimationTimer.push_back(timer);
    }

    return enemyAnimationTimer;
}



std::vector<sf::RectangleShape> Enemies::createEnemies() {
    sf::RectangleShape enemy;
    for (int i = 0; i < numEnemies; i++) {
        enemy.setSize(sf::Vector2f(70, 180));
        enemy.setFillColor(sf::Color::Red);
        enemy.setPosition(-1000, 200);
        enemies.push_back(enemy);
    }
    return enemies;
}

void Enemies::resetEnemiesPosition() {

    for (auto& enemy : enemies) {
        enemy.setPosition(-1000, 200);
    }
}


void Enemies::restartEnemies() {


    resetEnemiesPosition();
    enemiesVelocities.clear(); 
    enemiesHealth.clear();
    hitCooldown.clear();
    hitStatus.clear();
    isEnemySolid.clear();
    enemiesVelocities = setEnemiesVelocity();
    enemiesHealth = setEnemiesHealth();
    hitStatus = setEnemiesHitStatus();
    hitCooldown = setEnemiesHitCooldown();
    isEnemySolid = setEnemiesMass();

}