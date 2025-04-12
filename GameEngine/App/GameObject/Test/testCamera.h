#pragma once
#include"CLEYERA.h"

class TestCamera {
 public:
   TestCamera() {};
   ~TestCamera() {};

   void Create();

   void Update();

   void Call(UINT num) { camera_->Call(num); }

 private:
   std::shared_ptr<CLEYERA::Util::Camera> camera_ = nullptr;

   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 degreeRotate_ = {};
   Math::Vector::Vec3 translate_ = {0.0f, 0.0f, -16.0f};
};
