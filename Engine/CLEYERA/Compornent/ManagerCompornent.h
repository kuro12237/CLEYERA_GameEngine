#pragma once

#include "pch/Pch.h"

#include "../Compornent/CameraCompornent.h"
#include "ObjectCompornent.h"

namespace CLEYERA {

namespace Component {

class ManagerCompornent {
public:
  ManagerCompornent() {
    colliderSystem_ = Manager::ColliderSystem::GetInstance();
  };
  virtual ~ManagerCompornent() {};

  virtual void Init() = 0;

  virtual void Update() = 0;

  virtual void ImGuiUpdate();

  void CollectAllObjects(
                         std::list<std::weak_ptr<Component::ObjectComponent>> &outList);

#pragma region Get

  std::list<std::weak_ptr<Component::ManagerCompornent>> &GetManagerList() { return childManagerComponents_; }

  std::list<std::weak_ptr<Component::ObjectComponent>> &GetObjList() {
    return objComponents_;
  }
#pragma endregion

private:
protected:
  Manager::ColliderSystem *colliderSystem_ = nullptr;

  void ListInit();
  void ListUpdate();

  std::string name_ = "";

  std::list<std::weak_ptr<Component::ObjectComponent>> objComponents_;
  std::list<std::weak_ptr<Component::CameraCompornent>> cameraCompornents_;

  std::list<std::weak_ptr<Component::ManagerCompornent>> childManagerComponents_;
};

} // namespace Component

} // namespace CLEYERA
