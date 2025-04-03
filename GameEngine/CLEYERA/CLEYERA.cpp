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

   shaderCommon_ = std::make_shared<Shader::system::ShaderCommon>();
   shaderCommon_->Init();
   auto shaderManager = Shader::ShaderManager::GetInstance();
   shaderManager->SetCommon(shaderCommon_);

   rasterPiplineCommon_ = std::make_shared<Raster::system::RasterPiplineCommon>();
   rasterPiplineCommon_->Init();

   rasterPiplineManager_ = Raster::RasterPiplineManager::GetInstance();
   rasterPiplineManager_->SetCommon(rasterPiplineCommon_);
   rasterPiplineManager_->Init();

   modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();


   CLEYERA::Manager::RenderManager::GetInstance()->Init();
   CLEYERA::Manager::CameraManager::GetInstance()->Init();
}

void Engine::Finalize() {

   modelManager_->Finalize();

   shaderCommon_.reset();
   rasterPiplineCommon_.reset();

   raytracingManager_.reset();
   imGuiCommon_.reset();
   dxCommon_->Finalize();
   winApp_->Finalize();
}

void Engine::Begin() { dxCommon_->PreDraw(); }

void Engine::End() { dxCommon_->PostDraw(); }
