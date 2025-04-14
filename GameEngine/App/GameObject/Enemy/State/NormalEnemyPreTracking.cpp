#include "NormalEnemyPreTracking.h"

#include "VectorCalculation.h"
#include "Enemy/NormalEnemy/NormalEnemy.h"
#include "NormalEnemyTracking.h"

NormalEnemyPreTracking::NormalEnemyPreTracking(){
	stateName_ = "PreTracking";
}

void NormalEnemyPreTracking::Initialize(){

}

void NormalEnemyPreTracking::Update(NormalEnemy* normalEnemy) {
	//アニメーションしないように時間を設定する
	normalEnemy->SetAnimationTime(NO_ANIMATION_TIME_);
	//追跡前の方向
	Vector3 preDirection = {};
	if (isGetPreDirection_==false) {
		//取得
		preDirection = normalEnemy->GetDirection();
		//取得済みにする
		isGetPreDirection_ = true;
	}


	//プレイヤーの座標
	Vector3 playerPosition = normalEnemy->GetPlayerPosition();
	//回転する
	const float_t ROTATE_VALUE = 0.1f;
	ROTATE_VALUE;



	//追跡へ移動
	normalEnemy->ChengeState(std::make_unique<NormalEnemyTracking>());
}
