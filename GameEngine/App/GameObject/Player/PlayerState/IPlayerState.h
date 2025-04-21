#pragma once
#include "pch/Pch.h"
#include"CLEYERA.h"

class PlayerCore;
/// <summary>
/// player
/// </summary>
class IPlayerState {
 public:
   IPlayerState() { input_ = CLEYERA::Manager::InputManager::GetInstance(); };
   virtual ~IPlayerState() {};

   virtual void Init() = 0;

   virtual void Update() = 0;

   void SetCore(PlayerCore* core) { core_ = core; }

 private:
 protected:

   CLEYERA::Manager::InputManager *input_ = nullptr;
   PlayerCore* core_;
};
