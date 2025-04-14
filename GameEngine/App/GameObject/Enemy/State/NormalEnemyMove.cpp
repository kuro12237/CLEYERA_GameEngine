#include "NormalEnemyMove.h"

#include <imgui.h>

#include "Enemy/NormalEnemy/NormalEnemy.h"
#include "VectorCalculation.h"


NormalEnemyMove::NormalEnemyMove(){
	stateName_ = "Move";
}

void NormalEnemyMove::Initialize(){
	//方向をランダムで決める
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	std::uniform_real_distribution<float> speedDistribute(-1.0f, 1.0f);
	direction_ = { .x = speedDistribute(randomEngine) ,.y = 0.0f,.z = -speedDistribute(randomEngine) };

#ifdef _DEBUG
	speedAmount_ = 0.05f;//跳ね返りとかを確認するために少し早くする
#endif // _DEBUG

	
	
}

void NormalEnemyMove::Update(NormalEnemy* normalEnemy){
	//アニメーションしないように時間を設定する
	normalEnemy->SetAnimationTime(NO_ANIMATION_TIME_);

	//本体の座標を取得
	Vector3 worldPosition = normalEnemy->GetWorldPosition();
	//正規化
	Vector3 newDirection = VectorCalculation::Normalize(direction_);

	//スピードの値をかける
	Vector3 speed = VectorCalculation::Multiply(newDirection, speedAmount_);
	//加算(感電時を除く)
	if (normalEnemy->GetIsElectricShock() == false) {
		normalEnemy->SetTranslate(VectorCalculation::Add(worldPosition, speed));

	}
#ifdef _DEBUG
	ImGui::Begin("敵通常動作");
	ImGui::InputFloat3("方向", &newDirection.x);
	ImGui::End();
#endif // DEBUG


}
