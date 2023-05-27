#pragma once
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

struct PlayerStats {




};



class Player {

    public:
        
        std::vector<sf::RectangleShape> playerCharacter;
        sf::Vector2f velocity;
        float moveSpeed;
        float jumpSpeed = -11.f;
        int health;
        int attack;
        
        bool isJumping;
        bool isOnGround;
        
        std::vector<sf::RectangleShape> createPlayer();

        std::array<bool, 4> collision;


        Player() {
            moveSpeed = 0.9f;
            health = 100;
            attack = 25;
            velocity = {0, 0};
            playerCharacter = createPlayer();
        }

    private:

};