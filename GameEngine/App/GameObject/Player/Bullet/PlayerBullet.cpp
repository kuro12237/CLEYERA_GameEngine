#include "PlayerBullet.h"

void PlayerBullet::Init() { 
	
	
	this->CreateCollider(ColliderType::OBB); 
	auto obb =
            std::dynamic_pointer_cast<CLEYERA::Util::Collider::OBBCollider>(
                collider_);
        obb->SetSize({2.0f, 2.0f, 2.0f});
}

void PlayerBullet::Update() {

   CalcAliveTimer();

   TransformUpdate();
}
