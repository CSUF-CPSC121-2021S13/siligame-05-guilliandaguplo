#include "player.h"
void Player::Decide() {
  if (skin == "null") {
    skin = "player1.bmp";
  } //else if (skin == "player1.bmp") {
  //   skin = "player2.bmp";
  // } else if (skin == "player2.bmp") {
  //   skin = "player3.bmp";
  // } else if (skin == "player3.bmp") {
  //   skin = "player4.bmp";
  // } else if (skin == "player4.bmp") {
  //   skin = "player5.bmp";
  // } else if (skin == "player5.bmp") {
  //   skin = "player6.bmp";
  // } else if (skin == "player6.bmp") {
  //   skin = "player7.bmp";
  // } else if (skin == "player7.bmp") {
  //   skin = "player8.bmp";
  // } else if (skin == "player8.bmp") {
  //   skin = "player9.bmp";
  // } else if (skin == "player9.bmp") {
  //   skin = "player1.bmp";
  // }
  }

void Player::Draw(graphics::Image &background) {
  int x, y;
  x = GetX();
  y = GetY();
  Decide();
  Helper(background, skin, x, y);
}
void PlayerProjectile::Draw(graphics::Image &background) {
  int x, y;
  x = GetX();
  y = GetY();
  skin = "banana.bmp";
  Helper(background, skin, x, y);
}

void Player::Move(const graphics::Image &gameScreen) {}
void PlayerProjectile::Move(const graphics::Image &gameScreen) {
  if (!IsOutOfBounds(gameScreen)) {
   y_ -= 20; // Temp
  } else {
    SetIsActive(false);
    // std::cout << "Error: unable to move PlayerProjectile object\n";
  }
}
