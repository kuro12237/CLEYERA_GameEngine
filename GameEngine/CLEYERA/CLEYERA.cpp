#include "CLEYERA.h"

using namespace CLEYERA::Base::Win;
using namespace CLEYERA::Base::DX;
using namespace CLEYERA::LogManager;

void Engine::Init() {

  systemLogManager_ = std::shared_ptr<SystemLogManager>();

  winApp_ = WinApp::GetInstance();
  winApp_->Create();

  dxCommon_ = std::make_shared<DXCommon>("DX");
  dxCommon_->SetLogManager(systemLogManager_);
  dxCommon_->Create();




}

void Engine::Finalize() { winApp_->Finalize(); }
