
#include <Windows.h>

#include "CLEYERA/CLEYERA.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

   std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();
   engine_->Init();

   //CLEYERA::Utility::ImGuiManager *imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
   CLEYERA::Base::DX::DXCommandManager *commandManager = CLEYERA::Base::DX::DXCommandManager::GetInstace();
   CLEYERA::Base::Win::WinApp *winApp = CLEYERA::Base::Win::WinApp::GetInstance();

   std::unique_ptr<CLEYERA::Model3d::Model> model = std::make_unique<CLEYERA::Model3d::Model>();

   model->Init();

   //一旦クローズ
   CLEYERA::Base::DX::DXCommandManager::GetInstace()->CommandClose();

   while (CLEYERA::Base::Win::WinApp::GetInstance()->WinMsg()) {
      engine_->Begin();

      //imGuiManager->Begin();

      commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
      commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

      model->Render();


      //結果をレンダーターゲットにコピー
      auto swap = CLEYERA::Base::DX::DXManager::GetInstance()->GetSwapChain();
      UINT backBufferIndex_ = swap.lock()->GetSwapChain()->GetCurrentBackBufferIndex();

      auto rtv = CLEYERA::Base::DX::DXManager::GetInstance()->GetSwapChain().lock()->GetSwapChainResource(backBufferIndex_);

      auto list = CLEYERA::Base::DX::DXCommandManager::GetInstace()->GetCommandList();
      list->CopyResource(rtv, model->GetOutPut()->GetResource());

      //下ImGui rtvのstateが違うため一旦除外

     /* commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
      commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

      std::vector<ID3D12DescriptorHeap *> desc = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
      commandManager->SetDescripterHeap(desc);

      imGuiManager->Render();*/

      engine_->End();
   }

   model.reset();

   engine_->Finalize();

   return 0;
}