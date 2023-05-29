#include "graphics.h"


Graphics::Graphics(Logic& logic, Player& player, Enemies& enemies) : logic(logic), player(player), enemies(enemies) {

    playerTexture = loadTexture("img/player.png");
    playerWeaponTexture = loadTexture("img/weapon.png");
    createPlayerSprite();
    createWeaponSprite();
    

}


void Graphics::render(sf::RenderWindow& window) {

    window.clear(sf::Color(0, 0, 0));
    
    for (int row = 0; row < logic.gridHeight; ++row) {
        for (int col = 0; col < logic.gridWidth; ++col) {
        // Calculate the position of each grid cell based on the cell size
        sf::RectangleShape cell(sf::Vector2f(logic.cellSize, logic.cellSize));
        cell.setPosition(col * logic.cellSize, row * logic.cellSize);
        cell.setOutlineColor(sf::Color::Green);
        cell.setOutlineThickness(1);
        cell.setFillColor(sf::Color::Transparent);

        window.draw(cell);
        }
    }
       
    for (auto& element : levels.level) {
        window.draw(element);
    }
    for (auto& element : enemies.enemies) {
        window.draw(element);
    }
    for (auto& element : player.playerCharacter) {
        window.draw(element);
    }
 
    window.draw(playerSprite);

    window.display();
}


void Graphics::cameraView(sf::RenderWindow& window, sf::View& view) {
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
    playerSprite.setPosition(2500, 300);
}


void Graphics::createWeaponSprite() {
    playerWeaponSprite.setTexture(playerWeaponTexture);
    playerWeaponSprite.setPosition(2500, 300);
}


void Graphics::updateSpritesPosition() {

    playerSprite.setPosition(player.playerCharacter[0].getPosition());

}


void Graphics::animatePlayerSprite() {
    static sf::Clock timer;
    //static int frameCount;
    float animationSpeed = 0.1f;

    sf::IntRect idle(0, 0, 76, 136);
    sf::IntRect walk1(76, 0, 77, 136);
    sf::IntRect walk2(153, 0, 76, 136);
    sf::IntRect walk3(229, 0, 75, 136);


    // Define the duration of each frame in seconds
    const float FRAME_DURATION = 0.1f;

    sf::IntRect idleFrames[] = { idle };
    const int NUM_IDLE_FRAMES = sizeof(idleFrames) / sizeof(idleFrames[0]);

    sf::IntRect walkFrames[] = { walk1, walk2, walk3 };
    const int NUM_WALKING_FRAMES = sizeof(walkFrames) / sizeof(walkFrames[0]);

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

void Graphics::animateWeapon() {

    static sf::Clock weaponTimer;
    //static int weaponFrameCount;
    float animationSpeed = 0.1f;

    sf::IntRect attack1(305, 0, 24, 86);
    sf::IntRect attack2(329, 0, 51, 56);
    sf::IntRect attack3(380, 0, 73, 15);

    // Define the duration of each frame in seconds
    const float FRAME_DURATION = 0.1f;


    sf::IntRect attackFrames[] = { attack1, attack2, attack3};
    const int NUM_ATTACKING_FRAMES = sizeof(attackFrames) / sizeof(attackFrames[0]);

    // Determine which set of frames to use based on the velocity
    sf::IntRect* frames;
    int numFrames;

    if (player.attacking) {
        frames = attackFrames;
        numFrames = NUM_ATTACKING_FRAMES;
    }

    // Update the current frame based on the elapsed time
    int currentFrame = static_cast<int>((weaponTimer.getElapsedTime().asSeconds() / FRAME_DURATION)) % numFrames;

    // Set the texture rect based on the current frame
    if (player.attacking) {
        playerWeaponSprite.setTextureRect(frames[currentFrame]);
    }
    playerWeaponSprite.setPosition(player.playerCharacter[0].getPosition().x, player.playerCharacter[0].getPosition().y);

}




void Graphics::graphicsMain(sf::RenderWindow& window, sf::View& view) {
    
    //updateSpritesPosition();
    animatePlayerSprite();
    animateWeapon();
    cameraView(window, view);
    render(window);
    

}