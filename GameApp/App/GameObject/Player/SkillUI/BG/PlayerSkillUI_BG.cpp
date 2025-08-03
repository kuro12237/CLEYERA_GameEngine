#include "PlayerSkillUI_BG.h"

void PlayerSkillUI_BG::Init()
{
	this->Create();
	this->GetJsonName();
	uint32_t handle = texManager_->LoadPngTex("UI/Low_Attack_Normal");
	handle_ = handle;
}

void PlayerSkillUI_BG::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}
