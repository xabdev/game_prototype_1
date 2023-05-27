#include "logic.h"


Logic::Logic(Player& player) : gridmanager(gridWidth, gridHeight), player(player) {
    // Constructor initialization list, initializes the reference member

}

void Logic::gravityZ() {
    const float Gravity = 0.9f;
    player.velocity.y += Gravity; 
    //player.playerCharacter[0].move(player.velocity);

}




void Logic::vJoy() {


    player.isOnGround = player.collision[0];

    if (player.isJumping && player.isOnGround) {
        player.isJumping = false;
    }



    // Get the intended movement direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player.velocity.x -= player.moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player.velocity.x += player.moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player.velocity.y -= player.moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.velocity.y += player.moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!player.isJumping && player.isOnGround) {
            // Start jumping
            player.isJumping = true;
            player.velocity.y = player.jumpSpeed;
        } else { player.isJumping = false; }
    }
    
    
    
    
    
    updatePlayerVelocity();
    
    
    
    
}


void Logic::updatePlayerVelocity() {

    

    // Apply drag to the player's velocity
    player.velocity.x *= 0.75;

    player.playerCharacter[0].move(player.velocity);
    //gravityZ();

    limitPlayerMovementToGrid();
    player.collision = collisionSide(platformBounds);
    
    
    
    
}



void Logic::limitPlayerMovementToGrid() {
    sf::Vector2f pos = player.playerCharacter[0].getPosition();
    sf::Vector2f newPosition = pos + player.velocity;

    // Adjust the movement if it exceeds the grid boundaries
    if (newPosition.x < 0)
        newPosition.x = 0;
    if (newPosition.x + player.playerCharacter[0].getSize().x > gridWidth * cellSize) {
        // Use pre-defined maximum X position
        float maxX = gridWidth * cellSize - player.playerCharacter[0].getSize().x;
        newPosition.x = std::max(maxX, pos.x);
    }
    if (newPosition.y < 0)
        newPosition.y = 0;
    if (newPosition.y + player.playerCharacter[0].getSize().y > gridHeight * cellSize) {
        // Use pre-defined maximum Y position
        float maxY = gridHeight * cellSize - player.playerCharacter[0].getSize().y;
        newPosition.y = std::max(maxY, pos.y);
    }

    // Update the player's position
    player.playerCharacter[0].setPosition(newPosition);

    // Adjust the position further if it exceeds the grid boundaries
    sf::FloatRect playerBounds = player.playerCharacter[0].getGlobalBounds();
    sf::Vector2f playerSize = player.playerCharacter[0].getSize();

    if (playerBounds.left < 0) {
        newPosition.x = 0;
        player.playerCharacter[0].setPosition(newPosition);
    }
    if (playerBounds.left + playerSize.x > gridWidth * cellSize) {
        float maxX = gridWidth * cellSize - playerSize.x;
        newPosition.x = maxX;
        player.playerCharacter[0].setPosition(newPosition);
    }
    if (playerBounds.top < 0) {
        newPosition.y = 0;
        player.playerCharacter[0].setPosition(newPosition);
    }
    if (playerBounds.top + playerSize.y > gridHeight * cellSize) {
        float maxY = gridHeight * cellSize - playerSize.y;
        newPosition.y = maxY;
        player.playerCharacter[0].setPosition(newPosition);
    }
}






sf::Vector2i Logic::getPlayerCell() const {
    sf::Vector2f playerPosition = player.playerCharacter[0].getPosition();
    int cellX = static_cast<int>(playerPosition.x) / cellSize;
    int cellY = static_cast<int>(playerPosition.y) / cellSize;
    return sf::Vector2i(cellX, cellY);
}



void Logic::preCalculatePlatformPositions()
{
    for (const sf::RectangleShape& platform : levels.level) {
        sf::FloatRect platformRect = platform.getGlobalBounds();
        platformBounds.push_back(platformRect);
    }
}




std::array<bool, 4> Logic::collisionSide(const std::vector<sf::FloatRect>& platformBounds) {
    std::array<bool, 4> collisionSide{ false, false, false, false };
    const sf::FloatRect playerBounds = player.playerCharacter[0].getGlobalBounds();
    const sf::Vector2f playerPosition = player.playerCharacter[0].getPosition();
    const sf::Vector2f playerSize = player.playerCharacter[0].getSize();

    for (const auto& elementBounds : platformBounds) {
        if (playerBounds.intersects(elementBounds)) {
            const float playerTop = playerPosition.y;
            const float playerBottom = playerPosition.y + playerSize.y;
            const float playerLeft = playerPosition.x;
            const float playerRight = playerPosition.x + playerSize.x;

            const float shapeTop = elementBounds.top;
            const float shapeBottom = elementBounds.top + elementBounds.height;
            const float shapeLeft = elementBounds.left;
            const float shapeRight = elementBounds.left + elementBounds.width;

            const float topOverlap = playerBottom - shapeTop;
            const float bottomOverlap = shapeBottom - playerTop;
            const float leftOverlap = playerRight - shapeLeft;
            const float rightOverlap = shapeRight - playerLeft;

            if (topOverlap >= 0 && topOverlap < bottomOverlap && topOverlap < leftOverlap && topOverlap < rightOverlap) {
                player.playerCharacter[0].move(0, -topOverlap);
                player.velocity.y = 0;
                collisionSide[0] = true;
            }
            else if (bottomOverlap >= 0 && bottomOverlap < topOverlap && bottomOverlap < leftOverlap && bottomOverlap < rightOverlap) {
                player.playerCharacter[0].move(0, bottomOverlap);
                player.velocity.y = 0;
                collisionSide[2] = true;
            }
            else if (leftOverlap >= 0 && leftOverlap < topOverlap && leftOverlap < bottomOverlap && leftOverlap < rightOverlap) {
                player.playerCharacter[0].move(-leftOverlap, 0);
                player.velocity.x = 0;
                collisionSide[3] = true;
            }
            else if (rightOverlap >= 0 && rightOverlap < topOverlap && rightOverlap < bottomOverlap && rightOverlap < leftOverlap) {
                player.playerCharacter[0].move(rightOverlap, 0);
                player.velocity.x = 0;
                collisionSide[1] = true;
            }
        }
    }

    return collisionSide;
}


