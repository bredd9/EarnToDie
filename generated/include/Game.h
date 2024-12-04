//
// Created by Vlad on 03-Nov-24.
//

#ifndef GAME_H
#define GAME_H


#include <Player.h>
#include <Missile.h>
#include <MissileAlert.h>
#include <Background.h>
#include <CoinManager.h>

#include "MainMenu.h"

class Game {

private:
    const int windowWidth = 1200;
    const int windowHeight = 791;
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event event;
    bool endGame;
    bool isMenu;
    MainMenu *mainMenu;
    Player* player;
    Object *missileAlert;
    Object *missile;
    Background *background;
    CoinManager* coinManager;
    void initVariables();
    void initWindow();
    void initPlayer();
    void initMissile();
    void initCoins();
    void initMissileAlert();
    void initBackground();
    void initMenu();



public:
    Game();
    ~Game();
    bool running() const;
    void pollEvents();
    void update();
    void render() const;

};

#endif //GAME_H
