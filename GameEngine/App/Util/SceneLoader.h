#pragma once
#include "CLEYERA.h"

struct SceneObjData {

   Math::Vector::Vec3 scale = {};
   Math::Vector::Vec3 rotate = {};
   Math::Vector::Vec3 translate = {};

   std::string modelDirectoryPath = "";
   std::string modelName = "";
   std::vector<std::string> parentObjName_;
};

class SceneLoader {
 public:
   SceneLoader() {};
   ~SceneLoader() {};

   void LoadSceneData(std::string path);

   void SettingData();

 private:
   nlohmann::json deserialized = nullptr;

   SceneObjData LoadobjData(nlohmann::json object, SceneObjData data = {}, std::string name = "");

   const std::string directoryPath_ = "Resources/SceneData/";

   std::map<std::string, SceneObjData> objDatas_;
};
