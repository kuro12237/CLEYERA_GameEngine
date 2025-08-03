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

	if ( isStart_ == true ) {

	}
	else {
		theta_ += 0.01f;
		addValueY_ = std::sinf(theta_) * 2.0f;
	}


	translate_.y = 1.0f + addValueY_;

	// 更新
	TransformUpdate();
}
