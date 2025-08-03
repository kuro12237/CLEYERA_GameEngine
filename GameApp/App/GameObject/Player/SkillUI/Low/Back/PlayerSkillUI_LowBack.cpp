#include "PlayerSkillUI_LowBack.h"

void PlayerSkillUI_LowBack::Init()
{
	this->Create();
	this->GetJsonName();
	this->CreateJsonSystem("PlayerSkillUI_LowBack");
	uint32_t handle = texManager_->LoadPngTex("UI/Low_Attack_Normal");
	handle_ = handle;
}

void PlayerSkillUI_LowBack::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}
