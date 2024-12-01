//
// Created by Vlad on 03-Nov-24.
//

#include "../include/Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initBackground();
    this->initPlayer();

}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->background;
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
    const float backgroundSpeed = 200.0f; // Scrolling speed for the background
    if (!this->background->initialize("../resources/Background.png", backgroundSpeed, windowWidth, windowHeight)) {
        std::cout << "Failed to initialize background."<<std::endl;
        this->window->close(); // Close the game if initialization fails
    }
}

void Game::initPlayer() {
    this->player = new Player();
}
/*

 void Game::initMissile() {
    this->missile = new Missile();
}
void Game::initMissileAlert() {
    this->missileAlert = new MissileAlert();
}

*/

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
        }
    }
}

void Game::update() {
    this->pollEvents();
    this->background->update(144.0f);
    this->player->update();
  //  missile->update();
    //Move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else player->useJetpack(false);

//TODO:Missile si MissileAlert nu functioneaza

 /*  if(!missile->isLaunched() && !missileAlert->isAlerting()) {
        missileAlert->alert();

    }

    float playerY=player->getSprite().getPosition().y;

  //  missileAlert->update(playerY);
    if(!missile->isLaunched() && !missileAlert->isAlerting()) {
        missile->launch(missileAlert->getY());
    }
    */
}


void Game::render() const {
    this->window->clear();
    this->background->render(*this->window);
    this->player->render(*this->window);
  //  this->missile->renderMissile(*this->window);
   // this->missileAlert->renderAlert(*this->window);
    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}

