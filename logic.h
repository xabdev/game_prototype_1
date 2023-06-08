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
#include "items.h"



class Logic {

    public:
        Logic(Player& player, Enemies& enemies, Items& items);
        
        const int gridWidth = 320; // Number of grid cells horizontally
        const int gridHeight = 18; // Number of grid cells vertically
        const int cellSize = 40; // Size of each grid cell in pixels

        std::vector<sf::FloatRect> platformBounds;

        void debugKeys();
        float randNum(float start, float end);

        void gravityZ();
        void vJoy();
        void gameOver();
        void comboCounter();
        void comboCounterReset();
        void updatePlayerVelocity();
        void updateEnemyVelocity();
        void limitPlayerMovementToGrid();
        void preCalculatePlatformPositions();
        void playerDamaged();
        void playerAttack();
        void attackHitBoxManager();
        void attackStart();
        void attackEnd();
        void playerLevelUp();
        void weaponCollision();
        void checkWeaponCollision(sf::RectangleShape weapon);
        void itemCollision();
        void itemCollisionWithLevel();
        std::array<bool, 4> collisionSide(const std::vector<sf::FloatRect>& platformBounds);

        int numberOfEnemiesKilled = 0;
        bool restart = false;
        bool gameover = false;


        std::vector<std::vector<bool>> enemyCollisionSide();
        void enemyCollisionWithSelf();
        void enemiesRespawner();
        void enemiesAI();
        void enemyDamaged(int index, int attack);
        void enemyWallBounce();
        void itemRespawner(int index);
        sf::Vector2f locatePlayerWithIndexV2(int index);
        sf::Vector2f calculateDistances(int enemyIndex, const sf::FloatRect& platformBounds);
        void enemyJump(int index);

        sf::Vector2i getPlayerCell() const;



        void logicMain();
        





    private:
        Player& player;
        Enemies& enemies;
        Items& items;
        GridManager gridmanager;
        Levels levels;
        
        



};