#pragma once
#include "WIn/WinApp.h"
#include"SystemLogManager/SystemLogManager.h"

class Engine {
public:
  Engine() {};
  ~Engine() {};

  void Init();

  void Finalize();

private:

  std::unique_ptr<CLEYERA::LogManager::SystemLogManager> systemLogManager_ = nullptr;
  CLEYERA::Base::Win::WinApp* winApp_ = nullptr;
};
