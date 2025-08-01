#include "IScene.h"

using namespace CLEYERA;
using namespace CLEYERA::Model3d;

SceneComponent::SceneComponent() {
  gravityManager_ = Manager::GravityManager::GetInstance();
  terrain_ = Manager::Terrain::GetInstance();
  modelManager_ = Manager::ModelManager::GetInstance();
  colliderSystem_ = Manager::ColliderSystem::GetInstance();
  objectManager_ = Manager::ObjectManager::GetInstance();

}

void SceneComponent::ImGuiUpdate() {

  // obj
  ImGui::Begin("ManagerList");
  for (auto m : this->managerComponents_) {
    m.lock()->ImGuiUpdate();
  }
  ImGui::End();

  ImGui::Begin("Sprites");
  for (auto s : spriteComponents_) {

    s.lock()->ImGuiUpdate();
  }

  ImGui::End();
}

void SceneComponent::InitRaytracing() {

  // tlas作成
  tlas_ = std::make_unique<system::Tlas>();
  tlas_->SetCreateObject(objectList_);
  tlas_->Init();

  // 汎用ルートシグネチャ
  // globalにTlas
  // Camera
  globalrootsignature_ = std::make_unique<system::GlobalRootSignature>();
  globalrootsignature_->Init();

  // IB,VB
  // space1
  this->closeHitRootSignature_ =
      std::make_unique<system::CloseHitRootSignature>();
  closeHitRootSignature_->Create();

  // output
  // spcce2
  this->rayGenRootSignature_ = std::make_unique<system::RayGenRootSignature>();
  rayGenRootSignature_->Create();

  // 一旦クローズ
  CLEYERA::Base::DX::DXCommandManager::GetInstace()->CommandClose();

  // パイプライン
  stateObject_ = std::make_unique<system::PiplineStateObject>();
  stateObject_->SetGlobalRootSignature(
      globalrootsignature_->GetRootSignature());
  stateObject_->SetClosetHitRootSignature(
      closeHitRootSignature_->GetRootSignature());
  stateObject_->SetRayGenRootSignature(
      rayGenRootSignature_->GetRootSignature());

  stateObject_->Init();

  // シェーダーテーブル
  shaderTable_ = std::make_unique<ShaderTable>();
  shaderTable_->SetOutPutDescripterHandle(
      uint32_t(raytracingManager_.lock()->Gethandle()));
  shaderTable_->SetStateObj(stateObject_->GetStateObject());
  shaderTable_->Init();
}

void SceneComponent::RaytracigTransfar() {
  // tlas転送
  tlas_->Update(objectList_);
}

void SceneComponent::Render() {

  auto commandManager = Base::DX::DXCommandManager::GetInstace();
  auto list = commandManager->GetCommandList();

  std::vector<ID3D12DescriptorHeap *> descs = {
      CLEYERA::Base::DX::DXDescripterManager::GetInstance()
          ->GetSRV()
          .lock()
          ->GetDescripter()};
  CLEYERA::Base::DX::DXCommandManager::GetInstace()->SetDescripter(descs);

  // outの流れ
  // ソース_UAV_計算_ソース

  // outputRay_->Begin();

  // レイトレーシングを開始.
  // ルートシグネチャセット
  globalrootsignature_->Render();

  list->SetPipelineState1(stateObject_->GetStateObject().Get());

  // tlasのセット
  tlas_->BufferBind();

  // auto desc = Base::DX::DXDescripterManager::GetInstance();

  // auto VbIndex =
  // desc->GetSRVGPUHandle(this->objectList_[0].lock()->GetModel().lock()->GetMeshData()->GetVertexBufIndex());
  // auto IbIndex =
  // desc->GetSRVGPUHandle(this->objectList_[0].lock()->GetModel().lock()->GetMeshData()->GetIndexBufIndex());

  // auto command = Base::DX::DXCommandManager::GetInstace()->GetCommandList();
  // command->SetComputeRootDescriptorTable(2,IbIndex);
  // command->SetComputeRootDescriptorTable(3, VbIndex);
}
