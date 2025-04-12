#pragma once
#include "CLEYERA.h"
#include "Camera/PlayerCamera.h"
#include "PlayerCore.h"

/// <summary>
/// プレイヤー管理クラス
/// </summary>
class PlayerManager : public CLEYERA::Component::ManagerCompornent {
 public:
   PlayerManager() {};
   ~PlayerManager() {};

   void Init() override;

   void Update() override;

 private:
   std::shared_ptr<PlayerCore> core_ = nullptr;
   std::shared_ptr<PlayerCamera> camera_ = nullptr;
};
