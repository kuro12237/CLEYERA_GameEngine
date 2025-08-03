#include "ABotton.h"

void ABotton::Init(){
	SetCategory("bota");

}

void ABotton::Update(){

#ifdef _DEBUG
	ImGui::Begin("ABotton");
	ImGui::SliderFloat("Translate",&translate_.x, -10.0f, 10.0f);
	ImGui::End();
#endif // _DEBUG


	// 更新
	TransformUpdate();
}
