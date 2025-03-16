#include "CLEYERA.h"

using namespace CLEYERA::Base::Win;
using namespace CLEYERA::Base::DX;
using namespace CLEYERA::LogManager;
using namespace CLEYERA::Utility;
using namespace CLEYERA::Graphics;

void Engine::Init() {

   systemLogManager_ = std::make_shared<SystemLogManager>();

   winApp_ = WinApp::GetInstance();
   winApp_->Create();

   dxCommon_ = std::make_shared<DXCommon>(VAR_NAME(DXCommon));
   dxCommon_->SetLogManager(systemLogManager_);
   dxCommon_->Create();

   imGuiCommon_ = std::make_shared<ImGuiCommon>();
   imGuiCommon_->Init();

   imGuiManager_ = ImGuiManager::GetInstance();
   imGuiManager_->SetImGuiCommon(imGuiCommon_);

   raytracingManager_ = std::make_shared<RaytracingManager>();
   raytracingManager_->Create();

   rasterPiplineCommon_ = std::make_shared<Raster::system::RasterPiplineCommon>();
   rasterPiplineCommon_->Init();

   rasterPiplineManager_ = Raster::RasterPiplineManager::GetInstance();
   rasterPiplineManager_->SetCommon(rasterPiplineCommon_);

   modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
}

void Engine::Finalize() {

   modelManager_->Finalize();

   raytracingManager_.reset();
   imGuiCommon_.reset();
   dxCommon_->Finalize();
   winApp_->Finalize();
}

void Engine::Begin() { dxCommon_->PreDraw(); }

void Engine::End() { dxCommon_->PostDraw(); }
