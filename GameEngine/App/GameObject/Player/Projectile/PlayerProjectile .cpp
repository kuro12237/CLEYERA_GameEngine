#include "PlayerProjectile .h"

void PlayerProjectile::Update() {
  //座標を更新
	translate_ += velocity_;
	
	// 更新
  TransformUpdate();
}
