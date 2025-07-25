#pragma once

#include "3d/Game3dObject.h"
#include "3d/GlobalRootSignature/GlobalRootSignature.h"
#include "3d/Line3d/Line3d.h"
#include "3d/LocalRootSignature/ClosestHitRootSignature.h"
#include "3d/LocalRootSignature/RayGenRootSignature.h"
#include "3d/ShaderTable/ShaderTable.h"
#include "3d/StateObject/StateObject.h"
#include "3d/Tlas/Tlas.h"
#include "CLEYERA.h"
#include "Graphics/RaytracingManager/RaytracingManager.h"
#include "Utility/Json/GlobalVariables.h"
#include "pch/Pch.h"

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
  void
  SetRaytracingManager(std::weak_ptr<CLEYERA::Graphics::RaytracingManager> m) {
    raytracingManager_ = m;
  }

  void SpriteListPush(std::weak_ptr<SpriteComponent> s) {
    spriteComponents_.push_back(s);
  }

#pragma endregion

protected:
  CLEYERA::Manager::GravityManager *gravityManager_ = nullptr;
  CLEYERA::Manager::Terrain *terrain_ = nullptr;
  CLEYERA::Manager::ModelManager *modelManager_ = nullptr;
  CLEYERA::Manager::ColliderSystem *colliderSystem_ = nullptr;
  CLEYERA::Manager::ObjectManager *objectManager_ = nullptr;

  std::vector<std::weak_ptr<CLEYERA::Model3d::Game3dObject>> objectList_;

  std::list<std::weak_ptr<CLEYERA::Component::ManagerComponent>>
      managerComponents_;
  std::list<std::weak_ptr<SpriteComponent>> spriteComponents_;

  std::function<void()> imguiFunc_ = nullptr;

private:
  std::weak_ptr<CLEYERA::Graphics::RaytracingManager> raytracingManager_;

  std::unique_ptr<CLEYERA::Model3d::system::Tlas> tlas_ = nullptr;
  std::unique_ptr<CLEYERA::Model3d::system::GlobalRootSignature>
      globalrootsignature_ = nullptr;

  std::unique_ptr<CLEYERA::Model3d::system::CloseHitRootSignature>
      closeHitRootSignature_ = nullptr;
  std::unique_ptr<CLEYERA::Model3d::system::RayGenRootSignature>
      rayGenRootSignature_ = nullptr;

  std::unique_ptr<CLEYERA::Model3d::system::PiplineStateObject> stateObject_ =
      nullptr;
  std::unique_ptr<ShaderTable> shaderTable_ = nullptr;
};
