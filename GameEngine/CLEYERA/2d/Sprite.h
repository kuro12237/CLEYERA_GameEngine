#pragma once
#include "SpriteMesh.h"
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

  void Update();

#pragma region Set

  void SetTexHandle(const uint32_t &handle) { this->texHandle_ = &handle; };
  void SetSize(const Math::Vector::Vec2 &size) { this->size_ = &size; };
  void SetAnker(const Math::Vector::Vec2 &anker) { this->anker_ = &anker; };

#pragma endregion

private:
  Manager::CameraManager *cameraManager = nullptr;

  const Math::Vector::Vec2 *size_ = nullptr;
  const Math::Vector::Vec2 *anker_ = nullptr;

  const uint32_t *texHandle_ = nullptr;

  std::vector<System::Mesh2d> meshData_;

  // Buf
  std::unique_ptr<System::SpriteMesh> mesh_ = nullptr;
};
} // namespace Sprite2d
} // namespace CLEYERA