#include "ManagerCompornent.h"

void CLEYERA::Component::ManagerCompornent::ImGuiUpdate() {

  if (name_ == "") {
    return;
  }

  if (ImGui::TreeNode(name_.c_str())) {

    for (auto obj : objComponents_) {

      obj.lock()->ImGuiUpdate();
    }
    for (auto obj : cameraCompornents_) {
      obj.lock()->ImGuiUpdate();
    }

    ImGui::TreePop();
  }
}

void CLEYERA::Component::ManagerCompornent::CollectAllObjects(
    std::list<std::weak_ptr<Component::ObjectComponent>> &outList) {

  for (auto mgr : childManagerComponents_) {
    auto it = mgr.lock();
    if (!it)
      return;

    it->Update();

    // ObjList から Object を取得して objectComponents に移動
    for (auto &newObj : it->GetObjList()) {
      auto obj = newObj.lock();
      if (obj) {
        outList.push_back(obj);
      }
    }

    // ObjList をクリア（元の manager 側から削除）
    it->GetObjList().clear();

    // 子 Manager に対して再帰的に同じ処理を行う
    for (auto &childMgrWeak : it->GetManagerList()) {
      auto childMgr = childMgrWeak.lock();
      if (childMgr) {
        childMgr->CollectAllObjects(outList);
      }
    }
  }
}

void CLEYERA::Component::ManagerCompornent::ListInit() {

  for (auto obj : objComponents_) {

    obj.lock()->Init();
  }
  for (auto obj : cameraCompornents_) {
    obj.lock()->Init();
  }
}

void CLEYERA::Component::ManagerCompornent::ListUpdate() {

  for (auto obj : objComponents_) {
    obj;
    // obj.lock()->Update();
  }
  for (auto obj : cameraCompornents_) {
    obj.lock()->Update();
  }
}