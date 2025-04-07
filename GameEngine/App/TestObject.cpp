#include "TestObject.h"

void TestObject::Init() {

   CreateCollider(ColliderType::OBB);
}

void TestObject::Update() {
	ImGuiUpdate();
}
