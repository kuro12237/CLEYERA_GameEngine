
#include <Windows.h>

#include "CLEYERA/CLEYERA.h"

#include"testCamera.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

   std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();
   engine_->Init();

   // CLEYERA::Utility::ImGuiManager *imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
   CLEYERA::Base::DX::DXCommandManager *commandManager = CLEYERA::Base::DX::DXCommandManager::GetInstace();
   CLEYERA::Base::Win::WinApp *winApp = CLEYERA::Base::Win::WinApp::GetInstance();
   auto imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
   auto raytracingManager = engine_->GetRaytracingManager();

   std::weak_ptr<CLEYERA::Model3d::Model> model;

   uint32_t handle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel("Resources/Model/Tower","Tower");
   handle;

   model = CLEYERA::Manager::ModelManager::GetInstance()->GetModel("Resources/Model/Tower/Tower.obj");

   std::unique_ptr<TestCamera> camera = std::make_unique<TestCamera>();
   camera->Create();


   // 一旦クローズ
   CLEYERA::Base::DX::DXCommandManager::GetInstace()->CommandClose();



   raytracingManager.lock()->SetDispathRayDesc(model.lock()->GetShaderTable()->GetDispatchRayDesc());

   while (CLEYERA::Base::Win::WinApp::GetInstance()->WinMsg()) {
      engine_->Begin();
      auto swap = CLEYERA::Base::DX::DXManager::GetInstance()->GetSwapChain();

      imGuiManager->Begin();

#pragma region ImGui

#pragma endregion

#pragma region 更新

      camera->Update();

#pragma endregion

#pragma region レイトレーシング
      UINT backBufferIndex_ = swap.lock()->GetSwapChain()->GetCurrentBackBufferIndex();

      raytracingManager.lock()->SetBarrierRTVResource(swap.lock()->GetSwapChainResource(backBufferIndex_));
      raytracingManager.lock()->PreRaytracing();

      commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
      commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

      model.lock()->Render();
      camera->Call(2);

      raytracingManager.lock()->DispachRay();

      // レイトレのoutput結果をレンダーターゲットにコピー
      swap.lock()->RTVCopyBuf(raytracingManager.lock()->GetOutputResource());
      raytracingManager.lock()->PostRaytracing();

#pragma endregion

      commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
      commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

      std::vector<ID3D12DescriptorHeap *> desc = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
      commandManager->SetDescripterHeap(desc);

      ImGui::ShowDemoWindow();

      imGuiManager->Render();

      engine_->End();
   }

   camera.reset();
   model.reset();

   engine_->Finalize();

   return 0;
}