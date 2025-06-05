#pragma once
#include "CLEYERA.h"

enum class GameState {
  Play,
  Over,
  Clear,

};

class TestPlayGui : public CLEYERA::Component::ManagerCompornent {
public:
  TestPlayGui() {};
  ~TestPlayGui() {};

  void Init() override;

  void Update() override;

  void ImGuiUpdate() override;

  void SetPlayerHp(const int32_t &hp) { playerHp_ = &hp; }
  void SetEnemyCount(const size_t &count) { enemyCount_ = &count; }

  bool ResetScene() { return resetScene_; }

private:
  const int32_t *playerHp_ = nullptr;
  const size_t *enemyCount_ = nullptr;

  std::string gameStringState_ = "play";

  GameState gameState_ = GameState::Play;

  bool resetScene_ = false;

};
