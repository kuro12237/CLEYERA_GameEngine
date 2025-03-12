#pragma once
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"
#include "../TransformBase/TransformBase.h"

namespace CLEYERA {
namespace Util {

class Camera : public TransformBase {
 public:
   Camera() {};
   ~Camera() {};

   void Init() override;

   void Update() override;

 private:
   Math::Matrix::Mat4x4 matProj_ = {};
   Math::Matrix::Mat4x4 matView_ = {};


   const Math::Vector::Vec3 dfScale = {1.0f, 1.0f, 1.0f};

   float fov_ = 0.45f;
   float aspectRatio_ = static_cast<float>(CLEYERA::Base::Win::WinApp::GetKWindowWidth() / CLEYERA::Base::Win::WinApp::GetKWindowHeight());

   float nearClip_ = 0.1f;
   float farClip_ = 1000.0f;
};

} // namespace Util
} // namespace CLEYERA
