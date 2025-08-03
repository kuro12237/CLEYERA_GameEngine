#pragma once
#include "../Scene/IScene.h"
#include "IPlayerHpUI.h"

class PlayerHpUI_Gauge : public IPlayerHpUI {

public:

	PlayerHpUI_Gauge() = default;
	~PlayerHpUI_Gauge() = default;

	void Init() override {
		this->Create();
		this->GetJsonName();
		uint32_t handle = texManager_->LoadPngTex("hp/HPb");
		handle_ = handle;
	}
	void Update() {
		sprite_->Update();
		WorldMatUpdate();
	}

};