#pragma once
#include <SFML/Graphics.hpp>

class Enemies {

    public:
        std::vector<sf::RectangleShape> createEnemies();
        std::vector<sf::Vector2f> setEnemiesVelocity();
        std::vector<int> setEnemiesHealth();
        void restartEnemies();
        std::vector<sf::RectangleShape> enemies;
        std::vector<std::vector<bool>> collision;
        std::vector<std::vector<bool>> collisionWithSelf;
        std::vector<sf::Vector2f> enemiesVelocities;
        std::vector<int> enemiesHealth;
        const float enemyTopSpeed = 1.5f;
        const float enemyAlmostDeadSpeed = 3.f;
        const float enemyJumpSpeed = -12.0f;

        Enemies() {
            enemies = createEnemies();
            enemiesVelocities = setEnemiesVelocity();
            enemiesHealth = setEnemiesHealth();
        }



    private:
        int numEnemies = 2;
        int enemyHealth = 100;



};