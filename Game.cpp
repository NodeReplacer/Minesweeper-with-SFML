#include "Game.h"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(400,400), "Minesweeper");

    this->tileSheet.loadFromFile("images/tiles.png");
    this->tileSprites.setTexture(tileSheet);

    //This is like seeding srand with time but using C++ 11's newfangled randomizer.
    //Very readable.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    randomGenerator = std::mt19937(seed);
    mineRand = std::uniform_int_distribution<int>(0,5);

    ////Set up the minefield//// 
    for (int i=1;i<=10;++i) {
        for (int j=1;j<=10;++j) {
            //Set everything to 10. Blank.
            //Remember this is displayGrid. gameGrid will tell us what's really under the surface.
            displayGrid[i][j] = 10;

            //Before we start with this: mineRand(randomGenerator) is basically rand%5
            //But apparently this way is better on C++. I don't know why they made it so unintuitive
            //but this is how it is used.
            if (mineRand(randomGenerator)==0) {
                gameGrid[i][j] = 9;
            }
            else {
                gameGrid[i][j] = 0;
            }
        }
    }
    ////Establish the number beneath each mine////
    for (int i=1;i<=10;++i) {
        for (int j=1;j<=10;++j) {
            //This works by just checking every square around you for the a "9" (mine) panel. 
            int n=0;
            if (gameGrid[i][j]==9) continue;
            if (gameGrid[i+1][j]==9) ++n;
            if (gameGrid[i][j+1]==9) ++n;
            if (gameGrid[i-1][j]==9) ++n;
            if (gameGrid[i][j-1]==9) ++n;
            if (gameGrid[i+1][j+1]==9) ++n;
            if (gameGrid[i-1][j-1]==9) ++n;
            if (gameGrid[i-1][j+1]==9) ++n;
            if (gameGrid[i+1][j-1]==9) ++n;
            gameGrid[i][j] = n;
        }
    }
    
}

Game::~Game() {
    
}

const bool Game::IsRunning() const {
    return this->window->isOpen();
}

void Game::Update() {
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
            ////Mouse events////
            case sf::Event::MouseButtonPressed:
                sf::Vector2i cursorPos = sf::Mouse::getPosition(*this->window);
                clickX = cursorPos.x/fieldWidth;
                clickY = cursorPos.y/fieldWidth;
                switch (this->event.key.code) {
                    case sf::Mouse::Left:
                        displayGrid[clickX][clickY] = gameGrid[clickX][clickY];
                        break;
                    case sf::Mouse::Right:
                        displayGrid[clickX][clickY] = 11;
                        break;
                    default:
                        break;
                }
        }
    }
}

void Game::Render() {
    this->window->clear(sf::Color::White);
    ////////////////////Search the tiles.png for the correct square and cut its texture out////////////////////////
    for (int i=1;i<=10;++i) {
        for (int j=1;j<=10;++j) {
            if (displayGrid[clickX][clickY] == 9) displayGrid[i][j] = gameGrid[i][j];
            tileSprites.setTextureRect(sf::IntRect(displayGrid[i][j]*fieldWidth,0,fieldWidth,fieldWidth));
            tileSprites.setPosition(i*fieldWidth,j*fieldWidth);
            this->window->draw(tileSprites);
        }
    }
    this->window->display();
}