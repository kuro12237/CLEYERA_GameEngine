#pragma once


#include"CLEYERA.h"
#include "3d/Game3dObject.h"
#include "3d/Line3d/Line3d.h"
#include "3d/GlobalRootSignature/GlobalRootSignature.h"
#include "3d/ShaderTable/ShaderTable.h"
#include "3d/StateObject/StateObject.h"
#include "3d/Tlas/Tlas.h"
#include "pch/Pch.h"
#include "3d/LocalRootSignature/ClosestHitRootSignature.h"
#include "3d/LocalRootSignature/RayGenRootSignature.h"
#include "Graphics/RaytracingManager/RaytracingManager.h"
#include "Utility/Json/GlobalVariables.h"

class GameManager;

/// <summary>
/// Scene抽象クラス
/// </summary>
class SceneComponent {
public:
  SceneComponent();
  virtual ~SceneComponent() {};

  virtual void Init() = 0;

  virtual void Update(GameManager *g) = 0;

  virtual void ImGuiUpdate();

  virtual void Draw2d() {};

  void InitRaytracing();

  void RaytracigTransfar();

  void Render();

#pragma region Get

  ShaderTable *GetTable() { return shaderTable_.get(); }

#pragma endregion

#pragma region Set
  void SetRaytracingManager(std::weak_ptr<CLEYERA::Graphics::RaytracingManager> m) {
    raytracingManager_ = m;
  }

#pragma endregion

protected:
  CLEYERA::Manager::GravityManager *gravityManager_ = nullptr;
  CLEYERA::Manager::Terrain *terrain_ = nullptr;
  CLEYERA::Manager::ModelManager *modelManager_ = nullptr;
  CLEYERA::Manager::ColliderSystem *collidersystem_ = nullptr;

  std::vector<std::weak_ptr<CLEYERA::Model3d::Game3dObject>> objectList_;

  std::list<std::weak_ptr<CLEYERA::Component::ObjectComponent>> objectComponents_;
  std::list<std::weak_ptr<CLEYERA::Component::ManagerCompornent>> managerCompornents_;

private:
  std::weak_ptr<CLEYERA::Graphics::RaytracingManager> raytracingManager_;

  std::unique_ptr<CLEYERA::Model3d::system::Tlas> tlas_ = nullptr;
  std::unique_ptr<CLEYERA::Model3d::system::GlobalRootSignature> globalrootsignature_ = nullptr;

  std::unique_ptr<CLEYERA::Model3d::system::CloseHitRootSignature> closeHitRootSignature_ = nullptr;
  std::unique_ptr<CLEYERA::Model3d::system::RayGenRootSignature> rayGenRootSignature_ = nullptr;

  std::unique_ptr<CLEYERA::Model3d::system::PiplineStateObject> stateObject_ = nullptr;
  std::unique_ptr<ShaderTable> shaderTable_ = nullptr;
};
