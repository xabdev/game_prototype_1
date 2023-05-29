#pragma once
#include <vector>
#include <iostream>
#include "player.h"
#include "gridmanager.h"
#include "levels.h"
#include "enemies.h"
#include <array>
#include <limits>
#include <cmath>
#include <random>



class Logic {

    public:
        Logic(Player& player, Enemies& enemies);
        
        const int gridWidth = 320; // Number of grid cells horizontally
        const int gridHeight = 18; // Number of grid cells vertically
        const int cellSize = 40; // Size of each grid cell in pixels

        std::vector<sf::FloatRect> platformBounds;

        void debugKeys();

        void gravityZ();
        void vJoy();
        void updatePlayerVelocity();
        void updateEnemyVelocity();
        void limitPlayerMovementToGrid();
        void preCalculatePlatformPositions();
        void playerDamaged();
        void weaponCollision();
        std::array<bool, 4> collisionSide(const std::vector<sf::FloatRect>& platformBounds);


        std::vector<std::vector<bool>> enemyCollisionSide();
        void enemiesRespawner();
        void enemiesAI();
        sf::Vector2f locatePlayerWithIndexV2(int index);
        sf::Vector2f calculateDistances(int enemyIndex, const sf::FloatRect& platformBounds);
        void enemyJump(int index);

        sf::Vector2i getPlayerCell() const;



        void logicMain();
        





    private:
        Player& player;
        Enemies& enemies;
        GridManager gridmanager;
        Levels levels;
        
        



};