#pragma once
#include "Blas/Blas.h"

#include "Mesh/MeshData.h"

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
   MeshData *GetMeshData() { return mesh_.get(); }
#pragma endregion

 private:
   std::unique_ptr<MeshData> mesh_ = nullptr;

};

} // namespace Model3d
} // namespace CLEYERA