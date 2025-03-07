#include "ImGuiManager.h"

namespace CLEYERA {

namespace Utility {

ImGuiManager *CLEYERA::Utility::ImGuiManager::GetInstance() {
   static ImGuiManager instance;
   return &instance;
}

void ImGuiManager::Init() { common_.lock()->Init(); }

void ImGuiManager::Begin() { common_.lock()->Begin(); }

void ImGuiManager::Render() { common_.lock()->Render(); }

} // namespace Utility
} // namespace CLEYERA