#include "TestObject.h"

void TestObject::Init() {
   name_ = "TestObject";

   CreateCollider(ColliderType::OBB);
}

void TestObject::Update() { ImGuiUpdate(); }
