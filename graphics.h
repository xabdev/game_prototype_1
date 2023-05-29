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
        void updateSpritesPosition();
        void animatePlayerSprite();
        void animateWeapon();

        sf::Texture loadTexture(std::string filename);

        void createPlayerSprite();
        void createWeaponSprite();


        sf::Sprite playerSprite;
        sf::Texture playerTexture;
        sf::Sprite playerWeaponSprite;
        sf::Texture playerWeaponTexture;




    private:
        
        Logic& logic;
        Player& player;
        Enemies& enemies;
        Levels levels;




};