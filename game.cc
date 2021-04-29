#include "game.h"
#include "opponent.h"
#include "player.h"
#include <iostream>
#include <stdlib.h>

void Game::CreateOpponents() {

    int x = rand() % 800 + 1;
    int y = rand() % 350 + 1;
    // std::unique_ptr<Opponent> opp = std::make_unique<Opponent>(x,y);
    // std::unique_ptr<Opponent> opPush = std::move(opp);
    olist.push_back(std::make_unique<Opponent>(x,y));

}
void Game::Init() {
  GetGameScreen().AddMouseEventListener(*this);
  GetGameScreen().AddAnimationEventListener(*this);
  player_.SetX(400);
  player_.SetY(500);
}
void Game::Start() {
  gameScreen.ShowUntilClosed();
}

void Game::MoveGameElements() {
  for (size_t i = 0; i < olist.size(); i++) {
    if (olist[i]->GetIsActive())
    olist[i]->Move(GetGameScreen());
  }
  for (size_t i = 0; i < oshots_.size(); i++) {
    if (olist[i]->GetIsActive())
    oshots_[i]->Move(GetGameScreen());
  }
  for (size_t i = 0; i < pshots_.size(); i++) {
    if (olist[i]->GetIsActive())
    pshots_[i]->Move(GetGameScreen());
  }
}
void Game::LaunchProjectiles() {
  int size = GetOpponents().size();
  for (size_t i = 0; i < size; i++) {
    std::unique_ptr<OpponentProjectile> oshot = std::move(olist[i]->LaunchProjectile());
    if (oshot != nullptr) {
      oshots_.push_back(std::move(oshot));
      std::cout << oshots_.size() << std::endl;
    } else {
      continue;
    }
  }
}
void Game::RemoveInactive() {
  for (size_t i = 0; i < olist.size(); i++) {
    if (!(olist[i]->GetIsActive())) {
      olist.erase(olist.begin() + i);
      std::cout << olist.size() << ' ';
    }
  }
  for (size_t i = 0; i < oshots_.size(); i++) {
      if (!(oshots_[i]->GetIsActive()))
      oshots_.erase(oshots_.begin() + i);
    }
  }
void Game::FilterIntersections() {
  for (size_t i = 0; i < olist.size(); i++) {
    if (GetPlayer().IntersectsWith(olist[i].get())) {
      GetPlayer().SetIsActive(false);
      olist[i]->SetIsActive(false);
      gameState = true;
    }
  }
  for (size_t i = 0; i < olist.size(); i++) {
    for (size_t j = 0; j < pshots_.size(); j++) {
      if (olist[i]->IntersectsWith(pshots_[j].get())) {
        pshots_[j]->SetIsActive(false);
        olist[i]->SetIsActive(false);
        score_ += 1;
      }
    }
  }
  for (size_t i = 0; i < oshots_.size(); i++) {
    if (player_.IntersectsWith(oshots_[i].get())) {
      oshots_[i]->SetIsActive(false);
      GetPlayer().SetIsActive(false);
      gameState = true;
  }
 }
}
void Game::UpdateScreen() {
  if (!(HasLost())) {
  GetGameScreen().DrawRectangle(0,0,GetGameScreen().GetWidth(),GetGameScreen().GetHeight(), graphics::Color(255, 255, 255));
  std::string score = "Score: ";
  score + std::to_string(GetScore());
  gameScreen.DrawText(0,0, score, 32, graphics::Color(0,0,0));
  if (player_.GetIsActive()) player_.Draw(gameScreen);
  for (int i = 0; i < olist.size(); i++) {
    if (olist[i]->GetIsActive()) olist[i]->Draw(gameScreen);
    else continue;
  }
  for (int i = 0; i < oshots_.size(); i++) {
    if (oshots_[i]->GetIsActive()) oshots_[i]->Draw(gameScreen);
    else continue;
  }
  for (int i = 0; i < pshots_.size(); i++) {
    if (pshots_[i]->GetIsActive()) pshots_[i]->Draw(gameScreen);
    else continue;
  }
} else {
  gameScreen.DrawText(gameScreen.GetWidth()/2,gameScreen.GetHeight()/2, "GAME OVER", 50, graphics::Color(0,0,0));
}
}

void Game::OnAnimationStep() {
  if (olist.size() == 0) {
    int x = rand() % 11;
    for (size_t i = 0; i < x; i++) {
      CreateOpponents();
    }
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  GetGameScreen().Flush();
}
void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetX() >= 0 && event.GetY() >= 0 && event.GetX() <= gameScreen.GetWidth() && gameScreen.GetHeight()) {
    GetPlayer().SetX(event.GetX() - (player_.GetWidth()/2));
    GetPlayer().SetY(event.GetY() - (player_.GetHeight()/2));
  } else if (event.GetMouseAction() == graphics::MouseAction::kPressed && event.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> pshot = std::make_unique<PlayerProjectile>(GetPlayer().GetX()+(GetPlayer().GetWidth()/2), GetPlayer().GetY() + GetPlayer().GetHeight());
    pshots_.push_back(std::move(pshot));
  }
}

// void Game::CreatePlayerProjectiles() {
  //   std::unique_ptr<PlayerProjectile> pshot = std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY())
  //   pshots_.push_back(pshot);
  // }
