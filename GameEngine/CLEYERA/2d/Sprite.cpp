#include "Sprite.h"

CLEYERA::Sprite2d::Sprite::Sprite() { cameraManager = Manager::CameraManager::GetInstance(); }

void CLEYERA::Sprite2d::Sprite::Create() {

  mesh_ = std::make_unique<System::SpriteMesh>();
  mesh_->Create();

  meshData_.resize(4);
  mesh_->SetMeshData(meshData_);
}

void CLEYERA::Sprite2d::Sprite::TransfarBuf() { mesh_->Transfar(); }

void CLEYERA::Sprite2d::Sprite::Draw() { mesh_->CommandIBVB(); }

void CLEYERA::Sprite2d::Sprite::Update() {


    // 左下
  meshData_[0].vertex.x = -anker_->x * size_->x;
  meshData_[0].vertex.y = -anker_->y * size_->y;

  // 左上
  meshData_[1].vertex.x = -anker_->x * size_->x;
  meshData_[1].vertex.y = (1.0f - anker_->y) * size_->y;

  // 右上
  meshData_[2].vertex.x = (1.0f - anker_->x) * size_->x;
  meshData_[2].vertex.y = (1.0f - anker_->y) * size_->y;

  // 右下
  meshData_[3].vertex.x = (1.0f - anker_->x) * size_->x;
  meshData_[3].vertex.y = -anker_->y * size_->y;

  mesh_->Transfar();
}
