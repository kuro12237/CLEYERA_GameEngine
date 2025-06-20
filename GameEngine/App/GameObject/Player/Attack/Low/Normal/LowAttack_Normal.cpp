#include "LowAttack_Normal.h"


void LowAttack_Normal::Init()
{
	// コンボのMax
	comboMax_ = 3;
	// 攻撃ステップの初期値
	comboStep_ = 0;
	// コンボ間インターバルの初期値
	comboInterval_ = 60.0f;
	// コンボの進行
	comboElapse_ = 0.0f;
}

void LowAttack_Normal::Update()
{

}

void LowAttack_Normal::Reset()
{

}

void LowAttack_Normal::IsAttack()
{
	// 弾を発射
	FireBullet();

	// コンボ進行
	comboStep_ = (comboStep_ + 1) % comboMax_;
	comboElapse_ = comboInterval_;
}

void LowAttack_Normal::DrwaImGui()
{

}

void LowAttack_Normal::FireBullet()
{

}