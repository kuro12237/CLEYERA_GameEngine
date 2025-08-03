#pragma once
#include "../Scene/IScene.h"


class IPlayerSkillUI : public SpriteComponent {

public:

	virtual ~IPlayerSkillUI() = default;

	virtual void Init() {};
	virtual void Update() {};

	void SetScale(const Math::Vector::Vec2 & scale) {
		this->scale_ = {
			scale.x, scale.y, 0.0f
		};
	}
	void SetTranslate(const Math::Vector::Vec2 & pos) {
		this->translate_ = {
			pos.x, pos.y, 0.0f
		};
	}

	bool GetActive() const {return isActive_;}
	void SetActive(bool state) {isActive_ = state;}

protected:
	SceneComponent * scene_ = nullptr;

	bool isActive_ = false;
};