#include "CameraManager.h"

void CLEYERA::Manager::CameraManager::Init() { dxManager_ = Base::DX::DXManager::GetInstance();

commandManager_ = Base::DX::DXCommandManager::GetInstace();

}

void CLEYERA::Manager::CameraManager::Update() {
   if (!camera_.expired()) {
	   //カメラをセットしていない
	   assert(false);
   }

   auto camera = camera_.lock();

   camera->TransformUpdate();
}

void CLEYERA::Manager::CameraManager::BindCommand(UINT num) {
   if (!camera_.expired()) {
      // カメラをセットしていない
      assert(false);
   }

 commandManager_->GraphicsCommandCall(num, camera_.lock()->GetBuf());
}
