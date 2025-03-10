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

   // 出力用バッファ
   outputRay_ = std::make_unique<system::OutPutRay>();
   outputRay_->Init();

   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   commandManager->CommandClose();
}

void CLEYERA::Model3d::Model::Update() {}

void CLEYERA::Model3d::Model::Render() {

   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   auto list = commandManager->GetCommandList();

   std::vector<ID3D12DescriptorHeap *> descs = {CLEYERA::Base::DX::DXDescripterManager::GetInstance()->GetSRV().lock()->GetDescripter()};
   CLEYERA::Base::DX::DXCommandManager::GetInstace()->SetDescripter(descs);


   //outの流れ
   //ソース_UAV_計算_ソース

   //outputRay_->Begin();

   //ルートシグネチャセット
   globalrootsignature_->Render();

   //tlasのセット
   tlas_->BufferBind();

   //outputのセット
   outputRay_->BufferBind();

   // レイトレーシングを開始.
   list->SetPipelineState1(stateObject_->GetStateObject().Get());
   D3D12_DISPATCH_RAYS_DESC desc = shaderTable_->GetDispatchRayDesc();

   //計算
   list->DispatchRays(&desc);

   //stateの変更
   //outputRay_->End();

}
