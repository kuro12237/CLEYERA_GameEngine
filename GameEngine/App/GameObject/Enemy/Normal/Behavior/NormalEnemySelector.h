#pragma once


/**
 * @file NormalEnemySelector.h
 * @brief 雑魚敵セレクターのクラス
 * @author 茂木翼
 */

//Selector
//成功する子が見つかるまで1つ1つ実行する
//条件分岐はここでやるよ

#include "NormalEnemyBehaviorNode.h"

/// <summary>
/// 雑魚敵セレクター
/// </summary>
class NormalEnemySelector :public NormalEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NormalEnemySelector() = default;

    /// <summary>
    /// 子を追加
    /// </summary>
    /// <param name="child"></param>
    inline void AddChild(std::unique_ptr<NormalEnemyBehaviorNode> child) {
        children_.push_back(std::move(child));
    }

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    inline EnemyNodeState Execute(BaseNormalEnemy * baseBossEnemy) override {
        //子ノードに入っているものを全て実行していく
        for (const auto & child : children_ ) {
            EnemyNodeState status = child->Execute(baseBossEnemy);
            //失敗ではなかったら状態を返す
            if ( status != EnemyNodeState::Failure ) {
                return status;
            }
        }
        return EnemyNodeState::Failure;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~NormalEnemySelector()override = default;



protected:
    //子ノード
    std::vector<std::unique_ptr<NormalEnemyBehaviorNode>> children_;

};