#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player() : GameElement(0, 0, 50, 50) {}
  Player(const int &x, const int &y) : GameElement(x, y, 40, 40) {}
  void Decide();
  void Draw(graphics::Image &background) override;
  void Move(const graphics::Image &gameScreen) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : GameElement(0, 0, 15, 15) {}
  PlayerProjectile(const int &x, const int &y) : GameElement(x, y, 15, 15) {}

  void Draw(graphics::Image &background) override;
  void Move(const graphics::Image &gameScreen) override;
};

#endif
