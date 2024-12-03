//
// Created by Vlad on 03-Nov-24.
//

#include "../include/Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initBackground();
    this->initPlayer();
    this->initMissileAlert();
    this->initMissile();

}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->missile;
    delete this->missileAlert;

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




void Game::pollEvents() {
    while(this->window->pollEvent(this->event)) {
        switch(this->event.type) {
            case sf::Event::Closed:
                this->window->close();
            break;
            case sf::Event::KeyPressed:
                if(this->event.key.code==sf::Keyboard::Escape)
                    this->window->close();
            break;
            default: ;
        }
    }
}

void Game::update() {
    this->pollEvents();
    this->background->update(static_cast<float>(1.0/144.0f));
    this->player->update();

    //Move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else player->useJetpack(false);


   if(!static_cast<Missile *>(missile)->isLaunched() && !static_cast<MissileAlert *>(missileAlert)->isAlerting()) {
        static_cast<MissileAlert *>(missileAlert)->alert();
    }

    const float playerY=player->getSprite().getPosition().y;

     static_cast<MissileAlert *>(missileAlert)->updateAlert(playerY);
    if(!static_cast<Missile *>(missile)->isLaunched() && !static_cast<MissileAlert *>(missileAlert)->isAlerting()) {
        static_cast<Missile *>(missile)->launch(static_cast<MissileAlert *>(missileAlert)->getY());
    }
    this->missile->update();
}


void Game::render() const {
    this->window->clear();
    this->background->render(*this->window);
    this->player->render(*this->window);
    this->missileAlert->render(*this->window);
    this->missile->render(*this->window);
    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}

