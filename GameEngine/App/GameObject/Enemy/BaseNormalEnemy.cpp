#include "BaseNormalEnemy.h"

void BaseNormalEnemy::ChangeState(std::unique_ptr<BaseNormalEnemyState> newState) {
	
	// 前回と違った場合だけ通す
   if (currentState_!=newState) {
      // 新しく入れる
      currentState_ = std::move(newState);
      // 初期化
      currentState_->Initialize();
   }
}
