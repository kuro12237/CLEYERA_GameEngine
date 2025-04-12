#pragma once
#include "../../3d/Game3dObject.h"
#include "../../3d/ModelManager/ModelManager.h"
#include "../ColliderSystem/OBBCollider.h"
#include "../RenderManager/RenderManager.h"

#include "../ColliderSystem/Collider.h"
#include "../ColliderSystem/ColliderSystem.h"
#include"../Input/InputManager.h"
#include"../Flame/Flame.h"

namespace CLEYERA {
namespace Manager {

class ObjectManager;

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

   void GravityForceReset() { gravityforce_ = {}; }

   void TerrainHit(const Math::Vector::Vec3 &pos);
   void SetTerrainHitFlag(bool f) { isTerrainHit_ = f; }
   void SetPrevTerrainHitFlag(bool f) { isPrevTerrainHit_ = f; }
#pragma region Get
   std::weak_ptr<Model3d::Game3dObject> GetGameObject() { return gameObject_; }
   std::weak_ptr<Util::Collider::Collider> GetCollder() { return collider_; }
   Math::Vector::Vec3 &GetTranslate() { return translate_; }
   bool GetTerrainHitFlag() { return isTerrainHit_; }
   bool GetPrevTerrainHitFlag() { return isPrevTerrainHit_; }
#pragma endregion

#pragma region Set
   void SetName(std::string name) { name_ = name; }
   
#pragma endregion

 private:
   uint32_t modelHandle_ = 0;

   Math::Vector::Vec3 gravityforce_ = {};
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

   std::string name_ = "";
   float flame_ = 1.0f / 60.0f;

   
   
   bool isTerrainHit_ = false;
   bool isPrevTerrainHit_ = false;
   Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {};

   Math::Vector::Vec3 velocity_ = {};
   Math::Vector::Vec3 angleVelocity_{};
   Math::Vector::Vec3 force_ = {};
   float friction_ = 0.5f;
   float mass_ = 1.0f;
   float bounceFactor_ = 0.5f;

   std::shared_ptr<Util::Collider::OBBCollider> collider_ = nullptr;
   std::shared_ptr<Model3d::Game3dObject> gameObject_ = nullptr;
};
} // namespace Manager
} // namespace CLEYERA