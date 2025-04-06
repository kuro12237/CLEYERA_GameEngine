#pragma once
#include"ObjectCompornent.h"

namespace CLEYERA {

namespace Manager {

class ObjectManager {
 public:

	 static ObjectManager *GetInstance() {
      static ObjectManager instance;
      return &instance;
   }

	 void Update();

	 void AddObject(std::shared_ptr<Model3d::Game3dObject> object) { objectList_.push_back(object); }


	 const std::vector<std::weak_ptr<Model3d::Game3dObject>>& GetObjectList() const { return objectList_; }

 private:

	 std::vector<std::weak_ptr<Model3d::Game3dObject>> objectList_ = {};

#pragma region Singleton

   ObjectManager() = default;
   ~ObjectManager() = default;
   ObjectManager(const ObjectManager &) = delete;
   ObjectManager &operator=(const ObjectManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA