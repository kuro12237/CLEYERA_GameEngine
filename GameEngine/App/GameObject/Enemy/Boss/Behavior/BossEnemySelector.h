#pragma once


/**
 * @file EnemyManager.h
 * @brief ボスの合成ノードクラス
 * @author 茂木翼
 */

//Selector
//成功する子が見つかるまで1つ1つ実行する


#include "BossEnemyBehaviorNode.h"

/// <summary>
/// 合成ノード
/// </summary>
class BossEnemySelector :public BossEnemyBehaviorNode {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemySelector() = default;

    /// <summary>
    /// 子を追加
    /// </summary>
    /// <param name="child"></param>
    inline void AddChild(std::unique_ptr<BossEnemyBehaviorNode> child) {
        children_.push_back(std::move(child));
    }

    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="baseBossEnemy"></param>
    /// <returns></returns>
    inline NodeState Execute(BaseBossEnemy* baseBossEnemy) override {
        //子ノードに入っているものを全て実行していく
        for ( auto & child : children_ ) {
            NodeState status = child->Execute(baseBossEnemy);
            //失敗ではなかったら状態を返す
            if ( status != NodeState::Failure ) {
                return status;
            }
        }
        return NodeState::Failure;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BossEnemySelector()override = default;



private:
    //子ノード
    std::vector<std::unique_ptr<BossEnemyBehaviorNode>> children_;

};