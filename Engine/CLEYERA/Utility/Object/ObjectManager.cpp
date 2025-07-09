#include "ObjectManager.h"

using json = nlohmann::json;

void CLEYERA::Manager::ObjectManager::Update() {

  for (auto it = objectList_.begin(); it != objectList_.end();) {

    if (!(*it).expired()) {

      (*it).lock()->Update();
      ++it;
    } else {
      it = objectList_.erase(it);
    }
  }
}

void CLEYERA::Manager::ObjectManager::ImGuiUpdate() {

  for (auto it = objectList_.begin(); it != objectList_.end();) {

    if (!(*it).expired()) {

      (*it).lock()->ImGuiUpdate();
      ++it;
    } else {
      it = objectList_.erase(it);
    }
  }
}

void CLEYERA::Manager::ObjectManager::LoadObjectData(const std::string &file) {
  const std::string filePath = "Resources/Configs/SceneObjectNum/" + file;

  std::ifstream ifs(filePath);
  if (!ifs) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return;
  }

  nlohmann::json jsonRoot;
  ifs >> jsonRoot;

  // グループ名（例: "test"）を指定// ファイル名（例: "test.json"）から拡張子を除去
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
      unUseObjsName_[name][fullName] = fullName;
    }
  }
}
