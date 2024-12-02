//
// Created by Vlad on 03-Nov-24.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFMl/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Player {

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;

    float gravity;
    float jetpackPower;
    bool isUsingJetpack;
    void initTexture();
    void initSprite();




public:
    Player();
    ~Player();
    void update();
    void render(sf::RenderTarget& target) const;
    void useJetpack(bool activate);
    sf::Sprite& getSprite() { return sprite; }



};
#endif //PLAYER_H
