//
// Created by Vlad on 05-Nov-24.
//

#ifndef MISSILE_H
#define MISSILE_H


#include <Object.h>


class Missile : public Object {
private:

    float speed;
    bool launched;
    float timer=0;


public:
    Missile(const std::string& textureFile);
    ~Missile() override;
    void update()override;
    void render(sf::RenderTarget& target) const override;
    void launch(float yPosition);
    bool isLaunched() const;



};
#endif //MISSILE_H
