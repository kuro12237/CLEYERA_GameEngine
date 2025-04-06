#include "Game3dObject.h"

void CLEYERA::Model3d::Game3dObject::Create(uint32_t handle) {
   modelManager_ = Manager::ModelManager::GetInstance();
   cameraManager_ = Manager::CameraManager::GetInstance();
   texManager_ = Manager::TexManager::GetInstance();
   lightManager = Manager::LightManager::GetInstance();

   commandManager_ = Base::DX::DXCommandManager::GetInstace();

   modelHandle_ = handle;

   // modelmanagerの中にあるデータを基に新たに作成
   std::weak_ptr<Model> model = modelManager_->GetModel(handle);

   model_ = std::shared_ptr<Model>(model);
   texHandle_ = model_->GetTexHandle();

   WTCreate(ins_);
}

void CLEYERA::Model3d::Game3dObject::Update() {

   this->TransformUpdate();

   this->ConvertMat();
}

void CLEYERA::Model3d::Game3dObject::DrawRaster3d() {

   /// WTをマップ
   this->SetWorldTransfar();

   cameraManager_->BindCommand(0);
   this->BindWT(1);
   lightManager->DirectionLightCommandBind(3);

   this->BindWT(4);

   cameraManager_->BindCommand(5);
   //頂点、インデックス、形状設定
   model_->RasterDraw3d();

   auto data = texManager_->GetTexData(texHandle_);
   auto handle = Base::DX::DXDescripterManager::GetInstance()->GetSRVGPUHandle(data.lock()->GetSrvIndex());
   commandManager_->GraphicsDescripterTable(2,handle);

   commandManager_->DrawIndexCall(model_->GetMeshData()->GetData().indecs.size());
}
