#include "IMagicAttack.h"
#include "../../playerCore.h"

/// <summary>
/// 速度を求める
/// </summary>
Math::Vector::Vec3 IMagicAttack::CalcVelocity(const Math::Vector::Vec3 &vel) {

  return Math::Vector::Func::TransformNormal(vel, owner_->GetMatWorld());
}