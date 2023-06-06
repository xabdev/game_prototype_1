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
        std::vector<bool> isEnemyHittingThePlayer();
        std::vector<bool> setEnemyComboable();
        std::vector<sf::Clock> setEnemiesAnimationTimer();
        std::vector<sf::Clock> setPostHitInvincibility();
 

        void resetEnemiesPosition();
        void restartEnemies();


        std::vector<sf::RectangleShape> enemies;
        std::vector<sf::Vector2f> enemiesVelocities;
        std::vector<int> enemiesHealth;
        std::vector<std::vector<bool>> collision;
        std::vector<bool> isEnemySolid;
        std::vector<bool> isEnemyComboable;
        std::vector<bool> hitStatus;
        std::vector<sf::Clock> hitCooldown;
        std::vector<bool> isEnemyHittingPlayer;
        std::vector<sf::Clock> enemyAnimationTimer;
        std::vector<sf::Clock> postHitInvincibility;

        

        const float enemyTopSpeed = 2.5f;
        const float enemyAlmostDeadSpeed = 5.f;
        const float enemyJumpSpeed = -8.5f;
        const float enemyDeathJumpSpeed = -15.f;

        int attack = 5;
        int enemyCollisionDamage = 15;
        
        

        Enemies() {
            enemies = createEnemies();
            enemiesVelocities = setEnemiesVelocity();
            enemiesHealth = setEnemiesHealth();
            hitStatus = setEnemiesHitStatus();
            hitCooldown = setEnemiesHitCooldown();
            isEnemySolid = setEnemiesMass();
            isEnemyHittingPlayer = isEnemyHittingThePlayer();
            enemyAnimationTimer = setEnemiesAnimationTimer();
            postHitInvincibility = setPostHitInvincibility();
            isEnemyComboable = setEnemyComboable();

            
        }



    private:
        int numEnemies = 2000;
        int enemyHealth = 100;



};