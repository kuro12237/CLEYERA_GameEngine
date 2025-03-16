#pragma once
#include "DX/DXCommon.h"
#include "SystemLogManager/SystemLogManager.h"
#include "WIn/WinApp.h"

#include "Utility/ImGui/ImGuiManager.h"

#include "3d/Model3d.h"

#include "Graphics/RaytracingManager/RaytracingManager.h"
#include"3d/ModelManager/ModelManager.h"

#include"Graphics/RasterPipline/RasterPiplineManager.h"

class Engine {
 public:
   Engine() {};
   ~Engine() {};

   void Init();

   void Finalize();

   void Begin();

   void End();

#pragma region Get

   std::weak_ptr<CLEYERA::Graphics::RaytracingManager> GetRaytracingManager() { return raytracingManager_; }
#pragma endregion

 private:
   CLEYERA::Base::Win::WinApp *winApp_ = nullptr;
   CLEYERA::Utility::ImGuiManager *imGuiManager_ = nullptr;
   CLEYERA::Manager::ModelManager *modelManager_ = nullptr;
   CLEYERA::Graphics::Raster::RasterPiplineManager *rasterPiplineManager_ = nullptr;

   std::shared_ptr<CLEYERA::Graphics::RaytracingManager> raytracingManager_ = nullptr;

   std::shared_ptr<CLEYERA::LogManager::SystemLogManager> systemLogManager_ = nullptr;

   std::shared_ptr<CLEYERA::Graphics::Raster::system::RasterPiplineCommon> rasterPiplineCommon_ = nullptr;

   std::shared_ptr<CLEYERA::Base::DX::DXCommon> dxCommon_ = nullptr;
   std::shared_ptr<CLEYERA::Utility::ImGuiCommon> imGuiCommon_ = nullptr;
};
