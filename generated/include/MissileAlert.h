//
// Created by Vlad on 06-Nov-24.
//

#ifndef MISSILEALERT_H
#define MISSILEALERT_H

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

class MissileAlert {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool active;
    sf::Clock timer;
    float alertDuration;
    void initSprite();
    void initTexture();
public:
    MissileAlert();
    ~MissileAlert();
    void update(float playerY);
    float getY()const;
    void renderAlert(sf::RenderTarget& target);

    void alert();
    bool isAlerting()const;

};





#endif //MISSILEALERT_H
