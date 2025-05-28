#pragma once
#include "../3d/Game3dObject.h"
#include "../3d/ModelManager/ModelManager.h"
#include "../Utility/RenderManager/RenderManager.h"

#include "../Utility/Input/InputManager.h"
#include "Utility/Flame/Flame.h"

#include "JsonCompornent.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

enum class ColliderType;
class Collider;
class OBBCollider;
class AABBCollider;

} // namespace Collider
} // namespace Util

namespace Manager {
class ObjectManager;
class ColliderSystem;
} // namespace Manager

namespace Component {

/// <summary>
/// objectのコンポーネント基本継承
/// </summary>
class ObjectComponent {
public:
  ObjectComponent();
  virtual ~ObjectComponent() {};

  virtual void Init() = 0;

  virtual void ImGuiUpdate();

  virtual void Update() = 0;

  /// <summary>
  /// 加速度,veloの更新
  /// </summary>
  void TransformUpdate();

  /// <summary>
  /// 重力更新
  /// </summary>
  /// <param name="g"></param>
  void GravityUpdate(const float &g);

  /// <summary>
  /// 地形の当たり判定呼び出し
  /// </summary>
  /// <param name="pos"></param>
  void TerrainHit(const Math::Vector::Vec3 &pos);

#pragma region Get
  const std::string &GetName() { return name_; }
  std::weak_ptr<Model3d::Game3dObject> GetGameObject() { return gameObject_; }
  std::weak_ptr<Util::Collider::Collider> GetCollder() { return collider_; }
  Math::Vector::Vec3 &GetTranslate() { return translate_; }

  /// <summary>
  /// jsonパラメータのGet
  /// </summary>
  template <typename T> T GetValue(const std::string &name) {
    return jsonSystem_->GetValue<T>(name);
  }
#pragma endregion

#pragma region Set

  void SetName(std::string name) { name_ = name; }

   void SetScale(const Math::Vector::Vec3 &v) { scale_ = v; }
   void SetRotate(const Math::Vector::Vec3 &v) { rotate_ = v; }
   void SetTranslate(const Math::Vector::Vec3 & v) { translate_ = v; }
   void SetForce(const Math::Vector::Vec3 &v) { force_ = v; }

  void SetModelHandle(uint32_t handle) {
    modelHandle_ = handle;
    gameObject_->ChangeModel(handle);
  }

  /// <summary>
  /// jsonパラメータSet
  /// </summary>
  template <typename T> void SetValue(const std::string &name, T t) {
    jsonSystem_->SetValue<T>(name, t);
  }
#pragma endregion

private:
  uint32_t modelHandle_ = 0;

protected:
  Manager::ModelManager *modelManager_ = nullptr;
  Manager::ObjectManager *objectManager_ = nullptr;
  Manager::RenderManager *renderManager_ = nullptr;
  Manager::ColliderSystem *colliderSystem_ = nullptr;
  Manager::InputManager *inputManager_ = nullptr;

  using ColliderType = Util::Collider::ColliderType;

  /// <summary>
  /// コライダー作成
  /// </summary>
  /// <param name="type"></param>
  void CreateCollider(ColliderType type);

  /// <summary>
  /// jsonの作成
  /// </summary>
  void CreateJsonSystem(const std::string &fileGroupName);

  std::string name_ = "";

  Math::Vector::Vec3 scale_ = {2.0f, 2.0f, 2.0f};
  Math::Vector::Vec3 rotate_ = {};
  Math::Vector::Vec3 translate_ = {};

  Math::Vector::Vec3 velocity_ = {};
  Math::Vector::Vec3 force_ = {};
  float friction_ = 0.5f;
  float mass_ = 1.0f;
  float bounceFactor_ = 0.5f;

  // 当たり判定
  std::shared_ptr<Util::Collider::Collider> collider_ = nullptr;
  // jsonのシステム
  std::shared_ptr<Component::JsonCompornent> jsonSystem_ = nullptr;
  // WorldTransform,GameObject等のクラス
  std::shared_ptr<Model3d::Game3dObject> gameObject_ = nullptr;
};
} // namespace Component
} // namespace CLEYERA