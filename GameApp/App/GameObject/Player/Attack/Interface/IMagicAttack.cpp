#include "IMagicAttack.h"
#include "../../Core/playerCore.h"


/// <summary>
/// クールダウン開始
/// </summary>
void IMagicAttack::SetAttackCoolDown()
{
	isAttackCoolDown_ = true;
	coolDownTimer_ = coolDownInterval_;
}

/// <summary>
/// クールダウンタイマーの更新
/// </summary>
void IMagicAttack::UpdateCoolDownTimer()
{
	if ( isAttackCoolDown_ ) {

		coolDownTimer_--;

		if ( coolDownTimer_ <= 0.0f ) {
			isAttackCoolDown_ = false;
			coolDownTimer_ = 0.0f;
		}
	}
}

/// <summary>
/// 速度を求める
/// </summary>
Math::Vector::Vec3 IMagicAttack::CalcVelocity(const Math::Vector::Vec3 &vel) {

  return Math::Vector::Func::TransformNormal(vel, owner_->GetMatWorld());
}