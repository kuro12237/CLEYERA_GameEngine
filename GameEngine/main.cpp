
#include <Windows.h>

#include "CLEYERA/CLEYERA.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

   std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();
   engine_->Init();

   // CLEYERA::Utility::ImGuiManager *imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
   CLEYERA::Base::DX::DXCommandManager *commandManager = CLEYERA::Base::DX::DXCommandManager::GetInstace();
   CLEYERA::Base::Win::WinApp *winApp = CLEYERA::Base::Win::WinApp::GetInstance();

   std::unique_ptr<CLEYERA::Model3d::Model> model = std::make_unique<CLEYERA::Model3d::Model>();

   model->Init();

   auto imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();

   // 一旦クローズ
   CLEYERA::Base::DX::DXCommandManager::GetInstace()->CommandClose();

   auto list = CLEYERA::Base::DX::DXCommandManager::GetInstace()->GetCommandList();

   while (CLEYERA::Base::Win::WinApp::GetInstance()->WinMsg()) {
      engine_->Begin();
      auto swap = CLEYERA::Base::DX::DXManager::GetInstance()->GetSwapChain();

      imGuiManager->Begin();


      model->Update();

#pragma region レイトレーシング
      UINT backBufferIndex_ = swap.lock()->GetSwapChain()->GetCurrentBackBufferIndex();

      D3D12_RESOURCE_BARRIER barrier{};
      barrier.Transition.pResource = swap.lock()->GetSwapChainResource(backBufferIndex_);

      barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
      barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
      barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
      barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

      list->ResourceBarrier(1, &barrier);

      commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
      commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

      model->Render();

      // レイトレのoutput結果をレンダーターゲットにコピー
      swap.lock()->RTVCopyBuf(model->GetOutPut()->GetResource());


      barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
      barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
      barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
      list->ResourceBarrier(1, &barrier);

#pragma endregion

      commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
      commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

      std::vector<ID3D12DescriptorHeap *> desc = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
      commandManager->SetDescripterHeap(desc);

      model->ImGuiUpdate();

      ImGui::ShowDemoWindow();

      imGuiManager->Render();

      engine_->End();
   }

   model.reset();

   engine_->Finalize();

   return 0;
}