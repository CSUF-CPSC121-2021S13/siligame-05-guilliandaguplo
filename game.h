#include <iostream>
// #include "game_element.h"
#include "opponent.h"
#include "player.h"
#include "cpputils/graphics/image_event.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener, public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) : gameState(false), score_(0) {
    gameScreen.Initialize(width, height);
  }
  void CreateOpponents();
  void LaunchProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent &event) override;
  bool HasLost() const { return gameState; }
  int GetScore() const { return score_; }
  void RemoveInactive();

  // Accessors
  graphics::Image &GetGameScreen() { return gameScreen; }
  std::vector<std::unique_ptr<Opponent> > &GetOpponents() { return olist; }
  std::vector<std::unique_ptr<OpponentProjectile> > &GetOpponentProjectiles() { return oshots_; }
  std::vector<std::unique_ptr<PlayerProjectile> > &GetPlayerProjectiles() { return pshots_; }
  Player &GetPlayer() { return player_; }

 private:
  graphics::Image gameScreen;
  std::vector<std::unique_ptr<Opponent> > olist;
  std::vector<std::unique_ptr<OpponentProjectile> > oshots_;
  std::vector<std::unique_ptr<PlayerProjectile> > pshots_;
  Player player_;
  int score_;
  bool gameState;
};

#endif
