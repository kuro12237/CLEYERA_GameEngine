#include "PlayerSkillUI_LowNormal.h"

void PlayerSkillUI_LowNormal::Init()
{
	this->Create();
	this->GetJsonName();
	this->CreateJsonSystem("PlayerSkillUI_LowNormal");
	uint32_t handle = texManager_->LoadPngTex("UI/Low_Attack_Normal");
	handle_ = handle;
}

void PlayerSkillUI_LowNormal::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}