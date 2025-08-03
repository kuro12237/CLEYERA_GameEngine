#pragma once
#include "../Scene/IScene.h"


class IPlayerHpUI : public SpriteComponent {

public:

	virtual ~IPlayerHpUI() = default;

	virtual void Init() {}
	virtual void Update() {}

	virtual void SetScale(const Math::Vector::Vec2 & scale) {
		this->scale_ = {
			scale.x, scale.y, 0.0f
		};
	}
	virtual void SetTranslate(const Math::Vector::Vec2 & pos) {
		this->translate_ = {
			pos.x, pos.y, 0.0f
		};
	}
	virtual void SetAnker(const Math::Vector::Vec2 & val) {
		this->anker = val;
	}

	// UV座標アクセッサ
	Math::Vector::Vec2 GetLeftTop() const { return LeftTop; }
	void SetLeftTop(const Math::Vector::Vec2 & value) { LeftTop = value; }

	Math::Vector::Vec2 GetRightTop() const { return RightTop; }
	void SetRightTop(const Math::Vector::Vec2 & value) { RightTop = value; }

	Math::Vector::Vec2 GetLeftBottom() const { return LeftBottom; }
	void SetLeftBottom(const Math::Vector::Vec2 & value) { LeftBottom = value; }

	Math::Vector::Vec2 GetRightBottom() const { return RightBottom; }
	void SetRightBottom(const Math::Vector::Vec2 & value) { RightBottom = value; }

	Math::Vector::Vec2 GetSize() const { return size; }
	void SetSize(const Math::Vector::Vec2 & value) { size = value; }

protected:

};