//
// Created by Vlad on 05-Nov-24.
//

#ifndef MISSILE_H
#define MISSILE_H

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>


class Missile {
private:

    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool launched;
    void initSprite();
    void initTexture();
    float timer=0;

public:
    Missile();
    ~Missile();
    Missile(const Missile& missile);
    Missile& operator=(const Missile& other);


    void update();
    void renderMissile(sf::RenderTarget& target);
    void launch(float yPosition);
     bool isLaunched()const;

};
#endif //MISSILE_H
