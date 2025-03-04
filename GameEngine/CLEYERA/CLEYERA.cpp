#include "CLEYERA.h"

using namespace CLEYERA::Base::Win;
using namespace CLEYERA::Base::DX;
using namespace CLEYERA::LogManager;

void Engine::Init() {

  systemLogManager_ = std::make_shared<SystemLogManager>();

  winApp_ = WinApp::GetInstance();
  winApp_->Create();

  dxCommon_ = std::make_shared<DXCommon>(VAR_NAME(DXCommon));
  dxCommon_->SetLogManager(systemLogManager_);
  dxCommon_->Create();
}

void Engine::Finalize() {
  dxCommon_->Finalize();
  winApp_->Finalize();
}

void Engine::Begin() { dxCommon_->Begin(); }

void Engine::End() { dxCommon_->End(); }
