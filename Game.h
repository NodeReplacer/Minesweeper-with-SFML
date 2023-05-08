#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow* window;
    int fieldWidth = 32;
    int gameGrid[12][12]; // For the game to use to keep track of itself.
    int displayGrid[12][12]; // For actually displaying.
    
    sf::Event event;
    
    //////////////////Tiles, textures, and graphics (sprites)///////////////////
    sf::Texture tileSheet;
    sf::Sprite tileSprites; //All kept in one texture, the texture will be cut up to display the correct "look"
public:
    
    const bool IsRunning() const; //Maybe it'll make things clearer instead othe usual window->isopen(); marker. Maybe not.
    
    Game();
    virtual ~Game();
    void update();
    void render();
};


#endif //MINESWEEPER_GAME_H
