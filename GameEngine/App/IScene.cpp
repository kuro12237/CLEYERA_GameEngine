#include "IScene.h"

using namespace CLEYERA;
using namespace CLEYERA::Model3d;

void SceneCompornent::InitRaytracing() {

   // tlas作成
   tlas_ = std::make_unique<system::Tlas>();
   tlas_->SetCreateObject(objectList_);
   tlas_->Init();

   // 汎用ルートシグネチャ
   globalrootsignature_ = std::make_unique<system::GlobalRootSignature>();
   globalrootsignature_->Init();

   this->closeHitRootSignature_ = std::make_unique<system::CloseHitRootSignature>();
   closeHitRootSignature_->Create();
   this->rayGenRootSignature_ = std::make_unique<system::RayGenRootSignature>();
   rayGenRootSignature_->Create();

   // パイプライン
   stateObject_ = std::make_unique<system::PiplineStateObject>();
   stateObject_->SetGlobalRootSignature(globalrootsignature_->GetRootSignature());
   stateObject_->Init();

   // シェーダーテーブル
   shaderTable_ = std::make_unique<ShaderTable>();
   shaderTable_->SetStateObj(stateObject_->GetStateObject());
   shaderTable_->Init();
}

void SceneCompornent::RaytracigTransfar() {
   // tlas転送
   tlas_->Update(objectList_);
}

void SceneCompornent::Render() {

   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   auto list = commandManager->GetCommandList();

   std::vector<ID3D12DescriptorHeap *> descs = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
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
}
