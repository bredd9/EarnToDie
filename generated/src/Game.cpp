//
// Created by Vlad on 03-Nov-24.
//

#include "../include/Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initMenu();
    this->initBackground();
    this->initPlayer();
    this->initMissileAlert();
    this->initMissile();
    this->initCoins();

}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->missile;
    delete this->missileAlert;
    delete this->coinManager;
    delete this->mainMenu;

}

void Game::initVariables(){
    this->endGame = false;
}

void Game::initWindow() {
    this->videoMode=sf::VideoMode(windowWidth,windowHeight);
    this->window=new sf::RenderWindow(this->videoMode,"JetpackJoyride",sf::Style::Default);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initMenu() {
    this->mainMenu = new MainMenu(this->window,
                                  "../resources/GameMenu.png",
                                  "../resources/Logo.png",
                                  "../resources/ButtonMenu.png",
                                  "../resources/New Athletic M54.ttf");
    this->isMenu = true; // Start in the menu phase
}

void Game::initBackground() {
    this->background = new Background();
    const float backgroundSpeed = 200.0f; // Scrolling speed for the background
    if (!this->background->initialize("../resources/Background.png", backgroundSpeed, windowWidth, windowHeight)) {
        throw std::runtime_error("Failed to initialize background");
         // Close the game if initialization fails
    }
}




void Game::initPlayer() {
    this->player = new Player();
}

void Game::initMissileAlert() {
    this->missileAlert = new MissileAlert("../resources/MissileAlert.png");
}
void Game::initMissile() {
    this->missile = new Missile("../resources/Missile.png");
}

void Game::initCoins() {
    this->coinManager = new CoinManager("../resources/Coin.png", sf::Vector2f(windowWidth, windowHeight), 200.f);
}



void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
            break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
            break;
            case sf::Event::MouseButtonPressed:
                if (this->isMenu) {
                    switch (this->mainMenu->handleInput(this->event)) {
                        case 0: // PLAY button
                            this->isMenu = false; // Start to gameplay
                        break;
                        case 1: // SCOREBOARD button
                            std::cout << "Scoreboard button clicked!" << std::endl;
                        // Implement scoreboard logic here
                        break;
                        case 2: // RULES button
                            std::cout << "Rules button clicked!" << std::endl;
                        // Implement rules logic here
                        break;
                        default:
                            break;
                    }
                }
            break;
            default:;
        }
    }
}

void Game::update() {
    this->pollEvents();
    if (this->isMenu) {
        // Skip gameplay updates when in the menu
        return;
    }
    this->background->update(static_cast<float>(1.0/144.0f));
    this->player->update();

    //Move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else player->useJetpack(false);

    this->coinManager->update();

   if(!dynamic_cast<Missile *>(missile)->isLaunched() && !dynamic_cast<MissileAlert *>(missileAlert)->isAlerting()) {
        dynamic_cast<MissileAlert *>(missileAlert)->alert();
    }

    const float playerY=player->getSprite().getPosition().y;

     dynamic_cast<MissileAlert *>(missileAlert)->updateAlert(playerY);
    if(!dynamic_cast<Missile *>(missile)->isLaunched() && !dynamic_cast<MissileAlert *>(missileAlert)->isAlerting()) {
        dynamic_cast<Missile *>(missile)->launch(dynamic_cast<MissileAlert *>(missileAlert)->getY());
        dynamic_cast<Missile *>(missile)->update();
    }
    dynamic_cast<Missile *>(missile)->update();

}


void Game::render() const {
    this->window->clear();

    if (this->isMenu) {
        this->mainMenu->render(); // Render the main menu
    } else {
        this->background->render(*this->window);
        this->player->render(*this->window);
        this->missileAlert->render(*this->window);
        this->missile->render(*this->window);
        this->coinManager->render(*this->window);
    }

    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}

