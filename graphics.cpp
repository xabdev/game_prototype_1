#include "graphics.h"


Graphics::Graphics(Logic& logic, Player& player, Enemies& enemies, Items& items) : logic(logic), player(player), enemies(enemies), items(items) {

    playerTexture = loadTexture("img/player.png");
    createPlayerSprite();
    enemyTexture = loadTexture("img/gorito.png");
    createEnemySprites();
    cellTexture = loadTexture("img/cell.png");
    blockTexture = loadTexture("img/block.png");
    createLevelSprites();
    background1Texture = loadTexture("img/background1.png");
    createBackgroundSprite();
    createWeaponSprite();
    itemTexture = loadTexture("img/item.png");
    createItemSprites();

}


void Graphics::render(sf::RenderWindow& window) {

    window.clear(sf::Color(0, 0, 0));
    
    /*for (int row = 0; row < logic.gridHeight; ++row) {
        for (int col = 0; col < logic.gridWidth; ++col) {
        // Calculate the position of each grid cell based on the cell size
        sf::RectangleShape cell(sf::Vector2f(logic.cellSize, logic.cellSize));
        cell.setPosition(col * logic.cellSize, row * logic.cellSize);
        cell.setOutlineColor(sf::Color::Green);
        cell.setOutlineThickness(1);
        cell.setFillColor(sf::Color::Transparent);

        window.draw(cell);
        }
    }*/
       
    window.draw(background1);
    
    for (auto& element : enemies.enemies) {
        window.draw(element);
    }

    /*for (auto& element : levels.levelShapes) {
        window.draw(element);
    }*/
    for (auto& element : items.expShapes) {
        window.draw(element);
    }

    for (auto& element : itemSprites) {
        window.draw(element);
    }
    
    for (auto& element : cellSprites) {
        window.draw(element);
    }
    
    for (auto& element : enemySprites) {
        window.draw(element);
    }

    for (auto& element : player.playerCharacter) {
        window.draw(element);
    }
 
    window.draw(weaponSprite);
    window.draw(playerSprite);

    window.display();
}


/*void Graphics::cameraView(sf::RenderWindow& window, sf::View& view) {
    sf::Vector2u windowSize = window.getSize();
    const sf::Vector2u originalWindowSize(1280, 720); // Replace with your original window size

    view.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

    const float aspectRatio = static_cast<float>(originalWindowSize.x) / originalWindowSize.y;
    float scaleFactor;

    if (static_cast<float>(windowSize.x) / windowSize.y > aspectRatio) {
        scaleFactor = static_cast<float>(windowSize.y) / originalWindowSize.y;
    } else {
        scaleFactor = static_cast<float>(windowSize.x) / originalWindowSize.x;
    }

    const float scaledWidth = originalWindowSize.x * scaleFactor;
    const float scaledHeight = originalWindowSize.y * scaleFactor;
    const float offsetX = (windowSize.x - scaledWidth) / 2.0f;
    const float offsetY = (windowSize.y - scaledHeight) / 2.0f;

    view.setViewport(sf::FloatRect(offsetX / windowSize.x, offsetY / windowSize.y, scaledWidth / windowSize.x, scaledHeight / windowSize.y));
    view.setCenter(originalWindowSize.x / 2.0f, originalWindowSize.y / 2.0f);
    view.setSize(originalWindowSize.x, originalWindowSize.y);

    // Get the player's position
    float playerX = player.playerCharacter[0].getPosition().x;
    float playerY = player.playerCharacter[0].getPosition().y;

    // Calculate the camera bounds based on the grid
    
    // Modification for enemy respawner
    //float cameraLeftEdge = scaledWidth / 2.0f;
    float cameraLeftEdge = (scaledWidth / 2.0f) + 1500;
    
    float cameraRightEdge = (logic.gridWidth * logic.cellSize) - (scaledWidth / 2.0f);

    // Adjust the camera position if the player reaches the edges
    if (playerX < cameraLeftEdge)
        playerX = cameraLeftEdge;
    else if (playerX > cameraRightEdge)
        playerX = cameraRightEdge;
    
    
    view.setCenter(playerX, view.getCenter().y);
    //view.setCenter(playerX, playerY);

    window.setView(view);
}*/


void Graphics::cameraView(sf::RenderWindow& window, sf::View& view) {
    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    float desiredAspectRatio = 16.0f / 9.0f;
    float desiredWidth = windowHeight * desiredAspectRatio;

    float leftEdge = desiredWidth * 0.2f;    // Distance from the left edge
    float rightEdge = desiredWidth * 0.10f;   // Distance from the right edge

    sf::Vector2f playerPosition = player.playerCharacter[0].getPosition();
    sf::Vector2f currentCenter = view.getCenter();

    float newCenterX = currentCenter.x;

    if (playerPosition.x - newCenterX > rightEdge) {
        newCenterX = playerPosition.x - rightEdge;
    } else if (newCenterX - playerPosition.x > leftEdge) {
        newCenterX = playerPosition.x + leftEdge;
    }

    float newCenterY = windowHeight / 2.0f;

    view.setSize(desiredWidth, windowHeight);
    view.setCenter(newCenterX, newCenterY);
    window.setView(view);
}








sf::Texture Graphics::loadTexture(std::string filename) {

    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        //error
    }
    return texture;
}

void Graphics::createPlayerSprite() {
    playerSprite.setTexture(playerTexture);
    //playerSprite.setPosition(2500, 300);
}

void Graphics::createWeaponSprite() {

    sf::IntRect weaponRect(663, 0, 171  , 25);
    weaponSprite.setTexture(playerTexture);
    weaponSprite.setTextureRect(weaponRect);
}

void Graphics::createItemSprites() {

    sf::Sprite itemSprite;
    
    for (int i = 0; i < items.expShapes.size(); i++) {

        itemSprite.setTexture(itemTexture);
        itemSprite.setScale(0.25, 0.25);
        itemSprites.push_back(itemSprite);
    }
    
}




void Graphics::createBackgroundSprite() {
    background1.setTexture(background1Texture);
    background1.setPosition(-720, 0);
}


void Graphics::createEnemySprites() {

    sf::Sprite enemySprite;
    for (int i = 0; i < enemies.enemies.size(); i++){
        enemySprite.setTexture(enemyTexture);
        enemySprites.push_back(enemySprite);
    }
}

void Graphics::createLevelSprites() {

    sf::Color ground = {29, 148, 82, 255 };
    sf::Color block = { 255, 0, 0, 255 };

    sf::Sprite cellSprite;
    sf::Color color;
    for (auto& element : levels.levelShapes) {

        color = element.getFillColor();

        if (color == ground) {
            cellSprite.setTexture(cellTexture);
            cellSprites.push_back(cellSprite);
        }
        if (color == block) {
            cellSprite.setTexture(blockTexture);
            cellSprites.push_back(cellSprite);
        }
    }
}


void Graphics::updateBGSpritePosition(sf::View& view) {
    sf::Vector2f playerPosition = player.playerCharacter[0].getPosition();
    sf::Vector2f cameraCenter = view.getCenter();
    sf::Vector2f cameraSize = view.getSize();

    float leftEdge = cameraSize.x * 0.2f;    // Distance from the left edge
    float rightEdge = cameraSize.x * 0.10f;   // Distance from the right edge

    float deltaX = 0.0f;

    if (playerPosition.x - cameraCenter.x > rightEdge) {
        deltaX = -0.2;//(playerPosition.x - cameraCenter.x - rightEdge);
    } else if (cameraCenter.x - playerPosition.x > leftEdge) {
        deltaX = 0.2;//cameraCenter.x - playerPosition.x - leftEdge;
    }

    background1.move(deltaX, 0.0f);
}

void Graphics::updateWeaponSpritePosition() {

    weaponSprite.setPosition(player.playerCharacter[1].getPosition().x, player.playerCharacter[1].getPosition().y);    
    
    if (player.attackBOOL) {
        if (std::signbit(player.velocity.x)) {
            weaponSprite.setScale(-1.f, 1.f); // Reverse X scale
        } else if (player.velocity.x > 0) {
            weaponSprite.setScale(1.f, 1.f);
        }
    } else { weaponSprite.setScale(0, 0); };

}





void Graphics::animatePlayerSprite() {

    static sf::Clock timer;

    sf::IntRect idle(0, 0, 76, 136);
    sf::IntRect walk1(76, 0, 77, 136);
    sf::IntRect walk2(153, 0, 76, 136);
    sf::IntRect walk3(229, 0, 75, 136);
    sf::IntRect jump(304, 0, 72, 136);
    sf::IntRect attack1(376, 0, 106, 136);
    sf::IntRect attack2(482, 0, 74, 136);
    sf::IntRect attack3(556, 0, 108, 136);


    // Define the duration of each frame in seconds
    const float FRAME_DURATION = 0.1f;

    sf::IntRect idleFrames[] = { idle };
    const int NUM_IDLE_FRAMES = sizeof(idleFrames) / sizeof(idleFrames[0]);

    sf::IntRect walkFrames[] = { walk1, walk2, walk3 };
    const int NUM_WALKING_FRAMES = sizeof(walkFrames) / sizeof(walkFrames[0]);

    sf::IntRect jumpFrames[] = { jump };
    const int NUM_JUMP_FRAMES = sizeof(jumpFrames) / sizeof(jumpFrames[0]);

    sf::IntRect attackFrames[] = {attack1, attack2, attack3};
    const int NUM_ATTACK_FRAMES = sizeof(attackFrames) / sizeof(attackFrames[0]);


    // Determine which set of frames to use based on the velocity
    sf::IntRect* frames;
    int numFrames;

    if (std::abs(player.velocity.x) > 0.3) {
        frames = walkFrames;
        numFrames = NUM_WALKING_FRAMES;
    } else {
        frames = idleFrames;
        numFrames = NUM_IDLE_FRAMES;
    }

    if (player.velocity.y != 0) {
        frames = jumpFrames;
        numFrames = NUM_JUMP_FRAMES;
    }

    if (player.attackBOOL) {
        frames = attackFrames;
        numFrames = NUM_ATTACK_FRAMES;
    }

    // Update the current frame based on the elapsed time
    int currentFrame = static_cast<int>((timer.getElapsedTime().asSeconds() / FRAME_DURATION)) % numFrames;

    // Set the texture rect based on the current frame
    playerSprite.setTextureRect(frames[currentFrame]);


    if (player.velocity.x > 0) { 
        playerSprite.setScale(-1, 1);
        playerSprite.setOrigin(playerSprite.getLocalBounds().width, 0.f); // set origin to right edge

    } else {
        playerSprite.setScale(1, 1);
        playerSprite.setOrigin(0.f, 0.f);
    }

    // Set sprite to the player position
    playerSprite.setPosition(player.playerCharacter[0].getPosition().x, player.playerCharacter[0].getPosition().y);


}



void Graphics::animateLevelSprites() {

    sf::Color ground = {29, 148, 82, 255 };
    sf::Color block = { 255, 0, 0, 255 };
    sf::Color color;

    for (int i = 0; i < cellSprites.size(); i++) {
        
        color = levels.levelShapes[i].getFillColor();
        if (color == ground) {
            cellSprites[i].setPosition(levels.levelShapes[i].getPosition().x, levels.levelShapes[i].getPosition().y);
        }
        if (color == block) {
            cellSprites[i].setPosition(levels.levelShapes[i].getPosition().x, levels.levelShapes[i].getPosition().y);
        }
    }

}


void Graphics::animateEnemySprites() {

    static sf::Clock timerEnemy;
    static int frameCount;
    //const float animationSpeed = 0.01f; // 


    sf::IntRect goroWalking1(0, 0, 62, 120);
    sf::IntRect goroWalking2(62, 0, 63, 120);
    sf::IntRect goroWalking3(125, 0, 59, 120);
    sf::IntRect goroWalking4(184, 0, 63, 120);
    sf::IntRect goroWalking5(247, 0, 66, 120);
    sf::IntRect goroWalking6(313, 0, 61, 120);
    sf::IntRect goroWalking7(374, 0, 62, 120);
    sf::IntRect goroWalking8(436, 0, 63, 120);
    sf::IntRect goroWalking9(499, 0, 65, 120);


    // Define the duration of each frame in seconds
    const float FRAME_DURATION = 0.07f;

    // Define the animation frames for the walking animation
    sf::IntRect walkingFrames[] = {
        goroWalking1,
        goroWalking2,
        goroWalking3,
        goroWalking4,
        goroWalking5,
        goroWalking6,
        goroWalking7,
        goroWalking8,
        goroWalking9
    };
    const int NUM_WALKING_FRAMES = sizeof(walkingFrames) / sizeof(walkingFrames[0]);

    sf::IntRect* frames = walkingFrames;
    int numFrames;
    numFrames = NUM_WALKING_FRAMES;

    // Update the current frame based on the elapsed time
    int currentFrame = static_cast<int>((timerEnemy.getElapsedTime().asSeconds() / FRAME_DURATION)) % numFrames;


    for (int i = 0; i < enemies.enemies.size(); i++) {
        // Set the position of each sprite to the corresponding enemy
        enemySprites[i].setTextureRect(frames[currentFrame]);
        enemySprites[i].setPosition(enemies.enemies[i].getPosition());
        
        if (enemies.enemiesVelocities[i].x < 0) { 
            enemySprites[i].setScale(-1.5f, 1.5f);
            enemySprites[i].setOrigin(enemySprites[i].getLocalBounds().width, 0.f); // set origin to right edge

        } else {
            enemySprites[i].setScale(1.5f, 1.5f);
            enemySprites[i].setOrigin(0.f, 0.f);
        }
    }
}


void Graphics::animateItemSprites() {

    static sf::Clock timer;
    static int frameCount;
    //const float animationSpeed = 0.01f; // 


    sf::IntRect coin1(0, 0, 58, 100);
    sf::IntRect coin2(58, 0, 58, 100);
    sf::IntRect coin3(116, 0, 58, 120);
    sf::IntRect coin4(174, 0, 63, 120);



    // Define the duration of each frame in seconds
    const float FRAME_DURATION = 0.1f;

    // Define the animation frames for the walking animation
    sf::IntRect itemFrames[] = {
        coin1,
        coin2,
        coin3,
        coin4,

    };
    const int NUM_WALKING_FRAMES = sizeof(itemFrames) / sizeof(itemFrames[0]);

    sf::IntRect* frames = itemFrames;
    int numFrames;
    numFrames = NUM_WALKING_FRAMES;

    // Update the current frame based on the elapsed time
    int currentFrame = static_cast<int>((timer.getElapsedTime().asSeconds() / FRAME_DURATION)) % numFrames;


    for (int i = 0; i < enemies.enemies.size(); i++) {
        // Set the position of each sprite to the corresponding enemy
        itemSprites[i].setTextureRect(frames[currentFrame]);
        itemSprites[i].setPosition(items.expShapes[i].getPosition());
        
    }
}



void Graphics::graphicsMain(sf::RenderWindow& window, sf::View& view) {
    
    updateBGSpritePosition(view);
    updateWeaponSpritePosition();
    animatePlayerSprite();
    animateEnemySprites();
    animateItemSprites();
    animateLevelSprites();
    cameraView(window, view);
    render(window);
    

}