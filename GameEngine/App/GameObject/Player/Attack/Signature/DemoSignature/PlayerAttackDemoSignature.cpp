#include "PlayerAttackDemoSignature.h"
#include "../../../Attack/Manager/PlayerBulletManager.h"
#include "../../../Core/playerCore.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackDemoSignature::PlayerAttackDemoSignature(PlayerCore * corePtr,
													 std::weak_ptr<PlayerBulletManager> bulManagerPtr) {
	IMagicAttack::SetPre(corePtr, bulManagerPtr);
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerAttackDemoSignature::Init() {}

/// <summary>
/// 更新処理
/// </summary>
void PlayerAttackDemoSignature::Update() {}

/// <summary>
/// リセット
/// </summary>
void PlayerAttackDemoSignature::Reset() {}

/// <summary>
/// 攻撃処理
/// </summary>
void PlayerAttackDemoSignature::IsAttack() {

	std::string tag = VAR_NAME(PlayerDemoSignatureBullet);

	char name[ 32 ];

	auto pos = owner_->GetWorldPos();
	auto forward = owner_->GetForwardVec(); // プレイヤーの正面方向（単位ベクトル）

	// 方向数が1以下なら正面だけ撃つ
	int count = directionCount_ > 0 ? directionCount_ : 1;

	// 360度をcount分割した角度
	float angleStep = 2.0f * float(std::numbers::pi) / float(count);

	for ( int i = 0; i < count; ++i ) {
		float angle = angleStep * i;

		if ( bulletCount_ == 0 ) {

			// forwardベクトルをY軸周りに回転させる（弾の発射方向）
			Math::Vector::Vec3 dir = RotateAroundAxis(forward, { 0, 1, 0 }, angle);
			float bulletSpeed = 0.3f; // 好きな速さに調整
			dir.x *= bulletSpeed;
			dir.y *= bulletSpeed;
			dir.z *= bulletSpeed;

			auto newBul = std::make_shared<PlayerDemoSignatureBullet>();
			newBul->SetPosition(pos);
			newBul->SetVelocity(IMagicAttack::CalcVelocity(dir));
			newBul->Init();
			newBul->SetName(tag);
			bulletManager_.lock()->PushbackNewBullet(std::move(newBul));

		}
		else {
			std::snprintf(name, sizeof(name), "PlayerDemoBullet.%03zu", bulletCount_);
			// forwardベクトルをY軸周りに回転させる（弾の発射方向）
			Math::Vector::Vec3 dir = RotateAroundAxis(forward, { 0, 1, 0 }, angle);
			float bulletSpeed = 0.3f; // 好きな速さに調整
			dir.x *= bulletSpeed;
			dir.y *= bulletSpeed;
			dir.z *= bulletSpeed;

			auto newBul = std::make_shared<PlayerDemoSignatureBullet>();
			newBul->SetPosition(pos);
			newBul->SetVelocity(IMagicAttack::CalcVelocity(dir));
			newBul->Init();
			newBul->SetName(name);
			bulletManager_.lock()->PushbackNewBullet(std::move(newBul));
		}

		bulletCount_++;
	}
}

/// <summary>
/// 指定した軸の周りにベクトルを回転させます。
/// </summary>
Math::Vector::Vec3 PlayerAttackDemoSignature::RotateAroundAxis(const Math::Vector::Vec3 & v,
															   const Math::Vector::Vec3 & axis,
															   float angle) {
	// ロドリゲスの回転公式
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	// v*cosA
	Math::Vector::Vec3 term1 = v * cosA;

	// (axis × v)*sinA
	Math::Vector::Vec3 term2 = Math::Vector::Func::Cross(axis, v) * sinA;

	// axis * (axis・v) * (1 - cosA)
	float dot = Math::Vector::Func::Dot(axis, v);
	Math::Vector::Vec3 term3 = axis * dot * (1.0f - cosA);

	return term1 + term2 + term3;
}
