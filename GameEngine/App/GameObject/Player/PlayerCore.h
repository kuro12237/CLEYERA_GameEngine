#pragma once
#include "CLEYERA.h"
#include "IPlayer.h"
#include "PlayerState/IPlayerState.h"
#include "PlayerState/PlayerIdleState.h"
#include "PlayerState/PlayerMoveState.h"

class PlayerCore : public CLEYERA::Component::ObjectComponent, public IPlayer {
 public:
   PlayerCore() {};
   ~PlayerCore() {};

   void Init() override;

   void Update() override;

   /// <summary>
   /// ワールド座標を取得
   /// </summary>
   /// <returns></returns>
   inline Math::Vector::Vec3 GetWorldPosition() const { 
	   return gameObject_->GetWorldPos();
   }
   void ChangeState(std::unique_ptr<IPlayerState> newState);

   IPlayerState *GetState() { return state_.get(); }

   /// <summary>
   /// 当たった時に呼び出す関数
   /// </summary>
   void HitFunc(std::weak_ptr<CLEYERA::Component::ObjectComponent> other);


#pragma region

   /// <summary>
   /// 移動処理
   /// </summary>
   void Move(const Math::Vector::Vec2 &speed = {1.0f, 1.0f});

   /// <summary>
   /// 回転処理,移動に合わせる
   /// </summary>
   void Rotate();

#pragma endregion

 private:
   float interRotateTarget_ = {};

   std::unique_ptr<IPlayerState> state_ = nullptr;
};