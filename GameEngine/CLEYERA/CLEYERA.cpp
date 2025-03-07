#include "CLEYERA.h"

using namespace CLEYERA::Base::Win;
using namespace CLEYERA::Base::DX;
using namespace CLEYERA::LogManager;
using namespace CLEYERA::Utility;

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
}

void Engine::Finalize() {

   imGuiCommon_.reset();
   dxCommon_->Finalize();
   winApp_->Finalize();
}

void Engine::Begin() { dxCommon_->PreDraw(); }

void Engine::End() { dxCommon_->PostDraw(); }
