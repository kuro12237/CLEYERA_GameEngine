
#include <Windows.h>

#include "CLEYERA/CLEYERA.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  std::unique_ptr<Engine> engine_ = std::make_unique<Engine>();
  engine_->Init();

  CLEYERA::Utility::ImGuiManager *imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
  CLEYERA::Base::DX::DXCommandManager *commandManager = CLEYERA::Base::DX::DXCommandManager::GetInstace();
  CLEYERA::Base::Win::WinApp *winApp = CLEYERA::Base::Win::WinApp::GetInstance();


  std::unique_ptr<CLEYERA::Model3d::Model> model = std::make_unique<CLEYERA::Model3d::Model>();

  model->Init();

  while (CLEYERA::Base::Win::WinApp::GetInstance()->WinMsg())
  {
    engine_->Begin();

    imGuiManager->Begin();






    commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
    commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

    //imGuiManager->BeginParamsList();

    //imGuiManager->EndParamsList();

    std::vector<ID3D12DescriptorHeap *> desc = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
    commandManager->SetDescripterHeap(desc);

    imGuiManager->Render();

    engine_->End();

  }

  model.reset();


  engine_->Finalize();

  return 0;
}