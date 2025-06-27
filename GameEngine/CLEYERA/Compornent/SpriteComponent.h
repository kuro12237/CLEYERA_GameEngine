#pragma once
#include "2d/Sprite.h"
#include"Utility/World/WorldTransform.h"

class SpriteComponent :public CLEYERA::Util::WorldTransform{
public:
  SpriteComponent() { texManager_ = CLEYERA::Manager::TexManager::GetInstance(); };
  virtual ~SpriteComponent() {};

#pragma region VirtualFunc

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void ImGuiUpdate();
#pragma endregion

  /// <summary>
  /// 描画
  /// </summary>
  void Draw();

  void Create();


private:
protected:

	CLEYERA::Manager::TexManager *texManager_ = nullptr;

  std::shared_ptr<CLEYERA::Sprite2d::Sprite> sprite_;

  Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
  Math::Vector::Vec3 rotate_ = {};
  Math::Vector::Vec3 translate_ = {};

  Math::Vector::Vec2 size = {1280.0f,1280.0f};
  Math::Vector::Vec2 anker = {0.5f, 0.5f};

  uint32_t handle_ = 0;
};
