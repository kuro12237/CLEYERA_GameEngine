#pragma once
#include "CLEYERA.h"
#include "../Util/UtilFunc.h"

/// <summary>
/// プレイヤー弾インターフェース
/// </summary>
class IPlayerBullet : public CLEYERA::Component::ObjectComponent {
 public:
   IPlayerBullet() {};
   virtual ~IPlayerBullet() {};

   bool GetIsDeadFlag() { return isDeadFlag_; }

 private:
 protected:
   /// <summary>
   /// timerの更新
   /// </summary>
   void CalcAliveTimer();

   bool isDeadFlag_ = false;

   uint32_t timer_ = 0;
   uint32_t maxTimer_ = 20;
   float flame_ = 0.0f;
};
