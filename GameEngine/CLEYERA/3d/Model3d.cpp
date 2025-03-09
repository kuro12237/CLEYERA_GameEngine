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

   //
   globalrootsignature_ = std::make_unique<system::GlobalRootSignature>();
   globalrootsignature_->Init();

   //出力
   outputRay_ = std::make_unique<system::OutPutRay>();
   outputRay_->Init();

}

void CLEYERA::Model3d::Model::Update() {}
