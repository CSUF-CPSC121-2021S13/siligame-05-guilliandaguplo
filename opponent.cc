#include "opponent.h"
#include <iostream>
 void Opponent::Move(const graphics::Image &gameScreen) {
   if (!IsOutOfBounds(gameScreen)) {
    y_ += 1; // Temp
    x_ += 1;
   } else {
     SetIsActive(false);
     // std::cout << "Error: unable to move Opponent object\n";
   }
 }
 void OpponentProjectile::Move(const graphics::Image &gameScreen) {
   if (!IsOutOfBounds(gameScreen)) {
    y_ += 3; // Temp
   } else {
     SetIsActive(false);
     // std::cout << "Error: unable to move OpponentProjectile object\n";
   }
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
