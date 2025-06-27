#include "SpriteComponent.h"

void SpriteComponent::ImGuiUpdate() {

	this->TransformImGuiUpdate(); }

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

