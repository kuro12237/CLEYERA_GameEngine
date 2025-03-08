#include "Model3d.h"

void CLEYERA::Model3d::Model::Init() {
   vertex_ = std::make_unique<system::Vertex>();
   vertex_->Init();


}

void CLEYERA::Model3d::Model::Update() {}
