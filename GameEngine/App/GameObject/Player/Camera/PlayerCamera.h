#pragma once
#include "CLEYERA.h"
#include"../IPlayer.h"

class PlayerCamera : public CLEYERA::Component::CameraCompornent ,public IPlayer{
 public:
   PlayerCamera() {};
   ~PlayerCamera() {};

   void Init() override;

   void Update() override;

   void SetTarget(const Math::Vector::Vec3 &target) { target_ = &target; };
 private:
   void ImGuiFunc();

   const Math::Vector::Vec3 *target_ = nullptr;
   Math::Vector::Vec3 offset_{};
};
