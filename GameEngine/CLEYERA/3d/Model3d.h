#pragma once
#include "Blas/Blas.h"
#include "GlobalRootSignature/GlobalRootSignature.h"
#include "OutPutRay/OutPutRay.h"
#include "ShaderTable/ShaderTable.h"
#include "StateObject/StateObject.h"
#include "Tlas/Tlas.h"
#include "Vertex/Vertex.h"

#include "../Graphics/ShaderManager/ShaderManager.h"

namespace CLEYERA {
namespace Model3d {

class Model {
 public:
   Model() {};
   ~Model() {};

   void Init();

   void Update();

   void Render();

#pragma region Get

   system::OutPutRay *GetOutPut() { return outputRay_.get(); }

#pragma endregion

 private:
   std::unique_ptr<system::Vertex> vertex_ = nullptr;

   std::unique_ptr<system::Blas> blas_ = nullptr;
   std::unique_ptr<system::Tlas> tlas_ = nullptr;

   std::unique_ptr<system::GlobalRootSignature> globalrootsignature_ = nullptr;
   std::unique_ptr<system::PiplineStateObject> stateObject_ = nullptr;
   std::unique_ptr<ShaderTable> shaderTable_ = nullptr;

   std::unique_ptr<system::OutPutRay> outputRay_ = nullptr;
};

} // namespace Model3d
} // namespace CLEYERA