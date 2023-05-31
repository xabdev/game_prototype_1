#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "logic.h"
#include "player.h"
#include "levels.h"
#include "enemies.h"


class Graphics {

    public:

        Graphics(Logic& logic, Player& players, Enemies& enemies);

        void render(sf::RenderWindow& window);
        void cameraView(sf::RenderWindow& window, sf::View& view);
        void graphicsMain(sf::RenderWindow& window, sf::View& view);
        void updateBGSpritePosition(sf::View& view);
        void updateWeaponSpritePosition();
        void animatePlayerSprite();
        void animateEnemySprites();
        void animateLevelSprites();

        sf::Texture loadTexture(std::string filename);

        void createPlayerSprite();
        void createEnemySprites();
        void createLevelSprites();
        void createBackgroundSprite();
        void createWeaponSprite();



        sf::Sprite playerSprite;
        sf::Texture playerTexture;
        sf::Sprite weaponSprite;
        sf::Texture enemyTexture;
        std::vector<sf::Sprite> enemySprites;
        sf::Texture cellTexture;
        sf::Texture blockTexture;
        std::vector<sf::Sprite> cellSprites;
        sf::Texture background1Texture;
        sf::Sprite background1;




    private:
        
        Logic& logic;
        Player& player;
        Enemies& enemies;
        Levels levels;




};