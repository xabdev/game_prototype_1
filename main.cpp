#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "logic.h"
#include "graphics.h"
#include "player.h"
#include "gridmanager.h"
#include "levels.h"




void handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}


void runLogicTests() {
    // Create an instance of the Logic class
    Player player;
    Levels levels;
    Logic logic(player);
    Graphics graphics(logic, player);
    GridManager gridmanager(logic.gridWidth, logic.gridHeight);

    // Access the grid and perform tests
    std::vector<std::vector<int>>& grid = levels.levelGrid;

    // Print the grid to verify the value
    for (int row = 0; row < logic.gridHeight; ++row) {
        for (int col = 0; col < logic.gridWidth; ++col) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Grid Practice", sf::Style::Titlebar | sf::Style::Default);
    window.setFramerateLimit(60);

   Player player;
   Levels levels;
   Logic logic(player);
   Graphics graphics(logic, player);
   sf::View view;
   logic.preCalculatePlatformPositions();
    //for (const sf::FloatRect& rect : logic.platformBounds) {
     //   std::cout << "Left: " << rect.left << ", Top: " << rect.top << ", Width: " << rect.width << ", Height: " << rect.height << std::endl;
   // }
   //runLogicTests();


    

    while (window.isOpen()) {
        
        handleEvents(window);
                
        logic.gravityZ();                
        logic.vJoy();
        
        


        
        //std::cout << logic.getPlayerCell().x << " " << logic.getPlayerCell().y << "\n";

        graphics.render(window);
        graphics.cameraView(window, view);

    }

    return 0;
}
