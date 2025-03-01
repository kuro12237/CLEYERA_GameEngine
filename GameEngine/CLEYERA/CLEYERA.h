#pragma once
#include "WIn/WinApp.h"
#include"DX/DXCommon.h"
#include"SystemLogManager/SystemLogManager.h"

class Engine {
public:
  Engine() {};
  ~Engine() {};

  void Init();

  void Finalize();

private:

  std::shared_ptr<CLEYERA::LogManager::SystemLogManager> systemLogManager_ = nullptr;
  CLEYERA::Base::Win::WinApp* winApp_ = nullptr;
  std::shared_ptr<CLEYERA::Base::DX::DXCommon> dxCommon_ = nullptr;
};
