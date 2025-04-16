#include "SceneLoader.h"

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

SceneObjData SceneLoader::LoadobjData(nlohmann::json object, SceneObjData data, std::string name) {

   SceneObjData newData{};
   // insか通常
   std::string drawType = object["DrawType"].get<std::string>();
   // object名前
   std::string objectName = object["name"].get<std::string>();

   // uint32_t modelHandle = 0;

   if (name != "") {
      newData.parentObjName_.push_back(name);
   }

   // モデルのパスの受け取り
   if (object.contains("Directory_name") == 0) {
      newData.modelDirectoryPath = object["Directory_name"].get<std::string>();
   }
   if (object.contains("file_name") == 0) {
      newData.modelName = object["file_name"].get<std::string>();
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

   objDatas_[objectName] = newData;

   return {};
}
