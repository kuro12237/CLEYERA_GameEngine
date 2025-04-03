#include "Game3dObject.h"

void CLEYERA::Model3d::Game3dObject::Create(uint32_t handle) {
   modelManager_ = Manager::ModelManager::GetInstance();
   cameraManager_ = Manager::CameraManager::GetInstance();

   commandManager_ = Base::DX::DXCommandManager::GetInstace();

   modelHandle_ = handle;

   // modelmanagerの中にあるデータを基に新たに作成
   std::weak_ptr<Model> model = modelManager_->GetModel(handle);

   model_ = std::shared_ptr<Model>(model);

 
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


   //頂点、インデックス、形状設定
   model_->RasterDraw3d();

   commandManager_->DrawIndexCall(model_->GetMeshData()->GetData().indecs.size());
}
