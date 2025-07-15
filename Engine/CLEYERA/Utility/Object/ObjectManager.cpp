#include "ObjectManager.h"

using json = nlohmann::json;

void CLEYERA::Manager::ObjectManager::Update() {

  for (const auto &m : this->objects_) {
    for (auto &[name, obj] : m.second) {
      if (!obj)
        continue;

      switch (obj->GetMode()) {
      case Component::ObjectComponent::OBJ_MODE::SPAWN: {
        obj->Init();
        obj->SetMode(Component::ObjectComponent::OBJ_MODE::ACTIVE);
        obj->Update();
        obj->GameObjectUpdate();

        Manager::GravityManager::GetInstance()->PushData(obj);
        CLEYERA::Manager::Terrain::GetInstance()->PushData(obj);

        break;
      }

      case Component::ObjectComponent::OBJ_MODE::REMOVE: {
        obj->Finalize();
        // 削除対象
        DeleteObject(obj);
        break;
      }

      case Component::ObjectComponent::OBJ_MODE::PAUSE: {
        // 一時停止中なので何もしない（Update済み）
        break;
      }

      case Component::ObjectComponent::OBJ_MODE::INACTIVE: {
        // 完全に非アクティブなのでスキップ
        // 必要なら Update() 呼ばない方が良い
        break;
      }

      case Component::ObjectComponent::OBJ_MODE::ACTIVE: {
        obj->Update();
        obj->GameObjectUpdate();
        break;
      }
      }
    }
  }
}

void CLEYERA::Manager::ObjectManager::ImGuiUpdate() {

  ImGui::Begin("ObjManager");

  for (const auto &m : objects_) {

    if (ImGui::TreeNode(m.first.c_str())) {

      for (const auto &obj : m.second) {

        if (!obj.second) {
          continue;
        }
        obj.second->ImGuiUpdate();
      }
      ImGui::TreePop();
    }
  }

  ImGui::End();
}

void CLEYERA::Manager::ObjectManager::LoadObjectData(const std::string &file) {
  const std::string filePath = "Resources/Configs/SceneObjectNum/" + file;

  CLEYERA::Manager::RenderManager::GetInstance()->Clear();
  Clear();

  std::ifstream ifs(filePath);
  if (!ifs) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return;
  }

  nlohmann::json jsonRoot;
  ifs >> jsonRoot;

  // グループ名（例: "test"）を指定// ファイル名（例:
  // "test.json"）から拡張子を除去
  std::string groupName = file;
  size_t dotPos = groupName.rfind('.');
  if (dotPos != std::string::npos) {
    groupName = groupName.substr(0, dotPos);
  }

  // JSON内でグループ名を検索
  auto itGroup = jsonRoot.find(groupName);
  if (itGroup == jsonRoot.end() || !itGroup->is_object()) {
    std::cerr << "Group not found or invalid format: " << file << std::endl;
    return;
  }

  for (auto &[name, value] : itGroup->items()) {
    // ["Enemy", 3] の形式チェック
    if (!value.is_array() || value.size() != 2 || !value[0].is_string() ||
        !value[1].is_number_unsigned()) {
      std::cerr << "Invalid object format for key: " << name << std::endl;
      continue;
    }

    ObjectNumData data;
    data.key = value[0].get<std::string>();
    data.objNum = value[1].get<uint32_t>();

    for (uint32_t i = 0; i < data.objNum; ++i) {
      std::string fullName = data.key;
      if (i > 0) {
        std::ostringstream oss;
        oss << "." << std::setfill('0') << std::setw(3) << i;
        fullName += oss.str();
      }

      // 登録
      objects_[name][fullName] = nullptr;
      unUseObjsName_[name].push_back(fullName);
    }
  }
}

void CLEYERA::Manager::ObjectManager::CreateObject(
    const std::string &category,
    std::shared_ptr<Component::ObjectComponent> obj) {

  // カテゴリが存在しない場合、自動で128個作成
  auto itCategory = unUseObjsName_.find(category);
  if (itCategory == unUseObjsName_.end()) {
    for (uint32_t i = 0; i < 128; ++i) {
      std::string fullName = category;
      if (i > 0) {
        std::ostringstream oss;
        oss << "." << std::setfill('0') << std::setw(3) << i;
        fullName += oss.str();
      }

      // 登録
      objects_[category][fullName] = nullptr;
      unUseObjsName_[category].push_back(fullName);
    }
  }

  // 使用可能名がないならエラー
  if (unUseObjsName_[category].empty()) {
    std::cerr << "No available object names for category: " << category
              << std::endl;
    return;
  }

  itCategory = unUseObjsName_.find(category);
  std::string name = itCategory->second.front();
  itCategory->second.erase(itCategory->second.begin());
  // 登録
  objects_[category][name] = obj;
  RenderManager::GetInstance()->PushObj(obj->GetGameObject());

  // 名前とカテゴリを設定
  obj->SetName(name);
  obj->SetCategory(category);
}

void CLEYERA::Manager::ObjectManager::DeleteObject(
    std::weak_ptr<Component::ObjectComponent> obj) {
  if (!obj.lock())
    return;

  const std::string &name = obj.lock()->GetName();
  const std::string &category = obj.lock()->GetCategory();

  auto itCat = objects_.find(category);
  if (itCat != objects_.end()) {
    auto &nameMap = itCat->second;
    auto itName = nameMap.find(name);
    if (itName != nameMap.end()) {
      itName->second = nullptr;
    }
  }

  // 名前を unUse に戻す
  unUseObjsName_[category].push_back(name);
}