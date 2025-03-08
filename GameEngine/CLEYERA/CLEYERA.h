#pragma once
#include "DX/DXCommon.h"
#include "SystemLogManager/SystemLogManager.h"
#include "WIn/WinApp.h"

#include "Utility/ImGui/ImGuiManager.h"

#include"3d/Model3d.h"

class Engine {
 public:
   Engine() {};
   ~Engine() {};

   void Init();

   void Finalize();

   void Begin();

   void End();

 private:
   CLEYERA::Base::Win::WinApp *winApp_ = nullptr;
   CLEYERA::Utility::ImGuiManager *imGuiManager_ = nullptr;

   std::shared_ptr<CLEYERA::LogManager::SystemLogManager> systemLogManager_ = nullptr;

   std::shared_ptr<CLEYERA::Base::DX::DXCommon> dxCommon_ = nullptr;
   std::shared_ptr<CLEYERA::Utility::ImGuiCommon> imGuiCommon_ = nullptr;
};
