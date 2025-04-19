#include "PlayerBullet.h"

void PlayerBullet::Init() { this->CreateCollider(ColliderType::OBB); }

void PlayerBullet::Update() {

   CalcAliveTimer();

   TransformUpdate();
}
