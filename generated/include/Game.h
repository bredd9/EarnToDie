//
// Created by Vlad on 03-Nov-24.
//

#ifndef GAME_H
#define GAME_H


#include <Player.h>
#include <Missile.h>
#include <MissileAlert.h>

class Game {

private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        sf::Event event;
        bool endGame;
        Player* player;
        MissileAlert *missileAlert;
        Missile *missile;
        void initVariables();
        void initWindow();
        void initPlayer();
        void initMissile();
        void initMissileAlert();


public:
        Game();
        ~Game();

        bool running() const;
        void pollEvents();
        void update();
        void render();

};

#endif //GAME_H
