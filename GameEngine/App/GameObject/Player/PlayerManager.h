#pragma once
#include "Bullet/PlayerBulletManager.h"
#include "CLEYERA.h"
#include "Camera/PlayerCamera.h"
#include "PlayerCore.h"

#include "Command/PlayerCommandHandler.h"

/// <summary>
/// プレイヤー管理クラス
/// </summary>
class PlayerManager : public CLEYERA::Component::ManagerCompornent {
 public:
   PlayerManager() {};
   ~PlayerManager() {};

   void Init() override;

   void Update() override;


   /// <summary>
   /// プレイヤーの基盤を取得
   /// </summary>
   /// <returns></returns>
   inline PlayerCore* GetPlayerCore() const { 
	   return core_.get();
   }

 private:
   std::unique_ptr<PlayerCommandHandler> handler_ = nullptr;

   std::shared_ptr<PlayerCore> core_ = nullptr;
   std::shared_ptr<PlayerCamera> camera_ = nullptr;
   std::shared_ptr<PlayerBulletManager> bulletManager_ = nullptr;
};
