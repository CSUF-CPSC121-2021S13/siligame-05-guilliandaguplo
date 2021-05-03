#include "game_element.h"

#include "cpputils/graphics/image.h"


bool GameElement::IntersectsWith(GameElement* object) {
  if (!(GetX() > object->GetX() + object->GetWidth() ||
        GetX() + GetWidth() < object->GetX() ||
        GetY() > object->GetY() + object->GetHeight() ||
        GetY() + GetHeight() < object->GetY()))
    return true;
  else
    return false;
}
bool GameElement::IsOutOfBounds(const graphics::Image &gameScreen) {
  return GetX() < 0 || GetY() < 0 || GetX() + GetWidth() > gameScreen.GetWidth() ||
         GetY() + GetHeight() > gameScreen.GetHeight();
}
void GameElement::Helper(graphics::Image &background, std::string &skin, int x_, int y_) {
   graphics::Image drawing;
   drawing.Load(skin);
   for (int i = 0; i < drawing.GetWidth(); i++) {
     for (int j = 0; j < drawing.GetHeight(); j++) {
       if (drawing.GetColor(i,j) != graphics::Color(0, 0, 0)) {
         background.SetColor(i + x_, j + y_, drawing.GetColor(i,j));
       } else {
         continue;
       }
     }
   }
}
