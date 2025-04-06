#include "OBBCollider.h"

void CLEYERA::Util::Collider::OBBCollider::ColliderImGuiUpdate() {

   ImGui::SliderFloat3("Center", &obb_->center.x, 0.0f, 0.0f);
   ImGui::SliderFloat3("Rotate", &obb_->rotate.x, 0.0f, 0.0f);
   ImGui::SliderFloat3("Size", &obb_->size.x, 0.0f, 0.0f);
}
