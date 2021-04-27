#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}

  GameElement(const int &x, const int &y, const int width, const int &height)
      : x_(x), y_(y), width_(width), height_(height), is_active(true) {}

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  int GetX() const { return x_; }
  int GetY() const { return y_; }
  void SetX(const int &x) { x_ = x; }
  void SetY(const int &y) { y_ = y; }

  bool GetIsActive() const { return is_active; }
  void SetIsActive(const bool &active) { is_active = active; }

  void Helper(graphics::Image &background, std::string &skin, int x_, int y_);

  bool IntersectsWith(GameElement* object);
  bool IsOutOfBounds(const graphics::Image &gameScreen);
  virtual void Draw(graphics::Image &background) = 0;
  virtual void Move(const graphics::Image &gameScreen) = 0;
 protected:
  int width_, height_, x_, y_;
  bool is_active;
};

#endif
