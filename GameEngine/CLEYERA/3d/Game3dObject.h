#pragma once
#include "../Utility/TransformBase/TransformBase.h"
#include "../Utility/World/WorldTransform.h"
#include "ModelManager/ModelManager.h"
#include"../Graphics/RasterPipline/RasterEnum.h"

namespace CLEYERA {

namespace Model3d {

/// <summary>
/// ゲームオブジェクト
/// </summary>
class Game3dObject : public CLEYERA::Util::WorldTransform {
 public:
   Game3dObject() {};
   ~Game3dObject() {};

   void Create(uint32_t handle);

   void Update();

   void DrawRaster3d();

#pragma region Get
   std::weak_ptr<Model> GetModel() { return model_; }
   const Graphics::RasterPipline_Mode &GetRasterMode() const { return rasterMode_; }
#pragma endregion

 private:
   Graphics::RasterPipline_Mode rasterMode_ = Graphics::RasterPipline_Mode::DF_MODEL3d;

   Manager::CameraManager *cameraManager_ = nullptr;
   Manager::ModelManager *modelManager_ = nullptr;

   Base::DX::DXCommandManager *commandManager_ = nullptr;

   std::shared_ptr<Model> model_ = nullptr;
   uint32_t modelHandle_ = 0;

   uint32_t ins_ = 1;
};

} // namespace Model3d

} // namespace CLEYERA