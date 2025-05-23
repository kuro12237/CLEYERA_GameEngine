#pragma once
#include "Compornent/ObjectCompornent.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// Objct管理クラス
/// </summary>
class ObjectManager {
 public:
   static ObjectManager *GetInstance() {
      static ObjectManager instance;
      return &instance;
   }

   void Update();

   void ImGuiUpdate();

   void AddObject(std::shared_ptr<Model3d::Game3dObject> object) { objectList_.push_back(object); }

   const std::vector<std::weak_ptr<Model3d::Game3dObject>> &GetObjectList() const { return objectList_; }

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