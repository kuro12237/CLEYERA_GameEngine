#pragma once
#include "pch/pch.h"

/// <summary>
/// 2dSpriteClass
/// </summary>
class Sprite {
public:
  Sprite() {};
  ~Sprite() {};

  void Create();

  void TransfarBuf();

  void Draw();

#pragma region Set
  void SetTexHandle(const uint32_t &handle);
#pragma endregion

private:
  const Math::Vector::Vec3 *scale_ = nullptr;
  const Math::Vector::Vec3 *rotate_ = nullptr;
  const Math::Vector::Vec3 *translate_ = nullptr;

  const Math::Vector::Vec2 *size_ = nullptr;
  const Math::Vector::Vec2 *anker_ = nullptr;

  const uint32_t *texHandle_ = nullptr;

  // Buf
};
