#pragma once
#include "../Scene/IScene.h"
#include "IPlayerHpUI.h"

class PlayerHpUI_Heart : public IPlayerHpUI {

public:

	PlayerHpUI_Heart() = default;
	~PlayerHpUI_Heart() = default;

	void Init() override {
		this->Create();
		this->GetJsonName();
		uint32_t handle = texManager_->LoadPngTex("hp/HPHato");
		handle_ = handle;
	}
	void Update() override {
		sprite_->Update();
		WorldMatUpdate();
	}

};
