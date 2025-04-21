#pragma once


/**
 * @file NormalEnemyAttack.h
 * @brief 通常の敵が攻撃するクラス
 * @author 茂木翼
 */

#include "BaseNormalEnemyState.h"


/// <summary>
/// 通常の敵が攻撃する
/// </summary>
class NormalEnemyAttack : public BaseNormalEnemyState {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalEnemyAttack();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="normalEnemy">通常の敵</param>
	void Update(NormalEnemy* normalEnemy)override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemyAttack();
	

private:
	
	

	//0から始める
	const uint32_t RESTART_ATTACK_TIME_ = 0u;
	//攻撃する時間用の時間変化
	const uint32_t DELTA_ATTACK_TIME_ = 1u;
	//攻撃する時間
	const uint32_t JUST_ATTACK_TIME_ = 120u;
	//戻る時間
	const uint32_t RETURN_ATTACK_TIME_ = JUST_ATTACK_TIME_ * 4u;


	//0に戻る
	const float_t RESTART_ANIMATION_TIME_ = 0.0f;
	//増える値
	const float_t DELTA_ANIMATION_TIME_ = 1.0f / 60.0f;
	//戻る時間(4秒いっぱいまで)
	const float_t RETURN_ANIMATION_TIME_ = 5.0f;


private:
	//アニメーションの時間
	float_t animationTime_ = 0.0f;
	//攻撃の時間
	uint32_t attackTime_ = 0u;

};

