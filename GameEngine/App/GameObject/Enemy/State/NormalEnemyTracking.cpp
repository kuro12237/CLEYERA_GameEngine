#include "NormalEnemyTracking.h"

#include <imgui.h>

#include "VectorCalculation.h"
#include "Enemy/NormalEnemy/NormalEnemy.h"

NormalEnemyTracking::NormalEnemyTracking(){
	stateName_ = "Tracking";
}

void NormalEnemyTracking::Initialize(){

}

void NormalEnemyTracking::Update(NormalEnemy* normalEnemy){
	//アニメーションしないように時間を設定する
	normalEnemy->SetAnimationTime(NO_ANIMATION_TIME_);

	//敵本体の座標を取得
	Vector3 worldPosition = normalEnemy->GetWorldPosition();
	//プレイヤーの座標を取得
	Vector3 playerPosition = normalEnemy->GetPlayerPosition();

	//向きを求める
	direction_ = VectorCalculation::Subtract(playerPosition, worldPosition);
	//正規化
	direction_ = VectorCalculation::Normalize(direction_);
	//スピード
	const float SPEED_AMOUNT = 0.05f;
	Vector3 speed = VectorCalculation::Multiply(direction_, SPEED_AMOUNT);
	//加算(感電時を除く)
	if (normalEnemy->GetIsElectricShock() == false) {
		normalEnemy->SetTranslate(VectorCalculation::Add(worldPosition, speed));

	}
	
#ifdef _DEBUG
	ImGui::Begin("強敵追跡");
	ImGui::InputFloat3("方向", &direction_.x);

	ImGui::End();
#endif // DEBUG


}
