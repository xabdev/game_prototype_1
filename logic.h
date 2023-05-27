#pragma once
#include <vector>
#include <iostream>
#include "player.h"
#include "gridmanager.h"
#include "levels.h"
#include "enemies.h"
#include <array>
#include <limits>



class Logic {

    public:
        Logic(Player& player, Enemies& enemies);
        
        const int gridWidth = 160; // Number of grid cells horizontally
        const int gridHeight = 18; // Number of grid cells vertically
        const int cellSize = 40; // Size of each grid cell in pixels

        std::vector<sf::FloatRect> platformBounds;

        

        void gravityZ();
        void vJoy();
        void updatePlayerVelocity();
        void updateEnemyVelocity();
        void limitPlayerMovementToGrid();
        void preCalculatePlatformPositions();
        std::array<bool, 4> collisionSide(const std::vector<sf::FloatRect>& platformBounds);
        std::array<bool, 4> collisionSideEnemy(const std::vector<sf::FloatRect>& platformBounds);

        sf::Vector2i getPlayerCell() const;
        





    private:
        Player& player;
        Enemies& enemies;
        GridManager gridmanager;
        Levels levels;
        
        



};