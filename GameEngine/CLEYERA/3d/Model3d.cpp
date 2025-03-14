#include "Model3d.h"

void CLEYERA::Model3d::Model::Init() {


   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   commandManager->CommandClose();
}

void CLEYERA::Model3d::Model::Update() {

}

void CLEYERA::Model3d::Model::Render() {

 
}

void CLEYERA::Model3d::Model::ImGuiUpdate() {

   ImGui::Begin("Vertex_Test");

   ImGui::End();
}
