#include "SpriteMesh.h"

CLEYERA::Sprite2d::System::SpriteMesh::SpriteMesh() {

  buf_ = std::make_unique<Base::DX::DXBufferResource<Mesh2d>>();
}

void CLEYERA::Sprite2d::System::SpriteMesh::Create() {
  mesh_.resize(4);
  buf_->Init(4);


}

void CLEYERA::Sprite2d::System::SpriteMesh::Transfar() {}

void CLEYERA::Sprite2d::System::SpriteMesh::CommandVB() {}
