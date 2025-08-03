#include "PlayerSkillUI_SpecialNormal.h"

void PlayerSkillUI_SpecialNormal::Init()
{
	this->Create();
	this->GetJsonName();
	this->CreateJsonSystem("PlayerSkillUI_SpecialNormal");
	uint32_t handle = texManager_->LoadPngTex("UI/Special_Normal");
	handle_ = handle;
}

void PlayerSkillUI_SpecialNormal::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}
