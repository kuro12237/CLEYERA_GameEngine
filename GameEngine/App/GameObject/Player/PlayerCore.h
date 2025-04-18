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

   void ChangeState(std::unique_ptr<IPlayerState> newState);

   IPlayerState *GetState() { return state_.get(); }

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