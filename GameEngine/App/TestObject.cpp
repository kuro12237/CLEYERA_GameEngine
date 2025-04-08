#include "TestObject.h"

void TestObject::Init() {

	translate_.y = 10;
   CreateCollider(ColliderType::OBB);
}

void TestObject::Update() {
	ImGuiUpdate();

	CLEYERA::Manager::Terrain::GetInstance()->CheckObjct(translate_);

}
