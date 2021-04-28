#ifndef OPPONENT_H
#define OPPONENT_H

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include <stdlib.h>


class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : GameElement(0, 0, 15, 15) {}
  OpponentProjectile(const int &x, const int &y) : GameElement(x, y, 15, 15) {}

  void Draw(graphics::Image &background) override;
  void Move(const graphics::Image &gameScreen) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : GameElement(0, 0, 50, 50) {}
  Opponent(const int &x, const int &y) : GameElement(x, y, 40, 40) {}

  void Draw(graphics::Image &background) override;
  void Move(const graphics::Image &gameScreen) override;

  std::unique_ptr<OpponentProjectile> LaunchProjectile() {
    if (count != 200) {
      count++;
      return nullptr;
    } else if (count == 200) {
      std::unique_ptr<OpponentProjectile> oshot = std::make_unique<OpponentProjectile>(x_+ width_/2, y_ + height_);
      count = 0;
    return std::move(oshot);
    }
    return nullptr;
  }
  private:
    int count = 0;
    std::vector<std::unique_ptr<OpponentProjectile>> oshots_;
};

#endif
