#pragma once
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>


class Player {

    public:
        
        std::vector<sf::RectangleShape> playerCharacter;
        sf::Vector2f velocity;
        float moveSpeed;
        float jumpSpeed = -10.f;
        int health;
        int attack;
        int exp;
        float attackCD = 0.7;
        float attackTime = 0.01;
        int lastVelocity = 1;
        
        bool isJumping;
        bool isOnGround;
        bool attacking = false;
        bool onCooldown = false;
        
        
        std::vector<sf::RectangleShape> createPlayer();
        std::vector<sf::RectangleShape> createPlayerWeapon();
        void weaponAttack();

        std::array<bool, 4> collision;


        Player() {
            moveSpeed = 0.7f;
            health = 100;
            attack = 50;
            velocity = {0, 0};
            playerCharacter = createPlayer();
            playerCharacter = createPlayerWeapon();
            exp = 0;
        }

    private:

};