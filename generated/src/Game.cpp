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
    this->initScoreboard();

}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->missile;
    delete this->missileAlert;
    delete this->mainMenu;
    delete this->scoreboard;

}



void Game::initVariables(){
    this->endGame = false;
}

void Game::initWindow() {
    this->videoMode=sf::VideoMode(windowWidth,windowHeight);
    this->window=new sf::RenderWindow(this->videoMode,"JetpackJoyride",sf::Style::Default);
    this->window->setFramerateLimit(60);
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
    constexpr float backgroundSpeed = 15.0f; // Scrolling speed for the background
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

void Game::initScoreboard(){
    this->scoreboard = new Scoreboard("../resources/New Athletic M54.ttf", "../resources/record_distance.txt");
}



void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
            break;
            case sf::Event::MouseButtonPressed:
                if (this->isMenu) {
                    int buttonIndex = this->mainMenu->handleInput(this->event);
                    switch (buttonIndex) {
                        case 0: // PLAY button
                            this->isMenu = false; // Start the gameplay
                        break;
                        case 1: // SCOREBOARD button
                            this->mainMenu->showScoreboard(this->scoreboard->getHighScore()); // Pass the high score
                        break;
                        default:
                            break;
                    }
                }
            break;
            default:
                break;
        }
    }
}


void Game::update(float deltaTime) {
    this->pollEvents();
    if (this->isMenu) {
        // Skip gameplay updates when in the menu
        return;
    }

    this->background->update(deltaTime);
    this->player->update(deltaTime);
    this->scoreboard->update(deltaTime, 15.0f); // Update the scoreboard with the player's speed

    //Move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player->useJetpack(true);
    else player->useJetpack(false);

    auto* missile = dynamic_cast<Missile *>(this->missile);
    auto* missileAlert = dynamic_cast<MissileAlert *>(this->missileAlert);

   if(!missile->isLaunched() && !missileAlert->isAlerting()) {
        missileAlert->alert();
    }
        const float playerY=player->getSprite().getPosition().y;
     missileAlert->updateAlert(playerY, deltaTime);
    if(!missile->isLaunched() && !missileAlert->isAlerting()) {
        missile->launch(missileAlert->getY());
        missile->updateMissile(deltaTime);
    }
    missile->updateMissile(deltaTime);

    if (Collision::checkCollision(player->getSprite(), missile->getSprite())) {
        std::cout << "Collision detected!" << std::endl;
        // Handle collision (e.g., end the game, decrease health, etc.)
    }
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
        this->scoreboard->draw(*this->window);
    }

    this->window->display();
}

bool Game::running() const {
    return this->window->isOpen();
}