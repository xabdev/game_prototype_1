#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "logic.h"
#include "player.h"
#include "levels.h"
#include "enemies.h"
#include "items.h"


class Graphics {

    public:

        Graphics(Logic& logic, Player& players, Enemies& enemies, Items& items);

        void render(sf::RenderWindow& window);
        void showFPS();
        void loadingScreen(sf::RenderWindow& window);
        sf::Font loadFont();
        sf::Text formatText();
        std::vector<sf::Text> createText();
        void updateUIText(sf::View& view);
        void cameraView(sf::RenderWindow& window, sf::View& view);
        void graphicsMain(sf::RenderWindow& window, sf::View& view);
        void updateBGSpritePosition(sf::View& view);
        //void updateWeaponSpritePosition();
        void animatePlayerSprite();
        void animateAttackFrames(float attackDuration);
        void animateEnemySprites();
        void animateLevelSprites();
        void animateItemSprites();
        void updateUIElementsPosition(sf::View& view);

        sf::Texture loadTexture(std::string filename);

        void createPlayerSprite();
        void createEnemySprites();
        void createLevelSprites();
        void createBackgroundSprite();
        void createWeaponSprite();
        void createItemSprites();
        void createUIElements();


        sf::Font font;
        std::vector<sf::Text> texts;

        int framerate;



        sf::Sprite playerSprite;
        sf::Texture playerTexture;
        //sf::Sprite weaponSprite;
        sf::Texture enemyTexture;
        std::vector<sf::Sprite> enemySprites;
        sf::Texture cellTexture;
        sf::Texture blockTexture;
        std::vector<sf::Sprite> cellSprites;
        sf::Texture background1Texture;
        sf::Texture background2Texture;
        sf::Sprite background1;
        sf::Sprite background2;
        sf::Texture itemTexture;
        std::vector<sf::Sprite> itemSprites;


        std::vector<sf::RectangleShape> uiElements;




    private:
        
        Logic& logic;
        Player& player;
        Enemies& enemies;
        Items &items;
        Levels levels;




};