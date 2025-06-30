#pragma once
#include "SpriteMesh.h"
#include "Utility/Camera/CameraManager.h"
#include "pch/pch.h"

#include "../Graphics/TexManager/TexManager.h"
#include "Graphics/RasterPipline/RasterPiplineManager.h"
#include "LayerManager.h"
#include "Utility/World/WorldTransform.h"

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

  void LayerChange(uint32_t newNum) { layerManager_->ChangeLayer(layerNumber_, newNum); }

#pragma region Set

  void SetTexHandle(const uint32_t &handle) { this->texHandle_ = &handle; };
  void SetSize(const Math::Vector::Vec2 &size) { this->size_ = &size; };
  void SetAnker(const Math::Vector::Vec2 &anker) { this->anker_ = &anker; };

  void SetWorldbindFunc(std::function<void(UINT n)> f) { wtCallFunc_ = f; }
#pragma endregion

private:

	using piplineMode = CLEYERA::Graphics::RasterPipline_Mode2d;

  Manager::CameraManager *cameraManager = nullptr;
  System::LayerManager *layerManager_ = nullptr;
  CLEYERA::Base::DX::DXCommandManager *commandManager_ = nullptr;
  Manager::TexManager *texManager_ = nullptr;
  CLEYERA::Graphics::Raster::RasterPiplineManager *piplineManager_;

  const Math::Vector::Vec2 *size_ = nullptr;
  const Math::Vector::Vec2 *anker_ = nullptr;

  const uint32_t *texHandle_ = nullptr;

  std::vector<System::Mesh2d> meshData_;

  std::function<void(UINT n)> wtCallFunc_;

  // Buf
  std::unique_ptr<System::SpriteMesh> mesh_ = nullptr;

  uint32_t layerNumber_ = 0;
};
} // namespace Sprite2d
} // namespace CLEYERA