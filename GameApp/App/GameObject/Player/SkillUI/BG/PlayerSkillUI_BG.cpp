#include "PlayerSkillUI_BG.h"

void PlayerSkillUI_BG::Init()
{
	this->Create();
	this->GetJsonName();
	uint32_t handle = texManager_->LoadPngTex("UI/skillBack");
	handle_ = handle;
}

void PlayerSkillUI_BG::Update()
{
	sprite_->Update();
	WorldMatUpdate();
}
