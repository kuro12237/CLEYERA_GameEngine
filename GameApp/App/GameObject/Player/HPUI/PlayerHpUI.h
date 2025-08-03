#pragma once
#include "CLEYERA.h"

#include "IPlayerHpUI.h"
#include "PlayerHpUI_Frame.h"
#include "PlayerHpUI_Gauge.h"
#include "PlayerHpUI_Heart.h"

#include <list>

class PlayerCore;
class SceneComponent;

class PlayerHpUI {

public:

	PlayerHpUI() = default;
	~PlayerHpUI() = default;

	void Init();
	void Update();
	void Draw2D();

	void SetPtr(std::weak_ptr<PlayerCore> corePtrm, SceneComponent * scenePtr) {
		p_playerCore_ = corePtrm;
		scene_ = scenePtr;
	}


private:

	std::weak_ptr<PlayerCore> p_playerCore_;
	SceneComponent * scene_ = nullptr;

	std::vector<std::shared_ptr<IPlayerHpUI>> hpUI_;

};
