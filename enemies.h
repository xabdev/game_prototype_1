#pragma once
#include <SFML/Graphics.hpp>

class Enemies {

    public:
        std::vector<sf::RectangleShape> createEnemies();
        std::vector<sf::Vector2f> setEnemiesVelocity();
        std::vector<int> setEnemiesHealth();
        void restartEnemies();
        std::vector<sf::RectangleShape> enemies;
        std::vector<sf::Vector2f> enemiesVelocities;
        std::vector<int> enemiesHealth;
        std::vector<std::vector<bool>> collision;
        
        const float enemyTopSpeed = 2.5f;
        const float enemyAlmostDeadSpeed = 5.f;
        const float enemyJumpSpeed = -8.5f;
        
        

        Enemies() {
            enemies = createEnemies();
            enemiesVelocities = setEnemiesVelocity();
            enemiesHealth = setEnemiesHealth();
            
        }



    private:
        int numEnemies = 100;
        int enemyHealth = 100;



};