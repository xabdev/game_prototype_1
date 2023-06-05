#include "logic.h"
#include <SFML/System/Time.hpp>


Logic::Logic(Player& player, Enemies& enemies, Items& items) : gridmanager(gridWidth, gridHeight), player(player), enemies(enemies), items(items) {
    // Constructor initialization list, initializes the reference member
    preCalculatePlatformPositions();

}


void Logic::gravityZ() {
    
    const float Gravity = 0.9f;
    player.velocity.y += Gravity; 
    player.playerCharacter[0].move(player.velocity);


    for (size_t i = 0; i < enemies.enemies.size(); i++) {
        if (enemies.enemies[i].getPosition().x > -950 && enemies.enemies[i].getPosition().y < 900) {
            enemies.enemiesVelocities[i].y += Gravity;
            enemies.enemies[i].move(enemies.enemiesVelocities[i]);
        }
    }

    for (int i = 0; i < items.expShapes.size(); i++) {
        if (items.expShapes[i].getPosition().x > -200) {
            items.itemVelocities[i].y += Gravity;
            items.expShapes[i].move(items.itemVelocities[i]);
        }

    }
}


float Logic::randNum(float start, float end) {
  static std::random_device rd;
  static std::mt19937 engine(rd());
  std::uniform_real_distribution<float> dist(start, end);
  float rand = dist(engine);
  return rand;
}


void Logic::vJoy() {

    player.isOnGround = player.collision[0];

    if (player.isJumping && player.isOnGround) {
        player.isJumping = false;
    }

    if (player.isOnGround) {
        player.isDashing = false;
    }



    // Get the intended movement direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player.velocity.x -= player.moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player.velocity.x += player.moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!player.isJumping && player.isOnGround) {
            // Start jumping
            player.isJumping = true;
            player.velocity.y = player.jumpSpeed;
        } else { player.isJumping = false; }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) && !player.onCooldown) {
        player.weaponAttack();
        weaponCollision();
    }

    /*if (player.dashCooldown.getElapsedTime().asSeconds() > 1.5) {
        player.isDashing = false;
    }*/
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (!player.isOnGround && !player.isDashing && player.dashCooldown.getElapsedTime().asSeconds() > 0.5) {
            player.dashCooldown.restart();
            player.isDashing = true;
            player.velocity.x -= player.dashSpeed;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (!player.isOnGround && !player.isDashing && player.dashCooldown.getElapsedTime().asSeconds() > 0.5) {
            player.dashCooldown.restart();
            player.isDashing = true;
            player.velocity.x += player.dashSpeed;
        }
    }


    updatePlayerVelocity();
    player.velocity.x *= 0.90f;
    //Position player weapon
    player.playerCharacter[1].setPosition(player.playerCharacter[0].getPosition().x + player.playerCharacter[0].getSize().x / 2, player.playerCharacter[0].getPosition().y - 25);
}


void Logic::debugKeys() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        std::cout << player.playerCharacter[0].getPosition().x << "\n"; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        std::exit(0);
    }

}


void Logic::updatePlayerVelocity() {
    
    //limitPlayerMovementToGrid();
    player.playerCharacter[0].move(player.velocity);
    player.collision = collisionSide(platformBounds);
    
    
}


void Logic::gameOver() {

    if (gameover) {

        restart = true;
        items.restartItems();
        enemies.restartEnemies();
        numberOfEnemiesKilled = 0;
        player.health += 100;
        player.playerCharacter[0].setPosition(1600, 0);
        gameover = false;
    }
}


void Logic::comboCounter() {
    
    std::cout << player.comboCounter << "\n";

    if (player.comboCounterTimer.getElapsedTime().asSeconds() < 3.0f) {
        player.comboCounter++;
        player.comboCounterTimer.restart();
    }
}

void Logic::comboCounterReset() {

    if (player.comboCounterTimer.getElapsedTime().asSeconds() > 3.05f) {
        player.comboCounterTimer.restart();
        player.comboCounter = 0;
    }
}



void Logic::playerLevelUp() {

    if (player.exp >= player.nextLevelExp) {
        player.playerLEVEL++;
        player.nextLevelExp *= player.levelMultiplier;
        player.expReward += 5;
        std::cout << "Player Level: " << player.playerLEVEL << " current xp: " << player.exp << " next level: " << player.nextLevelExp << "\n";

    }
}



void Logic::playerDamaged() {

    for (size_t i = 0; i < enemies.enemies.size(); ++i) {
        if (enemies.enemiesHealth[i] > 0) {
            if (player.playerCharacter[0].getGlobalBounds().intersects(enemies.enemies[i].getGlobalBounds()) && !player.isDashing) {
                
                if (enemies.postHitInvincibility[i].getElapsedTime().asSeconds() > 0.1) {
                    player.comboCounter = 0;
                    player.health -= enemies.attack;
                    enemies.postHitInvincibility[i].restart();
                }
                
                
                enemies.enemiesVelocities[i].x *= 0.1;
                enemies.isEnemyHittingPlayer[i] = true;
            
                        
                if (player.health < 0) {
                    gameover = true;
                }

            } else { 
                enemies.isEnemyHittingPlayer[i] = false;                   
            }
        }
    }
}



void Logic::playerAttack() {
    
    // Check if the attack cooldown is over
    if (player.onCooldown && player.cooldownTimer.getElapsedTime().asSeconds() > player.attackCD) {
        player.onCooldown = false;
    }

    // Start the attack if the player is not attacking and not on cooldown
    if (!player.attacking && !player.onCooldown && player.attackBOOL) {
        player.attacking = true;
        player.attackTiming.restart();
        if (std::signbit(player.velocity.x)) {
            player.playerCharacter[1].setScale(-1.f, 1.f); // Reverse X scale
        } else if (player.velocity.x > 0) {
            player.playerCharacter[1].setScale(1.f, 1.f);
        }
    }

    // End the attack after the specified attack duration
    else if (player.attacking && player.attackDurationTimer.getElapsedTime().asSeconds() > player.attackDuration) {
        player.attacking = false;
        player.playerCharacter[1].setScale(0.f, 0.f);
        player.cooldownTimer.restart();
        player.onCooldown = true;
        player.attackBOOL = false;
        player.attackDurationTimer.restart();
    }
}


void Logic::weaponCollision() {
    float pushForce = 20.0f;
    

    for (size_t i = 0; i < enemies.enemies.size(); ++i) {

        if (player.playerCharacter[1].getGlobalBounds().intersects(enemies.enemies[i].getGlobalBounds())) {
            enemyDamaged(i, player.attack);

            if (enemies.enemiesHealth[i] > 0) {
                sf::Vector2f pushDirection = enemies.enemies[i].getPosition() - player.playerCharacter[1].getPosition();
                pushDirection = sf::Vector2f(pushDirection.x / std::abs(pushDirection.x), pushDirection.y / std::abs(pushDirection.y));

                enemies.enemies[i].move(pushDirection.x * pushForce, 0);
            }
        }
    }
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



void Logic::preCalculatePlatformPositions() {
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
                player.velocity.x *= 0.90f;
                collisionSide[3] = true;
            }
            else if (rightOverlap >= 0 && rightOverlap < topOverlap && rightOverlap < bottomOverlap && rightOverlap < leftOverlap) {
                player.playerCharacter[0].move(rightOverlap, 0);
                player.velocity.x *= 0.90f;
                collisionSide[1] = true;
            }
        }
    }

    return collisionSide;
}


sf::Vector2f Logic::calculateDistances(int enemyIndex, const sf::FloatRect& platformBounds) {
    sf::Vector2f distances; // distances.x for right edge, distances.y for left edge
    const sf::RectangleShape& enemy = enemies.enemies[enemyIndex];
    // Calculate bottom center position of the enemy
    sf::Vector2f enemyBottomCenter(enemy.getPosition().x + enemy.getSize().x / 2.f, enemy.getPosition().y + enemy.getSize().y);
    // Calculate distance from right edge
    distances.x = platformBounds.left + platformBounds.width - enemyBottomCenter.x;
    // Calculate distance from left edge
    distances.y = enemyBottomCenter.x - platformBounds.left;
    //std::cout << "X: " << distances.x << " Y: " << distances.y << "\n";
    return distances;
}


void Logic::enemyJump(int index) {

    float jumpPower = -13.5f;

    enemies.enemiesVelocities[index].y = jumpPower;
}


std::vector<std::vector<bool>> Logic::enemyCollisionSide() {
    std::vector<std::vector<bool>> collisionSide(enemies.enemies.size(), std::vector<bool>(4, false));
    
    for (int i = 0; i < enemies.enemies.size(); i++) {
        
        if (enemies.isEnemySolid[i] == true) {

         for (auto& platform : platformBounds) {
            float shapeTop = platform.top;
            float shapeBottom = platform.top + platform.height;
            float shapeLeft = platform.left;
            float shapeRight = platform.left + platform.width;
            
                if (enemies.enemies[i].getGlobalBounds().intersects(platform)) {
                    float enemyTop = enemies.enemies[i].getPosition().y;
                    float enemyBottom = enemies.enemies[i].getPosition().y + enemies.enemies[i].getSize().y;
                    float enemyLeft = enemies.enemies[i].getPosition().x;
                    float enemyRight = enemies.enemies[i].getPosition().x + enemies.enemies[i].getSize().x;

                    float topOverlap = enemyBottom - shapeTop;
                    float bottomOverlap = shapeBottom - enemyTop;
                    float leftOverlap = enemyRight - shapeLeft;
                    float rightOverlap = shapeRight - enemyLeft;

                    if (std::min({ topOverlap, bottomOverlap, leftOverlap, rightOverlap }) > 0.f) {
                        if (topOverlap < bottomOverlap && topOverlap < leftOverlap && topOverlap < rightOverlap) {
                            //Tocando el piso
                            enemies.enemies[i].setPosition(enemies.enemies[i].getPosition().x, shapeTop - enemies.enemies[i].getSize().y);
                            enemies.enemiesVelocities[i].y = 0;
                            collisionSide[i][2] = true;
                        
                            sf::Vector2f edge = calculateDistances(i, platform);
                            if (edge.x < 0.f) {
                                enemyJump(i);
                            }
                            if (edge.y < 0.f) {
                                enemyJump(i);
                            }

                        } else if (bottomOverlap < topOverlap && bottomOverlap < leftOverlap && bottomOverlap < rightOverlap) {
                            //Tocando el techo
                            enemies.enemies[i].setPosition(enemies.enemies[i].getPosition().x, shapeBottom);
                            enemies.enemiesVelocities[i].y = 0;
                            collisionSide[i][0] = true; 

                        } else if (leftOverlap < topOverlap && leftOverlap < bottomOverlap && leftOverlap < rightOverlap) {
                            //Tocando la derecha
                            enemies.enemies[i].setPosition(shapeLeft - enemies.enemies[i].getSize().x, enemies.enemies[i].getPosition().y);
                            //shapeVelocities[i].x = 0;
                            collisionSide[i][3] = true;

                        } else if (rightOverlap < topOverlap && rightOverlap < bottomOverlap && rightOverlap < leftOverlap) {
                            //Tocando la izquierda
                            enemies.enemies[i].setPosition(shapeRight, enemies.enemies[i].getPosition().y);
                            //shapeVelocities[i].x = 0;
                            collisionSide[i][1] = true;
                        }
                    }
                }
            }
        }
    }
    return collisionSide;
}


void Logic::enemyCollisionWithSelf() {
    float pushForce = 50.0f;

    
    
    for (size_t i = 0; i < enemies.enemies.size(); ++i) {
        if (!enemies.isEnemySolid[i] && enemies.enemiesVelocities[i].x != 0 && enemies.enemies[i].getPosition().y < 900) {
            
            sf::Vector2f pushDirection = enemies.enemies[i].getPosition() - player.playerCharacter[0].getPosition();
            pushDirection = sf::Vector2f(pushDirection.x / std::abs(pushDirection.x), pushDirection.y / std::abs(pushDirection.y));

    
            for (size_t j = i + 1; j < enemies.enemies.size(); ++j) {
                if (enemies.isEnemySolid[j]) {
                    if (enemies.enemies[i].getGlobalBounds().intersects(enemies.enemies[j].getGlobalBounds())) {
                        if (!enemies.hitStatus[j]) {
                            enemies.enemies[j].move(pushDirection.x * pushForce, 0);
                        }
                        enemyDamaged(j, enemies.enemyCollisionDamage);
                    }
                }
            }
        } 
    }
}


void Logic::enemiesRespawner() {
    static sf::Clock timer;
    static sf::Clock decreaseTimer;
    sf::Time elapsed = timer.getElapsedTime();
    sf::Time decreaseElapsed = decreaseTimer.getElapsedTime();
    static int respawn;
    static float respawn_time = 5.0f;
    if (gameover) {
        respawn = 0;
        respawn_time = 5.0;
        decreaseTimer.restart();
    }
        
    static bool spawnRight = true;

    if (respawn < enemies.enemies.size() - 5) {

        if (elapsed.asSeconds() > respawn_time) { 
            // Check if player's position is less than 700
            /*if (player.playerCharacter[0].getPosition().x < 1200) {
                spawnRight = true; // Always spawn from the right
            }*/
            if (player.playerCharacter[0].getPosition().x > 11500) {
                spawnRight = false; // Always spawn from the left
            }

            // Calculate the position offset based on the spawn direction
            float offsetX = spawnRight ? 1100.0f : -1100.0f;

            float offsetY = player.playerCharacter[0].getPosition().y - enemies.enemies[0].getSize().y;


            offsetX += randNum(0.f, 150.f);
            enemies.isEnemySolid[respawn] = true;
            enemies.enemies[respawn].setPosition(player.playerCharacter[0].getPosition().x + offsetX + randNum(0, 250), randNum(0.0, offsetY));
            enemies.enemyAnimationTimer[respawn].restart();
            respawn++;
            /*offsetX += randNum(0.f, 150.f);
            enemies.enemies[respawn].setPosition(player.playerCharacter[0].getPosition().x + offsetX + randNum(0, 250), randNum(0.0, offsetY));
            respawn++;
            offsetX += randNum(0.f, 150.f);
            enemies.enemies[respawn].setPosition(player.playerCharacter[0].getPosition().x + offsetX + randNum(0, 250), randNum(0.0, offsetY));
            respawn++;*/

            timer.restart();

            // Toggle the spawn direction for the next enemy
            spawnRight = !spawnRight;
        }

        if (decreaseElapsed.asSeconds() > 15.0f && respawn_time > 0.5) {
            respawn_time -= 0.50f;
            //std::cout << respawn_time << "\n";
            decreaseTimer.restart();
        }
    }
}


void Logic::itemRespawner(int index) {

    static int rspwn = 0;

    if (rspwn < items.expShapes.size() - 3) {
        
        items.expShapes[rspwn].setPosition(enemies.enemies[index].getPosition().x - randNum(0, 100), enemies.enemies[index].getPosition().y);
        items.itemVelocities[rspwn].y = randNum(-7, -2);

        rspwn++;
        items.expShapes[rspwn].setPosition(enemies.enemies[index].getPosition().x - randNum(0, 100), enemies.enemies[index].getPosition().y);
        items.itemVelocities[rspwn].y = randNum(-7, -2);
        rspwn++;
        items.expShapes[rspwn].setPosition(enemies.enemies[index].getPosition().x - randNum(0, 100), enemies.enemies[index].getPosition().y);
        items.itemVelocities[rspwn].y = randNum(-7, -2);
        rspwn++;
    }
}




void Logic::itemCollision() {
 
    for (auto& shape : items.expShapes) {
        if (player.playerCharacter[0].getGlobalBounds().intersects(shape.getGlobalBounds())) {
            player.exp += player.expReward;
            shape.setPosition(-500, 500);
        }
    }
}


void Logic::itemCollisionWithLevel() {

    for (int i = 0; i < items.expShapes.size(); i++) {
        
        if (items.expShapes[i].getPosition().x > -200) {

            for (auto& platform : platformBounds) {
                float shapeTop = platform.top;

                if (items.expShapes[i].getGlobalBounds().intersects(platform/*.getGlobalBounds()*/)) {
                    items.expShapes[i].setPosition(items.expShapes[i].getPosition().x, shapeTop - items.expShapes[i].getSize().y);
                    items.itemVelocities[i].y = 0;
                    
                }
            }
        }
    }
}





void Logic::enemyDamaged(int index, int attack) {

    sf::Vector2f pushDirection = enemies.enemies[index].getPosition() - player.playerCharacter[0].getPosition();
    pushDirection = sf::Vector2f(pushDirection.x / std::abs(pushDirection.x), pushDirection.y / std::abs(pushDirection.y));
    
    if (enemies.hitCooldown[index].getElapsedTime().asSeconds() > 0.05) {
        enemies.hitStatus[index] = false;
    }

    if (enemies.enemiesHealth[index] <= 0 && enemies.isEnemySolid[index]) {

        enemies.isEnemySolid[index] = false;
        numberOfEnemiesKilled++;
        enemies.enemiesVelocities[index].x = pushDirection.x * 0.1;
        itemRespawner(index);
        enemies.isEnemyHittingPlayer[index] = false;
        enemies.enemiesVelocities[index].y = enemies.enemyDeathJumpSpeed;
    }

    if (enemies.enemiesHealth[index] < 0 && !enemies.isEnemySolid[index]) {
        enemies.enemiesVelocities[index].y = enemies.enemyDeathJumpSpeed;
        enemies.enemiesVelocities[index].x = pushDirection.x * 20;
    }

        
    

    if (enemies.hitCooldown[index].getElapsedTime().asSeconds() > 0.06 && !enemies.hitStatus[index]) {
        comboCounter();
        enemies.hitStatus[index] = true;
        enemies.enemiesVelocities[index].x *= 0.1;
        enemies.enemiesHealth[index] -= attack;
        enemies.hitCooldown[index].restart();
    }
}




sf::Vector2f Logic::locatePlayerWithIndexV2(int index) {

    const float enemyRange = 2000.0f;
    sf::Vector2f enemyToPlayer = player.playerCharacter[0].getPosition() - enemies.enemies[index].getPosition();
        float distance = std::hypot(enemyToPlayer.x, enemyToPlayer.y);
        if (distance <= enemyRange && std::abs(enemyToPlayer.y) <= enemyRange) {
            enemyToPlayer /= distance;

            // Update only the X component of the enemy velocity based on the player's position
            enemies.enemiesVelocities[index].x = enemyToPlayer.x * enemies.enemyTopSpeed;
        }
    
        /*if (enemies.enemiesHealth[index] <= 0) {
                enemies.enemiesVelocities[index].x = 0;
        }*/

        if (enemies.enemiesHealth[index] <= 25) {
                enemies.enemiesVelocities[index].x = enemyToPlayer.x * enemies.enemyAlmostDeadSpeed;
        }

    return enemyToPlayer;
}


void Logic::enemiesAI() {
    enemies.collision = enemyCollisionSide();
    enemyCollisionWithSelf();

    for (size_t i = 0; i < enemies.collision.size(); i++) {

        //villereada 2009
        if (enemies.hitCooldown[i].getElapsedTime().asSeconds() > 0.15) {
        enemies.hitStatus[i] = false;
        }
        //fin de villereada 2009

        if (enemies.collision[i][2]) {
            //std::cout << "Enemy: " << i << " touching floor " << enemies.collision[i][2] << "\n";
            locatePlayerWithIndexV2(i);

        }
        if (enemies.collision[i][3]) {
            enemyJump(i);
            //std::cout << "Enemy: " << i << " tocando la derecha " << enemies.collision[i][3] << std::endl;
        }
        if (enemies.collision[i][1]) {
            enemyJump(i);

            //std::cout << "Enemy: " << i << " tocando la izquierda " << enemies.collision[i][1] << std::endl;
        }
        
    }
}


void Logic::logicMain() {

    
    gravityZ();
    enemiesAI();
    comboCounterReset();
    
    playerDamaged();
    enemiesRespawner();
    gameOver();
    itemCollision();
    itemCollisionWithLevel();
    playerAttack();
    playerLevelUp();
    vJoy();
    debugKeys();
    
}