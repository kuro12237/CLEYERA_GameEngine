#include "OBBCollider.h"

void CLEYERA::Util::Collider::OBBCollider::ColliderImGuiUpdate() {}

void CLEYERA::Util::Collider::OBBCollider::Create() {

   line_ = std::make_shared<CLEYERA::Model3d::Line3d>();
   line_->Init(24);

   colors_.resize(48);
   line_->SetLinePos(positions_);
   line_->SetLineColor(colors_);
   line_->SetRotate(*obb_.rotate);
   line_->SetTranslate(*obb_.center);
   line_->SetScale(obb_.size);
   line_->SetMat4x4(*obb_.worldMatrix);

   Util::Collider::system::Func::MakeLinesFromOBB(positions_, obb_);

   line_->Update();
}

void CLEYERA::Util::Collider::OBBCollider::Update() {

   for (size_t i = 0; i < 48; i++) {

      colors_[i] = {1.0f, 0.0f, 0.0f, 1.0f};
   }
   Util::Collider::system::Func::MakeLinesFromOBB(positions_, obb_);

   line_->Update();

   obb_.CalculateOrientations();
}
