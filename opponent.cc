#include "opponent.h"
#include <iostream>
 void Opponent::Move(const graphics::Image &gameScreen) {

 }
 void OpponentProjectile::Move(const graphics::Image &gameScreen) {
    y_ += 22; // Temp
    if (IsOutOfBounds(gameScreen)) SetIsActive(false);
     // std::cout << "Error: unable to move OpponentProjectile object\n";
}
void Opponent::Draw(graphics::Image &background) {
  std::string skin;
  int x, y;
  x = GetX();
  y = GetY();
  skin = "opponent.bmp";
  Helper(background, skin, x, y);
}
void OpponentProjectile::Draw(graphics::Image &background) {
  std::string skin;
  int x, y;
  x = GetX();
  y = GetY();
  skin = "poop.bmp";
  Helper(background, skin, x, y);
}
