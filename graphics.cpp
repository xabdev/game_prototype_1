#include "graphics.h"


Graphics::Graphics(Logic& logic, Player& player, Enemies& enemies) : logic(logic), player(player), enemies(enemies) {
    
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
    
    float cameraLeftEdge = scaledWidth / 2.0f;
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
