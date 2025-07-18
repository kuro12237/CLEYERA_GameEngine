#include "PlayerDashFunc.h"
#include "../playerCore.h"
#include "../../Camera/PlayerCamera.h"
#include "imgui.h"


PlayerDashFunc::PlayerDashFunc(PlayerCore * pPlayer)
	: p_player_(pPlayer)
{
}

void PlayerDashFunc::Init()
{

}

void PlayerDashFunc::Update()
{
	Dash();
}

void PlayerDashFunc::StartDash()
{
	if ( isDashing_ )
		return; // 既にダッシュ中

	isDashing_ = true;
	dashTimer_ = dashDuration_;

	// ダッシュ開始時に方向ベクトルを設定
	dashForce_ = Math::Vector::Func::Normalize(p_player_->GetForwardVec()) * dashSpeed_;
}

void PlayerDashFunc::Dash()
{
    if ( !isDashing_ )
        return;

    dashTimer_ -= 1.0f / 60.0f;

    // force に dashForce を加える
    p_player_->SetForce(dashForce_); // ← AddForce 関数がなければ、直接合成して SetForce でもOK

    if ( dashTimer_ <= 0.0f )
    {
        isDashing_ = false;
        dashTimer_ = 0.0f;
        dashForce_ = { 0.0f, 0.0f, 0.0f }; // 終了時に0に戻す
    }
}