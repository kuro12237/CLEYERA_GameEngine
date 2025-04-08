#pragma once
#include "../../3d/Game3dObject.h"
#include "../../3d/ModelManager/ModelManager.h"
#include "../ColliderSystem/OBBCollider.h"
#include "../RenderManager/RenderManager.h"

#include "../ColliderSystem/Collider.h"
#include "../ColliderSystem/ColliderSystem.h"
#include"../Input/InputManager.h"

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

#pragma region Get

   std::weak_ptr<Model3d::Game3dObject> GetGameObject() { return gameObject_; }

#pragma endregion

#pragma region Set

   void SetName(std::string name) { name_ = name; }

#pragma endregion

 private:
   uint32_t modelHandle_ = 0;
   Manager::ModelManager *modelManager_ = nullptr;
   Manager::ObjectManager *objectManager_ = nullptr;
   Manager::RenderManager *renderManager_ = nullptr;
   Manager::ColliderSystem *colliderSystem_ = nullptr;
  
 protected:
   Manager::InputManager *inputManager_ = nullptr;

   using ColliderType = Util::Collider::ColliderType;

   /// <summary>
   /// コライダー作成
   /// </summary>
   /// <param name="type"></param>
   void CreateCollider(ColliderType type);

   std::string name_ = "";

   Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {};

   std::shared_ptr<Util::Collider::OBBCollider> collider_ = nullptr;
   std::shared_ptr<Model3d::Game3dObject> gameObject_ = nullptr;
};
} // namespace Manager
} // namespace CLEYERA