#include "PlayState.h"

void PlayUIState::Init() {

  this->scene_->SpriteListPush(this->lowAttack_ =
                                   std::make_shared<GameLowAttackUI>());
  lowAttack_->SetName(VAR_NAME(GameLowAttackUI));

  skillBacks_.resize(skillNum_);
  for (size_t i = 0; i < this->skillNum_; i++) {

    this->scene_->SpriteListPush(this->skillBacks_[i] =
                                     std::make_shared<GameSkillBackUI>());
    std::string name = VAR_NAME(GameSkillBackUI) + std::to_string(i);
    skillBacks_[i]->SetName(name);
  }

  scene_->SpriteListPush(test_ = std::make_shared<TestUI>());

}

void PlayUIState::Update() {}

void PlayUIState::Draw2d() {

  for (auto skillBack : skillBacks_) {

    skillBack->Draw();
  }

  lowAttack_->Draw();

  test_->Draw();
}
