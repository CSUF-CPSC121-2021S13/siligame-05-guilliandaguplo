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
  Opponent(const int &x, const int &y) : GameElement(x, y, 40, 40), count(0) {}

  void Decide();
  void Draw(graphics::Image &background) override;
  void Move(const graphics::Image &gameScreen) override;

  std::unique_ptr<OpponentProjectile> LaunchProjectile() {
    if (count == 35) {
      std::unique_ptr<OpponentProjectile> oshot = std::make_unique<OpponentProjectile>(GetX() + (GetWidth()/2), GetY() + GetHeight());
      count = 0;
      return std::move(oshot);
    } else {
      count++;
      return nullptr;
    }
  }
  private:
    int count;
    std::vector<std::unique_ptr<graphics::Image> > skins;
};


#endif
