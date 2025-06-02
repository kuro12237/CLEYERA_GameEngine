#include "SkyBox.h"

void CLEYERA::Manager::SkyBox::Init() {
  modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
  renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();
  colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();
  objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();

  modelHandle_ = modelManager_->LoadModel(dfFilePath_, objName_);

  gameObj_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();

  gameObj_->Create(modelHandle_);
  gameObj_->SetScale(scaleTerrain_);
  gameObj_->SetRotate(rotateTerrain_);
  gameObj_->SetTranslate(translateTerrain_);
  gameObj_->SetName(objName_);
  this->gameObj_->Update();

  renderManager_->PushObj(gameObj_);
  objectManager_->AddObject(gameObj_);
}

void CLEYERA::Manager::SkyBox::Update() {}

void CLEYERA::Manager::SkyBox::Finalize() { gameObj_.reset(); }

void CLEYERA::Manager::SkyBox::CheckObjct() {}

void CLEYERA::Manager::SkyBox::ChengeData(uint32_t modelHandle) {
  modelHandle_ = modelHandle;
  gameObj_->ChangeModel(modelHandle);
}
