#include "PlayerSkillUI_HighNormal.h"

void PlayerSkillUI_HighNormal::Init()
{
	this->Create();
	this->GetJsonName();
	this->CreateJsonSystem("PlayerSkillUI_HighNormal");
	uint32_t handle = texManager_->LoadPngTex("UI/High_Attack_Normal");
	handle_ = handle;
}

void PlayerSkillUI_HighNormal::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}
