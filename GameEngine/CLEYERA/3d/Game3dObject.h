#pragma once
#include "../Utility/TransformBase/TransformBase.h"
#include "ModelManager/ModelManager.h"

namespace CLEYERA {

namespace Model3d {

/// <summary>
/// ゲームオブジェクト
/// </summary>
class Game3dObject : public Util::TransformBase {
 public:
   Game3dObject() {};
   ~Game3dObject() {};

   void Create(uint32_t handle);

   void Update();

   #pragma region Get

   std::weak_ptr<Model> GetModel() { return model_; }

#pragma endregion


 private:
   Manager::ModelManager *modelManager_ = nullptr;

   std::shared_ptr<Model> model_ = nullptr;
   uint32_t modelHandle_ = 0;


};

} // namespace Model3d

} // namespace CLEYERA