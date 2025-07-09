#include "SpriteComponent.h"

void SpriteComponent::ImGuiUpdate() {
  this->TransformImGuiUpdate();

  if (GetJsonName()) {
    JsonImGuiUpdate();
  }
}

void SpriteComponent::Draw() { sprite_->Draw(); }

void SpriteComponent::Create() {
  WTCreate(1);

  this->SetScale(this->scale_);
  this->SetRotate(this->rotate_);
  this->SetTranslate(this->translate_);

  this->sprite_ = std::make_shared<CLEYERA::Sprite2d::Sprite>();
  sprite_->Create();
  sprite_->SetAnker(this->anker);
  sprite_->SetSize(this->size);
  sprite_->SetTexHandle(handle_);

  sprite_->SetWorldbindFunc([this](UINT n) { this->BindWT(n); });
}

void SpriteComponent::CreateJsonSystem(const std::string &fileGroupName) {
  CreateJson(name_, fileGroupName);

  // 各パラメータの保存
  this->SetValue<decltype(scale_)>(VAR_NAME(scale_), scale_);
  this->SetValue<decltype(rotate_)>(VAR_NAME(rotate_), rotate_);
  this->SetValue<decltype(translate_)>(VAR_NAME(translate_), translate_);
  this->SetValue<decltype(size)>(VAR_NAME(size), size);
  this->SetValue<decltype(anker)>(VAR_NAME(anker), anker);

  // 各パラメータの読込
  scale_ = this->GetValue<decltype(scale_)>(VAR_NAME(scale_));
  rotate_ = this->GetValue<decltype(rotate_)>(VAR_NAME(rotate_));
  translate_ = this->GetValue<decltype(translate_)>(VAR_NAME(translate_));
  size = this->GetValue<decltype(size)>(VAR_NAME(size));
  anker = this->GetValue<decltype(anker)>(VAR_NAME(anker));
}
