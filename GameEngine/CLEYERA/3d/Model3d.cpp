#include "Model3d.h"

void CLEYERA::Model3d::Model::Init() {

   // 頂点作成
   vertex_ = std::make_unique<system::Vertex>();
   vertex_->Init();

   // blas作成
   blas_ = std::make_unique<system::Blas>();
   blas_->SetSize(sizeof(CLEYERA::Model3d::system::SVertex));
   blas_->SetParamCount(vertex_->GetVertexdata().size());
   blas_->SetVertexBuf(vertex_->GetResource()->GetResource());

   blas_->Init();

   // tlas作成
   tlas_ = std::make_unique<system::Tlas>();
   tlas_->SetBlas(blas_->GetResource());
   tlas_->Init();

   // 汎用ルートシグネチャ
   globalrootsignature_ = std::make_unique<system::GlobalRootSignature>();
   globalrootsignature_->Init();

   // パイプライン
   stateObject_ = std::make_unique<system::PiplineStateObject>();
   stateObject_->SetGlobalRootSignature(globalrootsignature_->GetRootSignature());
   stateObject_->Init();

   // シェーダーテーブル
   shaderTable_ = std::make_unique<ShaderTable>();
   shaderTable_->SetStateObj(stateObject_->GetStateObject());
   shaderTable_->Init();


   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   commandManager->CommandClose();
}

void CLEYERA::Model3d::Model::Update() { vertex_->Update();

blas_->Update();
}

void CLEYERA::Model3d::Model::Render() {


   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   auto list = commandManager->GetCommandList();

   std::vector<ID3D12DescriptorHeap *> descs = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
   CLEYERA::Base::DX::DXCommandManager::GetInstace()->SetDescripter(descs);


   //outの流れ
   //ソース_UAV_計算_ソース

   //outputRay_->Begin();

   // レイトレーシングを開始.
   //ルートシグネチャセット
   globalrootsignature_->Render();

   list->SetPipelineState1(stateObject_->GetStateObject().Get());

   //tlasのセット
   tlas_->BufferBind();

}

void CLEYERA::Model3d::Model::ImGuiUpdate() {

ImGui::Begin("Vertex_Test");

ImGui::DragFloat3("left", &vertex_->GetVertexdata()[0].pos.x);
ImGui::DragFloat3("top", &vertex_->GetVertexdata()[1].pos.x);
ImGui::DragFloat3("right", &vertex_->GetVertexdata()[2].pos.x);


ImGui::End();
}
