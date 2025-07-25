#pragma once
#include"../GameObject/EnvironmentObject/EnvironmentObject.h"


#include <fstream>

struct SceneObjData {

   Math::Vector::Vec3 scale = {};
   Math::Vector::Vec3 rotate = {};
   Math::Vector::Vec3 translate = {};

   std::string modelDirectoryPath = "";
   std::string modelName = "";
   uint32_t modeHandle_ = 0;
   std::vector<std::string> parentObjName_;
};

class SceneLoader {
 public:
   SceneLoader() {};
   ~SceneLoader() {};

   void LoadSceneData(std::string path);

   std::vector<std::weak_ptr<EnvironmentObject>>SettingData();

 private:

	 void SetParentObjects(const std::shared_ptr<CLEYERA::Component::ObjectComponent> &obj, const std::vector<std::string> &parentNames, const std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>> &objs, std::vector<std::shared_ptr<EnvironmentObject>> &environmentObjects) ;
   std::shared_ptr<EnvironmentObject> CreateEnvironmentObject(const SceneObjData &data, const std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>> &objs);


   nlohmann::json deserialized = nullptr;

   SceneObjData LoadobjData(nlohmann::json object, SceneObjData data = {}, std::string name = "");

   const std::string directoryPath_ = "Resources/SceneData/";

   std::map<std::string, SceneObjData> objDatas_;
};
