#pragma once
#include "Blas/Blas.h"
#include "Tlas/Tlas.h"
#include "Vertex/Vertex.h"
#include"GlobalRootSignature/GlobalRootSignature.h"
#include"OutPutRay/OutPutRay.h"

namespace CLEYERA {
namespace Model3d {

class Model {
 public:
   Model() {};
   ~Model() {};

   void Init();

   void Update();

 private:
   std::unique_ptr<system::Vertex> vertex_ = nullptr;

   std::unique_ptr<system::Blas> blas_ = nullptr;
   std::unique_ptr<system::Tlas> tlas_ = nullptr;

   std::unique_ptr<system::GlobalRootSignature> globalrootsignature_ = nullptr;
   std::unique_ptr<system::OutPutRay> outputRay_ = nullptr;

};

} // namespace Model3d
} // namespace CLEYERA