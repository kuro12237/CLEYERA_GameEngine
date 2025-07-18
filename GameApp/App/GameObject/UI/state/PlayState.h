#pragma once
#include "IuiState.h"

#include "../Scene/GameScene.h"

#include "../GameLowAttackUI.h"
#include "../GameSkillBackUI.h"

class PlayUIState : public IuiState {
public:
  PlayUIState() {};
  ~PlayUIState() {};

  void Init() override;

  void Update() override;

  void Draw2d() override;

private:
  const size_t skillNum_ = 3;

  std::shared_ptr<GameLowAttackUI> lowAttack_ = nullptr;
  std::vector<std::shared_ptr<GameSkillBackUI>> skillBacks_;
};
