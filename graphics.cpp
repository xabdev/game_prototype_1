#include "graphics.h"


Graphics::Graphics(Logic& logic, Player& player, Enemies& enemies, Items& items) : logic(logic), player(player), enemies(enemies), items(items) {

    font = loadFont();
    texts = createText();
    
    playerTexture = loadTexture("img/player.png");
    createPlayerSprite();
    enemyTexture = loadTexture("img/gorito.png");
    createEnemySprites();
    cellTexture = loadTexture("img/cell.png");
    blockTexture = loadTexture("img/block.png");
    createLevelSprites();
    background1Texture = loadTexture("img/background1.png");
    background2Texture = loadTexture("img/background2.png");
    createBackgroundSprite();
    itemTexture = loadTexture("img/item.png");
    createItemSprites();

    createUIElements();
}

void Graphics::showFPS()
{
    static sf::Clock clock;
    static int frameCount = 0;
    
    frameCount++;
    sf::Time time = clock.getElapsedTime();
    if (time.asMilliseconds() > 1000)
    {
        float fps = static_cast<float>(frameCount) / time.asSeconds();
        framerate = fps;
        frameCount = 0;
        clock.restart();
    }
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
    window.draw(background2);
    


    /*for (auto& element : levels.levelShapes) {
        window.draw(element);
    }*/
    /*for (auto& element : items.expShapes) {
        window.draw(element);
    }*/

    for (auto& element : itemSprites) {
        if (element.getPosition().x > -500) {
            window.draw(element);
        }
    }
    
    for (auto& element : cellSprites) {
        window.draw(element);
    }
    
    for (auto& element : enemySprites) {
        if (element.getPosition().x > -500) {
            window.draw(element);
        }
    }

    /*for (auto& element : enemies.enemies) {
        window.draw(element);
    }*/

    for (auto& element : uiElements) {
        window.draw(element);
    }

    /*for (auto& element : player.playerCharacter) {
        window.draw(element);
    }*/
 
    
    window.draw(playerSprite);

    for (auto& text : texts) {
        window.draw(text);
    }

    window.display();
}


void Graphics::loadingScreen(sf::RenderWindow& window) { 

    window.clear(sf::Color::Magenta);
    window.display();
}

sf::Font Graphics::loadFont() {

    sf::Font font;
    if (!font.loadFromFile("font/pixely.ttf")) {
        std::cout << "failed to load font \n";
    }
    return font;
}


sf::Text Graphics::formatText() {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    
    return text;
}


std::vector<sf::Text> Graphics::createText() {

    sf::Text xVel = formatText();
    sf::Text yVel = formatText();
    sf::Text enemiesKilled = formatText();
    sf::Text fps = formatText();
    sf::Text comboCounter = formatText();
    comboCounter.setCharacterSize(20);
    comboCounter.setFillColor(sf::Color::Green);
    enemiesKilled.setCharacterSize(25);
    texts.push_back(xVel);
    texts.push_back(yVel);
    texts.push_back(enemiesKilled);
    texts.push_back(fps);
    texts.push_back(comboCounter);
    
    
    return texts;
}

void Graphics::updateUIText(sf::View& view) {

    texts[0].setString("velocity.x: " + std::to_string(player.velocity.x));
    texts[0].setPosition(view.getCenter().x + 400, 5);
    texts[1].setString("velocity.y: " + std::to_string(player.velocity.y));
    texts[1].setPosition(view.getCenter().x + 400, 30);
    texts[2].setPosition(view.getCenter().x - 100, 10);
    texts[2].setString("Enemies Killed: " + std::to_string(logic.numberOfEnemiesKilled));
    texts[3].setPosition(view.getCenter().x + 400, 55);
    texts[3].setString("FPS: " + std::to_string(framerate));
    texts[4].setPosition(view.getCenter().x - 600, 250);
    
    if (player.comboCounter < 10) {
        texts[4].setCharacterSize(40);
    } else if (player.comboCounter > 10) {
        texts[4].setCharacterSize(75);
    } else if (player.comboCounter > 50) {
        texts[4].setCharacterSize(100);
    } else if (player.comboCounter > 100) {
        texts[4].setCharacterSize(150);
    }
    
    
    if (player.comboCounter > 0) {
        texts[4].setString(std::to_string(player.comboCounter));
    } else {texts[4].setString(" ");}

}




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

    player.playerView = view;
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
}



void Graphics::createItemSprites() {

    sf::Sprite itemSprite;
    
    for (int i = 0; i < items.expShapes.size(); i++) {

        itemSprite.setTexture(itemTexture);
        itemSprite.setPosition(-500, 0);
        itemSprite.setScale(0.25, 0.25);
        itemSprites.push_back(itemSprite);
    }
    
}




void Graphics::createBackgroundSprite() {
    background1.setTexture(background1Texture);
    background1.setPosition(0, 0);
    background2.setTexture(background2Texture);
    background1.setPosition(1280, 0);
}


void Graphics::createEnemySprites() {

    sf::Sprite enemySprite;
    for (int i = 0; i < enemies.enemies.size(); i++){
        enemySprite.setPosition(-5000, 0);
        enemySprite.setTexture(enemyTexture);
        enemySprites.push_back(enemySprite);
    }
}


void Graphics::createUIElements() {

    sf::RectangleShape uiElement1;
    sf::RectangleShape uiElement2;
    uiElement1.setSize(sf::Vector2f {200, 10});
    uiElement2.setSize(sf::Vector2f {200, 10});
    uiElement1.setFillColor(sf::Color::Green);
    uiElement2.setFillColor(sf::Color::Transparent);
    uiElement2.setOutlineColor(sf::Color::White);
    uiElement2.setOutlineThickness(3.0f);
    uiElements.push_back(uiElement2);
    uiElements.push_back(uiElement1);
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

    float leftEdge = cameraCenter.x - cameraSize.x / 2.0f + cameraSize.x * 0.2f;    // Distance from the left edge
    float rightEdge = cameraCenter.x + cameraSize.x / 2.0f - cameraSize.x * 0.1f;   // Distance from the right edge

    float deltaX = 0.0f;

    /*if (playerPosition.x - leftEdge > rightEdge) {
        deltaX = -0.2;
    } else if (leftEdge - playerPosition.x > 0) {
        deltaX = 0.2;
    }*/

    if (player.velocity.x > 2.24) {
        deltaX = -0.15;
    } else if (player.velocity.x < -2.24) {
        deltaX = 0.15;
    }

    background1.move(deltaX, 0.0f);
    background2.move(deltaX, 0.0f);

    // Check if background1 has moved off the screen to the left
    if (background1.getPosition().x + background1.getGlobalBounds().width < cameraCenter.x - cameraSize.x / 2.0f) {
        background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0);
    }

    // Check if background2 has moved off the screen to the left
    if (background2.getPosition().x + background2.getGlobalBounds().width < cameraCenter.x - cameraSize.x / 2.0f) {
        background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0);
    }

    // Check if background1 has moved off the screen to the right
    if (background1.getPosition().x > cameraCenter.x + cameraSize.x / 2.0f) {
        background1.setPosition(background2.getPosition().x - background1.getGlobalBounds().width, 0);
    }

    // Check if background2 has moved off the screen to the right
    if (background2.getPosition().x > cameraCenter.x + cameraSize.x / 2.0f) {
        background2.setPosition(background1.getPosition().x - background2.getGlobalBounds().width, 0);
    }
}


void Graphics::animatePlayerSprite() {

    static sf::Clock timer;

    sf::IntRect idle(0, 0, 94, 135);

    sf::IntRect walk1(94, 0, 94, 135);
    sf::IntRect walk2(188, 0, 84, 135);
    sf::IntRect walk3(272, 0, 59, 135);
    sf::IntRect walk4(331, 0, 78, 135);
    sf::IntRect walk5(409, 0, 76, 135);
    sf::IntRect walk6(485, 0, 76, 135);

    sf::IntRect jump(561, 0, 73, 136);

    sf::IntRect attack1(634, 0, 138, 136);
    sf::IntRect attack2(772, 0, 120, 136);
    sf::IntRect attack3(892, 0, 215, 136);


    // Define the duration of each frame in seconds
    float FRAME_DURATION = 0.1f;


    sf::IntRect idleFrames[] = { idle };
    const int NUM_IDLE_FRAMES = sizeof(idleFrames) / sizeof(idleFrames[0]);

    sf::IntRect walkFrames[] = { walk1, walk2, walk3, walk4, walk5, walk6 };
    const int NUM_WALKING_FRAMES = sizeof(walkFrames) / sizeof(walkFrames[0]);

    sf::IntRect jumpFrames[] = { jump };
    const int NUM_JUMP_FRAMES = sizeof(jumpFrames) / sizeof(jumpFrames[0]);

    sf::IntRect attackFrames[] = { /*attack1, attack2,*/ attack3};
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


    if (player.velocity.x < 0) {
        playerSprite.setScale(-1, 1);
        playerSprite.setOrigin(player.playerCharacter[0].getSize().x, 0.f);
        playerSprite.setPosition(player.playerCharacter[0].getPosition());
    } else {
        playerSprite.setScale(1, 1);
        playerSprite.setOrigin(0.f, 0.f);
        playerSprite.setPosition(player.playerCharacter[0].getPosition());
    }


    // Set sprite to the player position
    //playerSprite.setPosition(player.playerCharacter[0].getPosition().x, player.playerCharacter[0].getPosition().y);


}



void Graphics::updateUIElementsPosition(sf::View& view) {

    for (int i = 0; i < uiElements.size(); i++) {
        uiElements[i].setPosition(view.getCenter().x - 620, 10);
    }

    float currentWidth = (static_cast<float>(player.health) / 100.0f) * 200;
    uiElements[1].setSize(sf::Vector2f(currentWidth, 10));

    if (currentWidth > 100) {
        uiElements[1].setFillColor(sf::Color::Green);
    }
    if (currentWidth < 100) {
        uiElements[1].setFillColor(sf::Color::Red);
    }

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

    static int frameCount;

    sf::IntRect goroWalking1(0, 0, 62, 120);
    sf::IntRect goroWalking2(62, 0, 63, 120);
    sf::IntRect goroWalking3(125, 0, 59, 120);
    sf::IntRect goroWalking4(184, 0, 63, 120);
    sf::IntRect goroWalking5(247, 0, 66, 120);
    sf::IntRect goroWalking6(313, 0, 61, 120);
    sf::IntRect goroWalking7(374, 0, 62, 120);
    sf::IntRect goroWalking8(436, 0, 63, 120);
    sf::IntRect goroWalking9(499, 0, 65, 120);
    sf::IntRect goroDeath1(564, 0, 98, 120);
    sf::IntRect goroDeath2(662, 0, 105, 120);
    sf::IntRect goroDeath3(767, 0, 94, 120);
    sf::IntRect goroDeath4(861, 0, 79, 120);
    sf::IntRect goroDeath5(940, 0, 107, 120);
    sf::IntRect goroJump(1049, 0, 68, 120);
    sf::IntRect goroAttack1(1116, 0, 89, 120);
    sf::IntRect goroAttack2(1205, 0, 107, 120);
    sf::IntRect goroAttack3(1312, 0, 66, 120);
    sf::IntRect goroAttack4(1378, 0, 78, 120);
    sf::IntRect goroAttack5(1456, 0, 110, 120);
    sf::IntRect goroDamaged(1566, 0, 69, 120);

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

    sf::IntRect deathFrames[] = {
        goroDeath1,
        goroDeath2,
        goroDeath3,
        goroDeath4,
        goroDeath5
        //goroDeath6
    };
    const int NUM_DEATH_FRAMES = sizeof(deathFrames) / sizeof(deathFrames[0]);

    sf::IntRect jumpFrames[] = {
        goroJump

    };
    const int NUM_JUMP_FRAMES = sizeof(jumpFrames) / sizeof(jumpFrames[0]);

    sf::IntRect attackFrames[] = {
        goroAttack1,
        goroAttack2,
        goroAttack3,
        goroAttack4,
        goroAttack5

    };
    const int NUM_ATTACK_FRAMES = sizeof(attackFrames) / sizeof(attackFrames[0]);

    sf::IntRect damagedFrames[] = {
        goroDamaged
    };
    const int NUM_DAMAGED_FRAMES = sizeof(damagedFrames) / sizeof(damagedFrames[0]);


    for (int i = 0; i < enemies.enemies.size(); i++) {
        sf::IntRect* frames;
        int numFrames;

        if (std::abs(enemies.enemiesVelocities[i].x) > 0.3 && enemies.enemiesVelocities[i].y == 0) {
            frames = walkingFrames;
            numFrames = NUM_WALKING_FRAMES;
        }
        else if (enemies.enemiesHealth[i] <= 0) {
            frames = deathFrames;
            numFrames = NUM_DEATH_FRAMES;
        }
        else if (enemies.enemiesVelocities[i].y != 0) {
            frames = jumpFrames;
            numFrames = NUM_JUMP_FRAMES;
        }
        else if (enemies.isEnemyHittingPlayer[i]) {
            frames = attackFrames;
            numFrames = NUM_ATTACK_FRAMES;
        }
        else {
            // Handle any other animation type or default behavior here
            // ...
            continue;
        }
        
        if (enemies.hitStatus[i]) {
            frames = damagedFrames;
            numFrames = NUM_DAMAGED_FRAMES;
        }
        

        // Update the current frame based on the elapsed time
        int currentFrame = static_cast<int>((enemies.enemyAnimationTimer[i].getElapsedTime().asSeconds() / FRAME_DURATION)) % numFrames;

        enemySprites[i].setTextureRect(frames[currentFrame]);
        enemySprites[i].setPosition(enemies.enemies[i].getPosition());

        // Set the scale and origin of the sprite
        if (enemies.enemiesVelocities[i].x < 0) {
            enemySprites[i].setScale(-1.5f, 1.5f);
            enemySprites[i].setOrigin(enemySprites[i].getLocalBounds().width, 0.f); // set origin to right edge
        }
        else {
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
    
    if (logic.restart) {
        enemySprites.clear();
        createEnemySprites();
        logic.restart = false;
    }

    
    updateBGSpritePosition(view);
    updateUIElementsPosition(view);
    animatePlayerSprite();
    animateEnemySprites();
    animateItemSprites();
    animateLevelSprites();
    cameraView(window, view);
    updateUIText(view);
    showFPS();
    render(window);
    

}