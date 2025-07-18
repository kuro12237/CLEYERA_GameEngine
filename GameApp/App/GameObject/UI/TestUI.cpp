#include "TestUI.h"

void TestUI::Init() {
  this->Create();

  handle_ = texManager_->LoadPngTex("UI/numbers");
  this->name_ = "test";
  size = texManager_->GetTexData(handle_).lock()->GetSize();
}

void TestUI::Update() {

  this->sprite_->LayerChange(3);

  this->sprite_->LayerChange(0);

  this->sprite_->Update();
  this->WorldMatUpdate();
}

void TestUI::ImGuiUpdate() {

  if (ImGui::TreeNode(name_.c_str())) {

    this->TransformImGuiUpdate();

    ImGui::Separator();

    ImGui::DragFloat2("size", &size.x, 4.0f);
    ImGui::DragFloat2("anker", &anker.x);
    ImGui::DragFloat2("leftTop", &LeftTop.x,0.1f);
    ImGui::DragFloat2("RightTop", &RightTop.x, 0.1f);
    ImGui::DragFloat2("leftBottom", &LeftBottom.x, 0.1f);
    ImGui::DragFloat2("RightBottom", &RightBottom.x, 0.1f);

    ImGui::TreePop();
  }
}
