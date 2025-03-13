#pragma once
#include "Blas/Blas.h"
#include "GlobalRootSignature/GlobalRootSignature.h"
#include "ShaderTable/ShaderTable.h"
#include "StateObject/StateObject.h"
#include "Tlas/Tlas.h"
#include "Vertex/Vertex.h"

#include "../Graphics/ShaderManager/ShaderManager.h"

#include"Mesh/MeshData.h"

namespace CLEYERA {
namespace Model3d {

class Model {
 public:
   Model() {};
   ~Model() {};

   void Init();

   void Update();

   void Render();

   void ImGuiUpdate();

   void CreateMesh(aiMesh *mesh) {
      mesh_ = std::make_unique<Model3d::MeshData>();
      mesh_->Create(mesh);
   }

#pragma region Get
   ShaderTable *GetShaderTable() { return shaderTable_.get(); }
#pragma endregion

 private:

	 std::unique_ptr<MeshData> mesh_ = nullptr;
	

   std::unique_ptr<system::Tlas> tlas_ = nullptr;

   std::unique_ptr<system::GlobalRootSignature> globalrootsignature_ = nullptr;
   std::unique_ptr<system::PiplineStateObject> stateObject_ = nullptr;
   std::unique_ptr<ShaderTable> shaderTable_ = nullptr;

};

} // namespace Model3d
} // namespace CLEYERA