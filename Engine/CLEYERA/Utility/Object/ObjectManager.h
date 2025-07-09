#pragma once
#include "Compornent/ObjectCompornent.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// オブジェクトのJson型
/// </summary>
struct ObjectNumData {

  std::string key;
  uint32_t objNum;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(ObjectNumData, key, objNum);
};

/// <summary>
/// Object管理クラス
/// </summary>
class ObjectManager {
public:
  static ObjectManager *GetInstance() {
    static ObjectManager instance;
    return &instance;
  }

  void Update();

  void ImGuiUpdate();

  void AddObject(std::shared_ptr<Model3d::Game3dObject> object) {
    objectList_.push_back(object);
  }

  const std::vector<std::weak_ptr<Model3d::Game3dObject>> &

  GetObjectList() const {
    return objectList_;
  }

  /// <summary>
  /// オブジェクトの合計数を読み込む関数
  /// </summary>
  void LoadObjectData(const std::string &file);

private:
  std::vector<std::weak_ptr<Model3d::Game3dObject>> objectList_ = {};

  std::map<std::string,std::map<std::string, std::shared_ptr<Component::ObjectComponent>>>
      objects_;
  std::map<std::string,std::map<std::string, std::string>> unUseObjsName_;

#pragma region Singleton

  ObjectManager() = default;
  ~ObjectManager() = default;
  ObjectManager(const ObjectManager &) = delete;
  ObjectManager &operator=(const ObjectManager &) = delete;

#pragma endregion
};

} // namespace Manager
} // namespace CLEYERA