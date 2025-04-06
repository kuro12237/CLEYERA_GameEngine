#pragma once
#include "../../3d/Game3dObject.h"
#include "../../3d/ModelManager/ModelManager.h"
#include "../ColliderSystem/OBBCollider.h"
#include"../RenderManager/RenderManager.h"

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


 private:
   std::string name_ = "obj";

   uint32_t modelHandle_ = 0;
   Manager::ModelManager *modelManager_ = nullptr;
   Manager::ObjectManager *objectManager_ = nullptr;
   Manager::RenderManager *renderManager_ = nullptr;

 protected:
   Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {};

   std::shared_ptr<Util::Collider::Collider> collider_ = nullptr;
   std::shared_ptr<Model3d::Game3dObject> gameObject_ = nullptr;
};
} // namespace Manager
} // namespace CLEYERA