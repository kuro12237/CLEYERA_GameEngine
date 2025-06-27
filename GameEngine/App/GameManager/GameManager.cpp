#include "GameManager.h"

#include "../Scene/EnemyDebugScene.h"

GameManager::GameManager() {
  engine_ = std::make_unique<Engine>();

  engine_->Init();

  scene_ = std::make_unique<GameScene>();
  auto raytracingManager = engine_->GetRaytracingManager();

  scene_->SetRaytracingManager(raytracingManager);

  scene_->Init();
}

void GameManager::Run() {

  // CLEYERA::Utility::ImGuiManager *imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
  CLEYERA::Base::DX::DXCommandManager *commandManager =
      CLEYERA::Base::DX::DXCommandManager::GetInstace();
  CLEYERA::Base::Win::WinApp *winApp = CLEYERA::Base::Win::WinApp::GetInstance();
  auto imGuiManager = CLEYERA::Utility::ImGuiManager::GetInstance();
  auto raytracingManager = engine_->GetRaytracingManager();

  // 一旦クローズ
  CLEYERA::Base::DX::DXCommandManager::GetInstace()->CommandClose();
  raytracingManager.lock()->SetDispathRayDesc(scene_->GetTable()->GetDispatchRayDesc());

  while (CLEYERA::Base::Win::WinApp::GetInstance()->WinMsg()) {
    engine_->Begin();
    auto swap = CLEYERA::Base::DX::DXManager::GetInstance()->GetSwapChain();

#pragma region ImGui

#pragma endregion

#pragma region 更新

    engine_->PhysiceForcesUpdate();

    scene_->Update(this);

    engine_->PreDraw();

    imGuiManager->Begin();

#ifdef _DEBUG

    scene_->ImGuiUpdate();
    engine_->ImGuiUpdate();

#endif // _DEBUG

    // scene_->RaytracigTransfar();

    CLEYERA::Manager::CameraManager::GetInstance()->Update();
    CLEYERA::Manager::RenderManager::GetInstance()->Update();

    engine_->Update();
#pragma endregion

#pragma region レイトレーシング
    UINT backBufferIndex_ = swap.lock()->GetSwapChain()->GetCurrentBackBufferIndex();

    raytracingManager.lock()->SetBarrierRTVResource(
        swap.lock()->GetSwapChainResource(backBufferIndex_));
    raytracingManager.lock()->PreRaytracing();

    commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
    commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

    // scene_->Render();
    // CLEYERA::Manager::CameraManager::GetInstance()->BindComputeCommand(1);

    // raytracingManager.lock()->DispachRay();

    //// レイトレのoutput結果をレンダーターゲットにコピー
    // swap.lock()->RTVCopyBuf(raytracingManager.lock()->GetOutputResource());

    auto command = CLEYERA::Base::DX::DXCommandManager::GetInstace();
    auto handle =
        CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetRTVCPUHandle(backBufferIndex_);
    auto dsvhandle = CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetDSVCPUHandle(0);

    raytracingManager.lock()->PostRaytracing();

    command->ClearRenderTargetView(handle, {1.0f, 0.0f, 0.0f, 1.0f});
    command->ClearDepthStencilView(dsvhandle, D3D12_CLEAR_FLAG_STENCIL);
#pragma endregion

#pragma region ラスタ描画

#pragma region 背景2d

#pragma endregion

#pragma region 3d

    std::vector<ID3D12DescriptorHeap *> desc = {
        CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
    commandManager->SetDescripterHeap(desc);

    commandManager->SetViewCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());
    commandManager->SetScissorCommand(winApp->GetKWindowWidth(), winApp->GetKWindowHeight());

    CLEYERA::Manager::RenderManager::GetInstance()->Draw3d();

#pragma endregion

#pragma region 前景2d

    scene_->Draw2d();

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region ポストエフェクトの画像処理

#pragma endregion

    commandManager->SetDescripterHeap(desc);

    imGuiManager->Render();

    engine_->End();
  }

  scene_.reset();

  engine_->Finalize();
}

void GameManager::ChangeScene(std::unique_ptr<SceneCompornent> newScene) {

  //CLEYERA::Manager::ColliderSystem::GetInstance()->Clear();
  CLEYERA::Manager::GravityManager::GetInstance()->Clear();
  CLEYERA::Manager::Terrain::GetInstance()->Clear();

  scene_.reset();

  scene_ = std::move(newScene);
  auto raytracingManager = engine_->GetRaytracingManager();

  scene_->SetRaytracingManager(raytracingManager);

  scene_->Init();

  scene_->Update(this);

  // engine_->End();
  CLEYERA::Base::DX::DXCommandManager::GetInstace()->CommandClose();
  this->isChange_ = true;
  return;
}
