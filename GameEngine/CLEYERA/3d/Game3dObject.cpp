#include "Game3dObject.h"

void CLEYERA::Model3d::Game3dObject::Create(uint32_t handle) {
   modelManager_ = Manager::ModelManager::GetInstance();

   modelHandle_ = handle;
   std::weak_ptr<Model> model = modelManager_->GetModel(handle);

   model_ = std::shared_ptr<Model>(model);


}

void CLEYERA::Model3d::Game3dObject::Update() {

this->TransformUpdate();

}
