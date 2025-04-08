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

   CLEYERA::Manager::TexManager::GetInstance()->Init();
   modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
   modelManager_->Init();

   CLEYERA::Manager::RenderManager::GetInstance()->Init();
   CLEYERA::Manager::CameraManager::GetInstance()->Init();

   debugCamera_ = std::make_shared<CLEYERA::DebugTools::DebugCamera>();
   debugCamera_->Init();

   grid_ = CLEYERA::DebugTools::Grid::GetInstance();
   grid_->Init();

   lightManager_ = CLEYERA::Manager::LightManager::GetInstance();
   lightManager_->Init();

   objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();
   colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();

   terrain_ = CLEYERA::Manager::Terrain::GetInstance();
   terrain_->Init();

   inputManager_ = CLEYERA::Manager::InputManager::GetInstance();
   inputManager_->Init();
}

void Engine::ImGuiUpdate() {

   dxCommon_->ImGuiUpdate();

   lightManager_->ImGuiUpdate();
   debugCamera_->ImGuiUpdate();

   grid_->ImGuiUpdate();
   // objectManager_->ImGuiUpdate();
   colliderSystem_->ImGuiUpdate();
}

void Engine::Update() {
   terrain_->Update();
   objectManager_->Update();
   colliderSystem_->Update();
   lightManager_->Update();
   grid_->Update();
   debugCamera_->Update();
}

void Engine::Finalize() {

   inputManager_->Finalize();
   terrain_->Finalize();
   lightManager_->Finalize();
   grid_->Finalize();

   debugCamera_.reset();

   modelManager_->Finalize();

   CLEYERA::Manager::TexManager::GetInstance()->Finalize();
   shaderCommon_.reset();
   rasterPiplineCommon_.reset();

   raytracingManager_.reset();
   imGuiCommon_.reset();
   dxCommon_->Finalize();
   winApp_->Finalize();
}

void Engine::Begin() {
   dxCommon_->PreDraw();
   inputManager_->Begin();

}

void Engine::End() { dxCommon_->PostDraw(); }

void Engine::Draw() { grid_->DrawRaster3d(); }
