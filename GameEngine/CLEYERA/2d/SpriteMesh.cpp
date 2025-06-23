#include "SpriteMesh.h"

CLEYERA::Sprite2d::System::SpriteMesh::SpriteMesh() {

  vertexBuf_ = std::make_unique<Base::DX::DXBufferResource<Mesh2d>>();
  indexBuf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
}

void CLEYERA::Sprite2d::System::SpriteMesh::Create() {
  mesh_.resize(4);
  vertexBuf_->Init(4);
  auto device = Base::DX::DXManager::GetInstance()->GetDevice();
  vertexBuf_->SetDevice(device);
  vertexBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  vertexBuf_->CreateVertexBufferView();

  index_.resize(4);
  indexBuf_->Init(4);
  indexBuf_->SetDevice(device);
  indexBuf_->CreateBuffer(D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
  indexBuf_->CreateIndexBufferView();
}

void CLEYERA::Sprite2d::System::SpriteMesh::Transfar() {
  vertexBuf_->SetParam(*mesh_);
  vertexBuf_->Update();

  indexBuf_->SetParam(index_);
  indexBuf_->Update();
}

void CLEYERA::Sprite2d::System::SpriteMesh::CommandIBVB() {

  vertexBuf_->VBCommand();
  indexBuf_->IBCommand();
}
