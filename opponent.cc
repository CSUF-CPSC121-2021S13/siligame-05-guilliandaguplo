#include "opponent.h"
#include <iostream>

void Opponent::Decide() {
  if (skin == "null") {
    skin = "opponent1.bmp";
  }
 // } else if (skin == "opponent1.bmp") {
 //    skin = "opponent2.bmp";
 //  } else if (skin == "opponent2.bmp") {
 //    skin = "opponent3.bmp";
 //  } else if (skin == "opponent3.bmp") {
 //    skin = "opponent4.bmp";
 //  } else if (skin == "opponent4.bmp") {
 //    skin = "opponent1.bmp";
 //  }
 }
 void Opponent::Move(const graphics::Image &gameScreen) {
   x_ += 1;
   y_ += 1;
   if (IsOutOfBounds(gameScreen)) SetIsActive(false);
 }
 void OpponentProjectile::Move(const graphics::Image &gameScreen) {
    y_ += 22; // Temp
    if (IsOutOfBounds(gameScreen)) SetIsActive(false);
     // std::cout << "Error: unable to move OpponentProjectile object\n";
}
void Opponent::Draw(graphics::Image &background) {
  int x, y;
  x = GetX();
  y = GetY();
  Decide();
  Helper(background, skin, x, y);
}
void OpponentProjectile::Draw(graphics::Image &background) {
  int x, y;
  x = GetX();
  y = GetY();
  skin = "poop.bmp";
  Helper(background, skin, x, y);
}
