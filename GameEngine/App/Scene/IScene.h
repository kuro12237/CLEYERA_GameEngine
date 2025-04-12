#pragma once
#include "../../CLEYERA/3d/Game3dObject.h"
#include "../../CLEYERA/3d/Line3d/Line3d.h"

#include "../../CLEYERA/3d/GlobalRootSignature/GlobalRootSignature.h"
#include "../../CLEYERA/3d/ShaderTable/ShaderTable.h"
#include "../../CLEYERA/3d/StateObject/StateObject.h"
#include "../../CLEYERA/3d/Tlas/Tlas.h"
#include "../../CLEYERA/pch/Pch.h"

#include "../../CLEYERA/3d/LocalRootSignature/ClosestHitRootSignature.h"
#include "../../CLEYERA/3d/LocalRootSignature/RayGenRootSignature.h"

#include "../../CLEYERA/Graphics/RaytracingManager/RaytracingManager.h"
#include"../../CLEYERA/CLEYERA.h"

/// <summary>
/// Scene抽象クラス
/// </summary>
class SceneCompornent {
 public:
   SceneCompornent();
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

#pragma region Set
   void SetRaytracingManager(std::weak_ptr<CLEYERA::Graphics::RaytracingManager> m) { raytracingManager_ = m; }

#pragma endregion

 protected:
   CLEYERA::Manager::GravityManager *gravityManager_ = nullptr;
   CLEYERA::Manager::Terrain *terrain_ = nullptr;
   CLEYERA::Manager::ModelManager *modelManager_ = nullptr;

   std::vector<std::weak_ptr<CLEYERA::Model3d::Game3dObject>> objectList_;
   std::list<std::shared_ptr<CLEYERA::Component::ManagerCompornent>> managerCompornents_;
 private:
   std::weak_ptr<CLEYERA::Graphics::RaytracingManager> raytracingManager_;

   std::unique_ptr<CLEYERA::Model3d::system::Tlas> tlas_ = nullptr;
   std::unique_ptr<CLEYERA::Model3d::system::GlobalRootSignature> globalrootsignature_ = nullptr;

   std::unique_ptr<CLEYERA::Model3d::system::CloseHitRootSignature> closeHitRootSignature_ = nullptr;
   std::unique_ptr<CLEYERA::Model3d::system::RayGenRootSignature> rayGenRootSignature_ = nullptr;

   std::unique_ptr<CLEYERA::Model3d::system::PiplineStateObject> stateObject_ = nullptr;
   std::unique_ptr<ShaderTable> shaderTable_ = nullptr;
};
