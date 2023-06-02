#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemies {

    public:
        std::vector<sf::RectangleShape> createEnemies();
        std::vector<sf::Vector2f> setEnemiesVelocity();
        std::vector<int> setEnemiesHealth();
        std::vector<bool> setEnemiesHitStatus();
        std::vector<sf::Clock> setEnemiesHitCooldown();
        std::vector<bool> setEnemiesMass();
        void restartEnemies();
        void resetEnemiesPosition();


        std::vector<sf::RectangleShape> enemies;
        std::vector<sf::Vector2f> enemiesVelocities;
        std::vector<int> enemiesHealth;
        std::vector<std::vector<bool>> collision;
        std::vector<bool> isEnemySolid;
        std::vector<bool> hitStatus;
        std::vector<sf::Clock> hitCooldown;
        

        const float enemyTopSpeed = 2.5f;
        const float enemyAlmostDeadSpeed = 5.f;
        const float enemyJumpSpeed = -8.5f;
        const float enemyDeathJumpSpeed = -11.5f;
        
        

        Enemies() {
            enemies = createEnemies();
            enemiesVelocities = setEnemiesVelocity();
            enemiesHealth = setEnemiesHealth();
            hitStatus = setEnemiesHitStatus();
            hitCooldown = setEnemiesHitCooldown();
            isEnemySolid = setEnemiesMass();
            
        }



    private:
        int numEnemies = 2000;
        int enemyHealth = 100;



};