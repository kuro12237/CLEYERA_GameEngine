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

std::vector<std::shared_ptr<EnvironmentObject>>
SceneLoader::SettingData(std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>> objs) {

  std::vector<std::shared_ptr<EnvironmentObject>> enviObjs;
  for (auto obj : objs) {
    auto it = obj.lock();
    if (!it) {
      continue; // ロック失敗時はスキップ
    }
    std::string name = it->GetName();

    if (objDatas_.find(name) != objDatas_.end()) {

      auto data = objDatas_[name];

      it->SetScale(data.scale);
      it->SetRotate(data.rotate);
      it->SetTranslate(data.translate);
      it->SetModelHandle(data.modeHandle_);

      auto gameObj = it->GetGameObject().lock();

      for (std::string pName : data.parentObjName_) {

        for (auto pObj : objs) {
          if (pObj.lock()->GetName() == pName) {
            gameObj->SetParent(pObj.lock()->GetGameObject());
            break;
          }
        }
      }
      objDatas_.erase(name);
    }
  }

   // objsに登録されている背景オブジェクトの作成
   for (auto data : objDatas_) {
      auto it = data.second;

      std::shared_ptr<EnvironmentObject> enviObj = std::make_shared<EnvironmentObject>();
      enviObj->SetName(data.first);
      enviObj->Init();
      enviObj->SetScale(it.scale);
      enviObj->SetRotate(it.rotate);
      enviObj->SetTranslate(it.translate);
      enviObj->SetModelHandle(it.modeHandle_);
      auto gameObj = enviObj->GetGameObject().lock();

      // 子
      for (std::string pName : it.parentObjName_) {

         for (auto pObj : objs) {
            if (pObj.lock()->GetName() == pName) {

               gameObj->SetParent(pObj.lock()->GetGameObject());
               break;
            }
         }
      }
    }

    enviObjs.push_back(enviObj);
  }
  objDatas_.clear();
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
