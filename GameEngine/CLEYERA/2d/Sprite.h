#pragma once
#include "Utility/Camera/CameraManager.h"
#include "pch/pch.h"

namespace CLEYERA {
namespace Sprite2d {
/// <summary>
/// 2dSpriteClass
/// </summary>
class Sprite {
public:
  Sprite();
  ~Sprite() {};

  void Create();

  void TransfarBuf();

  void Draw();

#pragma region Set
  void SetSRT(const Math::Vector::Vec3 &s, const Math::Vector::Vec3 &r,
              const Math::Vector::Vec3 &t) {
    this->scale_ = &s;
    this->rotate_ = &r;
    this->translate_ = &t;
  }
  void SetTexHandle(const uint32_t &handle) { this->texHandle_ = &handle; };
  void SetSize(const Math::Vector::Vec2 &size) { this->size_ = &size; };
  void SetAnker(const Math::Vector::Vec2 &anker) { this->anker_ = &anker; };

#pragma endregion

private:
  Manager::CameraManager *cameraManager = nullptr;

  const Math::Vector::Vec3 *scale_ = nullptr;
  const Math::Vector::Vec3 *rotate_ = nullptr;
  const Math::Vector::Vec3 *translate_ = nullptr;

  const Math::Vector::Vec2 *size_ = nullptr;
  const Math::Vector::Vec2 *anker_ = nullptr;

  const uint32_t *texHandle_ = nullptr;

  // Buf
};
} // namespace Sprite2d
} // namespace CLEYERA