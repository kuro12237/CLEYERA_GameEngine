#include "ManagerCompornent.h"

void CLEYERA::Component::ManagerComponent::ImGuiUpdate() {

  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

  
    for (auto obj : cameraComponents_) {
      obj.lock()->ImGuiUpdate();
    }

    ImGui::TreePop();
  }
}

void CLEYERA::Component::ManagerComponent::CollectAllObjects(
    std::list<std::weak_ptr<Component::ObjectComponent>> &outList) {

  for (auto mgr : childManagerComponents_) {
    auto it = mgr.lock();
    if (!it)
      return;

    it->Update();

    // 子 Manager に対して再帰的に同じ処理を行う
    for (auto &childMgrWeak : it->GetManagerList()) {
      auto childMgr = childMgrWeak.lock();
      if (childMgr) {
        childMgr->CollectAllObjects(outList);
      }
    }
  }
}

void CLEYERA::Component::ManagerComponent::ListInit() {

  for (auto obj : cameraComponents_) {
    obj.lock()->Init();
  }

  for (auto mgr : childManagerComponents_) {
    {
      mgr.lock()->Init();
    }
  }
}

void CLEYERA::Component::ManagerComponent::ListUpdate() {

  for (auto obj : cameraComponents_) {
    obj.lock()->Update();
  }
}