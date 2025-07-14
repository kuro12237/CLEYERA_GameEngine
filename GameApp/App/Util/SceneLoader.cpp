#include "SceneLoader.h"
#include "pch/Pch.h"

void SceneLoader::LoadSceneData(std::string path) {

  std::string filePath = directoryPath_ + path + ".json";

  std::ifstream file = CLEYERA::FileLoader::JsonLoadFile(filePath);
  file >> deserialized;
  assert(deserialized.is_object());
  assert(deserialized.contains("name"));
  assert(deserialized["name"].is_string());

  // sceneじゃなかった時エラーを吐く
  std::string name = deserialized["name"].get<std::string>();
  assert(name.compare("scene") == 0);

  // 読み込み開始
  for (nlohmann::json &object : deserialized["objects"]) {
    assert(object.contains("type"));

    std::string type = object["type"].get<std::string>();

    if (type.compare("MESH") == 0) {
      LoadobjData(object);
    }
  }
}
std::vector<std::shared_ptr<EnvironmentObject>> SceneLoader::SettingData(
    std::list<std::weak_ptr<CLEYERA::Component::ObjectComponent>> /*unused*/) {

  const auto &objsMap =
      CLEYERA::Manager::ObjectManager::GetInstance()->GetObjects();

  std::vector<std::shared_ptr<EnvironmentObject>> enviObjs;

  for (const auto &[category, nameMap] : objsMap) {
    for (const auto &[name, obj] : nameMap) {
      if (!obj)
        continue;

      // データがあれば反映
      auto itData = objDatas_.find(name);
      if (itData != objDatas_.end()) {
        const auto &data = itData->second;

        // 変換データを適用
        obj->SetScale(data.scale);
        obj->SetRotate(data.rotate);
        obj->SetTranslate(data.translate);
        obj->SetModelHandle(data.modeHandle_);

        // 親設定
        auto gameObj = obj->GetGameObject().lock();
        if (gameObj) {
          for (const auto &parentName : data.parentObjName_) {
            for (const auto &[_, innerMap] : objsMap) {
              for (const auto &[_a, potentialParent] : innerMap) {
                if (potentialParent &&
                    potentialParent->GetName() == parentName) {
                  gameObj->SetParent(potentialParent->GetGameObject());
                  break;
                }
              }
            }
          }
        }

        objDatas_.erase(itData); // 反映済データ削除
      }
    }
  }

  return enviObjs;
}



void SceneLoader::SetParentObjects(
    [[maybe_unused]] const std::shared_ptr<CLEYERA::Component::ObjectComponent> &obj,
    [[maybe_unused]] const std::vector<std::string> &parentNames,
    [[maybe_unused]] const std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>> &objs,
    [[maybe_unused]] std::vector<std::shared_ptr<EnvironmentObject>> &environmentObjects) {}

std::shared_ptr<EnvironmentObject> SceneLoader::CreateEnvironmentObject(
    [[maybe_unused]] const SceneObjData &data,
    [[maybe_unused]] const std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>> &objs) {
  return std::shared_ptr<EnvironmentObject>();
}

SceneObjData SceneLoader::LoadobjData(nlohmann::json object, [[maybe_unused]] SceneObjData data,
                                      std::string name) {

  SceneObjData newData{};
  // insか通常
  std::string drawType = object["DrawType"].get<std::string>();
  // object名前
  std::string objectName = object["name"].get<std::string>();

  uint32_t modelHandle = 0;

  if (name != "") {
    newData.parentObjName_.push_back(name);
  }

  // モデルのパスの受け取り
  if (object.contains("Directory_name")) {
    newData.modelDirectoryPath = object["Directory_name"].get<std::string>();
  }
  if (object.contains("file_name")) {
    newData.modelName = object["file_name"].get<std::string>();
  }

  if (newData.modelName != "" && newData.modelDirectoryPath != "") {
    modelHandle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(
        newData.modelDirectoryPath, newData.modelName);
  }

  // 座標
  nlohmann::json &transform = object["transform"];
  Math::Vector::Vec3 translate, rotate, scale;
  translate.x = (float)transform["translate"][0];
  translate.y = (float)transform["translate"][2];
  translate.z = (float)transform["translate"][1];

  // rotate
  rotate.x = -(float)transform["rotate"][0];
  rotate.y = -(float)transform["rotate"][2];
  rotate.z = -(float)transform["rotate"][1];

  // scale
  scale.x = (float)transform["scale"][0];
  scale.y = (float)transform["scale"][2];
  scale.z = (float)transform["scale"][1];

  rotate.x = Math::Vector::Func::degreesToRadians(rotate.x);
  rotate.y = Math::Vector::Func::degreesToRadians(rotate.y);
  rotate.z = Math::Vector::Func::degreesToRadians(rotate.z);

  newData.scale = scale;
  newData.rotate = rotate;
  newData.translate = translate;
  newData.modeHandle_ = modelHandle;

  // 子の読み込み
  if (object.contains("children")) {
    nlohmann::json &child = object["children"];
    for (size_t i = 0; i < child.size(); i++) {
      std::string childType = child[i]["type"].get<std::string>();

      if (childType.compare("MESH") == 0) {
        this->LoadobjData(child[i], newData, objectName);
      }
    }
  }

  objDatas_[objectName] = newData;

  return {};
}
