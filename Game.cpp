#include "Game.h"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(400,400), "Minesweeper");

    this->tileSheet.loadFromFile("images/tiles.png");
    this->tileSprites.setTexture(tileSheet);
}

Game::~Game() {
    
}

const bool Game::IsRunning() const {
    return this->window->isOpen();
}

void Game::update() {
    //////////////////////Set all squares on displayGrid to 10 for now. Default////////////////////////////// 
    for (int i=1;i<=10;++i) {
        for (int j=1;j<=10;++j) {
            this->displayGrid[i][j] = 10;
        }
    }
    
    //////////////////////Event handling////////////////////
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            //////////////////Window close event////////////////
            case sf::Event::Closed:
                this->window->close();
                break;
            default:
                break;
            //////////////////All keyboard events here////////////////
            case sf::Event::KeyPressed:
                switch (this->event.key.code) {
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;
                    default:
                        break;
                }
        }
    }
}

void Game::render() {
    this->window->clear(sf::Color::White);
    ////////////////////Search the tiles.png for the correct square and cut its texture out////////////////////////////////
    for (int i=1;i<=10;++i) {
        for (int j=1;j<=10;++j) {
            tileSprites.setTextureRect(sf::IntRect(displayGrid[i][j]*fieldWidth,0,fieldWidth,fieldWidth));
            tileSprites.setPosition(i*fieldWidth,j*fieldWidth);
            this->window->draw(tileSprites);
        }
    }
    this->window->display();
}