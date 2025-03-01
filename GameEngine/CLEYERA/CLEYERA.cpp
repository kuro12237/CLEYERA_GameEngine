#include "CLEYERA.h"

using namespace CLEYERA::Base::Win;
using namespace CLEYERA::LogManager;

void Engine::Init() {

  systemLogManager_ = std::unique_ptr<SystemLogManager>();

  winApp_ = WinApp::GetInstance();
  winApp_->Create();
}

void Engine::Finalize() { winApp_->Finalize(); }
