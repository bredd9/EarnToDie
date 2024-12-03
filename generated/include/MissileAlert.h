//
// Created by Vlad on 06-Nov-24.
//

#ifndef MISSILEALERT_H
#define MISSILEALERT_H

#include <Object.h>

class MissileAlert : public Object {
private:

    bool active;
    sf::Clock timer;
    float alertDuration;

public:

    MissileAlert(const std::string& textureFile);
    ~MissileAlert() override;
    void update() override;
    void updateAlert(float playerY);
    float getY()const;
    void render(sf::RenderTarget& target) const override;
    void alert();
    bool isAlerting()const;

};





#endif //MISSILEALERT_H
