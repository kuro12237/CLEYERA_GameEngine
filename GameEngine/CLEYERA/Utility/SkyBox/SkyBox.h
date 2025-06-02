#pragma once
#include "../ColliderSystem/ColliderSystem.h"

#include "../../3d/ModelManager/ModelManager.h"
#include "../Object/ObjectManager.h"

namespace CLEYERA {
namespace Manager {

/// <summary>
/// 地形
/// </summary>
class SkyBox : public CLEYERA::Util::WorldTransform {
public:
  static SkyBox *GetInstance() {
    static SkyBox instance;
    return &instance;
  }

  void Init();

  void Update();

  void Finalize();

  void CheckObjct();

  void PushData(std::weak_ptr<Component::ObjectComponent> obj) { objList_.push_back(obj); };

  void ChengeData(uint32_t modelHandle);

private:
  std::list<std::weak_ptr<Component::ObjectComponent>> objList_;

  Manager::ModelManager *modelManager_ = nullptr;
  Manager::RenderManager *renderManager_ = nullptr;
  Manager::ColliderSystem *colliderSystem_ = nullptr;
  Manager::ObjectManager *objectManager_ = nullptr;

  std::string dfFilePath_ = "Resources/Model/system/SkyBox";
  std::string objName_ = "SkyBox";

  uint32_t modelHandle_ = 0;

  std::shared_ptr<Model3d::Game3dObject> gameObj_;

  Math::Vector::Vec3 scaleTerrain_ = {1.0f, 1.0f, 1.0f};
  Math::Vector::Vec3 rotateTerrain_ = {};
  Math::Vector::Vec3 translateTerrain_ = {};

  std::vector<Util::Collider::system::Triangle> triCollider_;

  std::shared_ptr<CLEYERA::Model3d::Line3d> line_ = nullptr;
  std::vector<Math::Vector::Vec3> positions_ = {};

  std::vector<Math::Vector::Vec4> colors_ = {};

  Math::Matrix::Mat4x4 mat_;

#pragma region Singleton
  SkyBox() = default;
  ~SkyBox() = default;
  SkyBox(const SkyBox &) = delete;
  SkyBox &operator=(const SkyBox &) = delete;
#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA