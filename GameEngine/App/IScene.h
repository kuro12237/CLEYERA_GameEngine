#pragma once
#include "../CLEYERA/3d/Game3dObject.h"
#include "../CLEYERA/3d/GlobalRootSignature/GlobalRootSignature.h"
#include "../CLEYERA/3d/ShaderTable/ShaderTable.h"
#include "../CLEYERA/3d/StateObject/StateObject.h"
#include "../CLEYERA/3d/Tlas/Tlas.h"
#include "../CLEYERA/pch/Pch.h"

#include"../CLEYERA/3d/LocalRootSignature/ClosestHitRootSignature.h"
#include"../CLEYERA/3d/LocalRootSignature/RayGenRootSignature.h"


/// <summary>
/// Scene抽象クラス
/// </summary>
class SceneCompornent {
 public:
   SceneCompornent() {};
   virtual ~SceneCompornent() {};

   virtual void Init() = 0;

   virtual void Update() = 0;

   virtual void ImGuiUpdate() {};

   void InitRaytracing();

   void RaytracigTransfar();

   void Render();

   #pragma region Get

   ShaderTable *GetTable() { return shaderTable_.get(); }

#pragma endregion


 protected:

   std::vector<std::weak_ptr<CLEYERA::Model3d::Game3dObject>> objectList_;

 private:
   std::unique_ptr<CLEYERA::Model3d::system::Tlas> tlas_ = nullptr;
   std::unique_ptr<CLEYERA::Model3d::system::GlobalRootSignature> globalrootsignature_ = nullptr;

   std::unique_ptr<CLEYERA::Model3d::system::CloseHitRootSignature> closeHitRootSignature_ = nullptr;
   std::unique_ptr<CLEYERA::Model3d::system::RayGenRootSignature> rayGenRootSignature_ = nullptr;


   std::unique_ptr<CLEYERA::Model3d::system::PiplineStateObject> stateObject_ = nullptr;
   std::unique_ptr<ShaderTable> shaderTable_ = nullptr;
};
