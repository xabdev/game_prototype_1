#pragma once
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Player {

    public:
        
        std::vector<sf::RectangleShape> playerCharacter;
        sf::Vector2f velocity;
        float moveSpeed;
        float jumpSpeed = -10.f;
        int health;
        int attack;
        int exp;
        float attackCD = 0.5;

        
        bool isJumping;
        bool isOnGround;
        bool attacking = false;
        bool onCooldown = false;
        sf::Clock attackTiming;
        sf::Clock cooldownTimer;
        sf::Clock attackDurationTimer;
        float attackDuration = .05f;
        bool attackBOOL = false;
        
        
        std::vector<sf::RectangleShape> createPlayer();
        std::vector<sf::RectangleShape> createPlayerWeapon();
        void weaponAttack();

        std::array<bool, 4> collision;


        Player() {
            moveSpeed = 0.2f;
            health = 100;
            attack = 50;
            velocity = {0, 0};
            playerCharacter = createPlayer();
            playerCharacter = createPlayerWeapon();
            exp = 0;
        }

    private:

};