#include "PlayerInvincibleFunc.h"

PlayerInvincibleFunc::PlayerInvincibleFunc(PlayerCore * pPlayer)
{
	p_player_ = pPlayer;
}

void PlayerInvincibleFunc::Init()
{
	isInvincible_ = false;
	invincibleTimer_ = 0.0f;
}

void PlayerInvincibleFunc::Update()
{
	if(!isInvincible_ )
		return;

	invincibleTimer_--;

	if ( invincibleTimer_ <= 0.0f ) {
		invincibleTimer_ = 0.0f;
		isInvincible_ = false;
	}
}

void PlayerInvincibleFunc::AddInvTimer(float addTimer)
{
	invincibleTimer_ = addTimer;
	isInvincible_ = true;
}
