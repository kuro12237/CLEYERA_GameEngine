#pragma once
#include"CLEYERA.h"

class PlayerCamera:public CLEYERA::Component::CameraCompornent {
 public:
   PlayerCamera() {};
   ~PlayerCamera() {};

   void Init() override;

   void Update() override;

 private:
};
