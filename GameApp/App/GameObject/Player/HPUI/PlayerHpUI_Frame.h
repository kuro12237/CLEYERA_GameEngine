#pragma once
#include "../Scene/IScene.h"
#include "IPlayerHpUI.h"

class PlayerHpUI_Frame : public IPlayerHpUI {

public:

	PlayerHpUI_Frame() = default;
	~PlayerHpUI_Frame() = default;

	void Init() override {
		this->Create();
		this->GetJsonName();
		uint32_t handle = texManager_->LoadPngTex("hp/HP");
		handle_ = handle;
	}
	void Update() {
		sprite_->Update();
		WorldMatUpdate();
	}

};