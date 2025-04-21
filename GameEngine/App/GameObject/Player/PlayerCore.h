#pragma once
#include"CLEYERA.h"

class PlayerCore : public CLEYERA::Component::ObjectComponent {
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

 private:
};