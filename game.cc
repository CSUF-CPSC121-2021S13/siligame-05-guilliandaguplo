#include "game.h"
#include "opponent.h"
#include "player.h"
#include <iostream>
#include <stdlib.h>

const int kAnimationMs = 80;

void Game::CreateOpponents() {
    int x = rand() % 700 + 1;
    int y = rand() % 300 + 1;
    olist.push_back(std::make_unique<Opponent>(x,y));

}
void Game::Init() {
  GetGameScreen().AddMouseEventListener(*this);
  GetGameScreen().AddAnimationEventListener(*this);
  player_.SetX(400);
  player_.SetY(500);
}
void Game::Start() {
  gameScreen.ShowUntilClosed("Hate it here", kAnimationMs);
}

void Game::MoveGameElements() {
  for (int i = 0; i < olist.size(); i++) {
    if (olist[i]->GetIsActive())
    olist[i]->Move(GetGameScreen());
  }
  for (int i = 0; i < oshots_.size(); i++) {
    if (oshots_[i]->GetIsActive())
    oshots_[i]->Move(GetGameScreen());
  }
  for (int i = 0; i < pshots_.size(); i++) {
    if (pshots_[i]->GetIsActive())
    pshots_[i]->Move(GetGameScreen());
  }
}
void Game::LaunchProjectiles() {
   for (int i = 0; i < GetOpponents().size(); i++) {
    if (olist[i]->GetIsActive()) {
      std::unique_ptr<OpponentProjectile> oshot = olist[i]->LaunchProjectile();
      if (oshot != nullptr) {
        oshots_.push_back(std::move(oshot));
      } else continue;
    }
  }
}
void Game::RemoveInactive() {
  for (int i = olist.size() - 1; i >= 0; i--) {
    if (!(olist[i]->GetIsActive())) {
      olist.erase(olist.begin() + (i));
    }
  }
  for (int i = oshots_.size(); i > 0; i--) {
      if (!(oshots_[i-1]->GetIsActive())) {
      oshots_.erase(oshots_.begin() + (i-1));
    } else continue;
    }
  for (int i = pshots_.size(); i > 0; i--) {
      if (!(pshots_[i-1]->GetIsActive())) {
      pshots_.erase(pshots_.begin() + (i-1));
    } else continue;
  }
}
void Game::FilterIntersections() {
  for (int i = 0; i < olist.size(); i++) {
    if (GetPlayer().IntersectsWith(olist[i].get())) {
      GetPlayer().SetIsActive(false);
      olist[i]->SetIsActive(false);
      gameState = true;
    }
  }
  for (int i = 0; i < olist.size(); i++) {
    for (int j = 0; j < pshots_.size(); j++) {
      if (olist[i]->IntersectsWith(pshots_[j].get())) {
        pshots_[j]->SetIsActive(false);
        olist[i]->SetIsActive(false);
        if (player_.GetIsActive()) score_ += 1;
      }
    }
  }
  for (int i = 0; i < oshots_.size(); i++) {
    if (player_.IntersectsWith(oshots_[i].get())) {
      oshots_[i]->SetIsActive(false);
      GetPlayer().SetIsActive(false);
      gameState = true;
  }
 }
}
void Game::UpdateScreen() {
  if (!(HasLost())) {
  // LoadMap();
  gameScreen.DrawRectangle(0,0, gameScreen.GetWidth(), gameScreen.GetHeight(), graphics::Color(255, 255, 255));
  std::string score = "Score: ";
  score + std::to_string(GetScore());
  gameScreen.DrawText(0,0, score, 32, graphics::Color(0,0,0));
  if (player_.GetIsActive()) player_.Draw(gameScreen);
  for (int i = 0; i < olist.size(); i++) {
      if (olist[i]->GetIsActive() && !(olist[i]->IsOutOfBounds(gameScreen))) {
        olist[i]->Draw(gameScreen);
      }
    }
    for (int i = 0; i < oshots_.size(); i++) {
      if (oshots_[i]->GetIsActive() && !(oshots_[i]->IsOutOfBounds(gameScreen))) {
        oshots_[i]->Draw(gameScreen);
      }
    }
    for (int i = 0; i < pshots_.size(); i++) {
      if (pshots_[i]->GetIsActive() && !(pshots_[i]->IsOutOfBounds(gameScreen))) {
        pshots_[i]->Draw(gameScreen);
      }
    }
  } else {
  gameScreen.DrawText(gameScreen.GetWidth()/2,gameScreen.GetHeight()/2, "GAME OVER", 50, graphics::Color(0,0,0));
}
}

void Game::OnAnimationStep() {
  if (olist.size() == 0) {
    int x = rand() % 50;
    for (int i = 0; i < x; i++) {
      CreateOpponents();
    }
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  GetGameScreen().Flush();
  // std::cout << olist.size() << std::endl << oshots_.size() << std::endl << pshots_.size() << std::endl;
}
void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - player_.GetWidth() / 2;
    int new_y = event.GetY() - player_.GetHeight() / 2;
    int old_x = player_.GetX();
    int old_y = player_.GetY();

    player_.SetX(new_x);
    player_.SetY(new_y);

    if (player_.IsOutOfBounds(gameScreen)) {
      player_.SetX(old_x);
      player_.SetY(old_y);
    }
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed || event.GetMouseAction() == graphics::MouseAction::kDragged) {
      /* code */
    std::unique_ptr<PlayerProjectile> pshot = std::make_unique<PlayerProjectile>(GetPlayer().GetX()+(GetPlayer().GetWidth()/2), GetPlayer().GetY());
    GetPlayerProjectiles().push_back(std::move(pshot));
  }
}
