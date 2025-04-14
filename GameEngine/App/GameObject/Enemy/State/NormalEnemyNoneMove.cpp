#include "NormalEnemyNoneMove.h"

#include "Enemy/NormalEnemy/NormalEnemy.h"

NormalEnemyNoneMove::NormalEnemyNoneMove(){
	stateName_ = "NoneMove";
	
}

void NormalEnemyNoneMove::Initialize(){
	//動かない
	speed_ = { .x = 0.0f, .y = 0.0f, .z = 0.0f };
}


void NormalEnemyNoneMove::Update(NormalEnemy* normalEnemy){
	//スピードの設定
	normalEnemy->SetSpeed(speed_);
}
