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
        float dashSpeed = 15.f;
        float jumpSpeed = -10.f;
        int health;
        int attack;
        int exp;
        int expReward = 10;
        int playerLEVEL = 1;
        int nextLevelExp = 100;
        int levelMultiplier = 2;
        float attackCD = 0.4;

        
        bool isJumping;
        bool isOnGround;
        bool isDashing = false;
        bool attacking = false;
        bool onCooldown = false;
        sf::Clock attackTiming;
        sf::Clock cooldownTimer;
        
        sf::Clock attackDurationTimer;
        sf::Clock dashCooldown;
        float attackDuration = .05;
        bool attackBOOL = false;
        
        
        std::vector<sf::RectangleShape> createPlayer();
        std::vector<sf::RectangleShape> createPlayerWeapon();
        void weaponAttack();

        std::array<bool, 4> collision;


        Player() {
            moveSpeed = 0.25f;
            health = 100;
            attack = 20;
            velocity = {0, 0};
            playerCharacter = createPlayer();
            playerCharacter = createPlayerWeapon();
            exp = 0;
        }

    private:

};