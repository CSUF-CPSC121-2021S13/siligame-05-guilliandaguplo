#include "player.h"

void Player::Draw(graphics::Image &background) {
  std::string skin;
  int x, y;
  x = GetX();
  y = GetY();
  skin = "player.bmp";
    Helper(background, skin, x, y);
}
void PlayerProjectile::Draw(graphics::Image &background) {
  std::string skin;
  int x, y;
  x = GetX();
  y = GetY();
  skin = "banana.bmp";
  Helper(background, skin, x, y);
}

void Player::Move(const graphics::Image &gameScreen) {}
void PlayerProjectile::Move(const graphics::Image &gameScreen) {
  if (!IsOutOfBounds(gameScreen)) {
   y_ -= 3; // Temp
  } else {
    SetIsActive(false);
    // std::cout << "Error: unable to move PlayerProjectile object\n";
  }
}
