//
// Created by Vlad on 03-Dec-24.
//

#ifndef COINS_H
#define COINS_H

#include <Object.h>
#include <random>
class Coin : public Object {
private:
  float speed;           // Speed at which the coin moves
  sf::Vector2f position; // Position of the coin

  // Helper function for random float generation
  static float randomFloat(float min, float max);

public:
  Coin(const std::string& textureFile);
  ~Coin() override;

  void updateMovement(float offsetX, float offsetY);

  // Override methods
  void update() override;
  void render(sf::RenderTarget& target) const override;

  // Spawn coin at a specific position
  void spawnAt(float x, float y);

  float getY() const;
  float getX() const;

  float getWidth() const;
};


#endif //COINS_H
