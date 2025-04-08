#include "TestObject.h"

void TestObject::Init() {

   translate_.y = 10;
   CreateCollider(ColliderType::OBB);
}

void TestObject::Update() {

   float speed = 0.05f;
   if (inputManager_->PushKey(DIK_LSHIFT)) {
      speed *= 3;
   }
   if (inputManager_->PushKey(DIK_W)) {
      translate_.z += speed;
   }
   if (inputManager_->PushKey(DIK_S)) {
      translate_.z -= speed;
   }
   if (inputManager_->PushKey(DIK_A)) {
      translate_.x -= speed;
   }
   if (inputManager_->PushKey(DIK_D)) {
      translate_.x += speed;
   }

   ImGuiUpdate();

   CLEYERA::Manager::Terrain::GetInstance()->CheckObjct(translate_, 1.0f);
}
