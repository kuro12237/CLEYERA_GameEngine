#pragma once
#include "../Scene/IScene.h"


class IPlayerSkillUI : public SpriteComponent {

public:

	virtual ~IPlayerSkillUI() = default;

	virtual void Init() {};
	virtual void Update() {};

	void SetTranslate(const Math::Vector::Vec2 & pos) {
		this->translate_ = {
			pos.x, pos.y, 0.0f
		};
	}

protected:
	SceneComponent * scene_ = nullptr;
};