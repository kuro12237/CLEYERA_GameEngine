#include "ABotton.h"

#include <../App/Scene/TitleScene.h>


void ABotton::SetTitleScene(TitleScene * titleScene) {
	this->titleScene_ = titleScene;
}

void ABotton::Init(){
	SetCategory("bota");
	isGravity_ = false;
}

void ABotton::Update(){

#ifdef _DEBUG
	ImGui::Begin("ABotton");
	ImGui::SliderFloat("Translate",&translate_.x, -10.0f, 10.0f);
	ImGui::End();
#endif // _DEBUG

	if ( titleScene_->GetIsStart() == true ) {
		
		
		theta2_ += 0.01f;
		t_ = 0.01f;
		if ( rotate_.y > std::numbers::pi_v<float_t>*8.0f ) {
			titleScene_->SetIsEndProcess(true);
		}

		//
		//Math::Vector::Vec3 start = { -1.169f,0.0f,0.0f };
		//Math::Vector::Vec3 end = { -1.169f, std::numbers::pi_v<float_t>*8.0f, 0.0f };
		//rotate_ = Math::Vector::Func::Lerp(start, end, t_);


		rotate_.y += 0.5f;
	}
	else {
		theta_ += 0.01f;
		addValueY_ = std::sinf(theta_) * 2.0f;
	}
#ifdef _DEBUG
	ImGui::Begin("ABotton");
	ImGui::SliderFloat3("Rotate", &rotate_.x, 0.0f, 20.0f);
	ImGui::InputFloat("T", &t_);
	ImGui::InputFloat("Theta2", &theta2_);
	ImGui::End();

#endif // _DEBUG



	translate_.y = 2.0f + addValueY_+ tmpY_;

	// 更新
	TransformUpdate();
}