#include "Grid.h"

void CLEYERA::DebugTools::Grid::Init() {

   uint32_t modelHandle = CLEYERA::Manager::ModelManager::GetInstance()->LoadModel(planePath_, planeName_);
   grid_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();
   grid_->Create(modelHandle);
   grid_->SetScale(scale_);
   grid_->SetRotate(rotate_);
   grid_->SetTranslate(translate_);

   CLEYERA::Manager::RenderManager::GetInstance()->PushObj(grid_);

   lines_ = std::make_shared<CLEYERA::Model3d::Line3d>();
   lines_->Init(lineMax_);
   lines_->SetLinePos(positions_);
   lines_->SetScale(scale_);
   lines_->SetRotate(rotate_);
   lines_->SetTranslate(translate_);

   positions_.resize(lineVertCount_);

   CLEYERA::Manager::RenderManager::GetInstance()->PushLine3d(lines_);
}

void CLEYERA::DebugTools::Grid ::Update() {
 

   lines_->Update();
   grid_->Update();
}

void CLEYERA::DebugTools::Grid::ImGuiUpdate() {

  ImGui::Begin("glines");

   for (size_t i = 0; i < positions_.size(); i++) {

      std::string name = "p" + std::to_string(i);
      ImGui::DragFloat3(name.c_str(), &positions_[i].x, 0.5f);
   }
   ImGui::End();
}

void CLEYERA::DebugTools::Grid::DrawRaster3d() { grid_->DrawRaster3d(); }

void CLEYERA::DebugTools::Grid::Finalize() {
   grid_.reset();
   lines_.reset();
}
