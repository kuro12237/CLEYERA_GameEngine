#pragma once

#include "../Utility/Camera/Camera.h"
#include "../Utility/Camera/CameraManager.h"

namespace CLEYERA {

namespace Component {

class CameraCompornent {
 public:
   CameraCompornent();
   virtual ~CameraCompornent() {};

   virtual void Init() = 0;

   virtual void Update() = 0;

   void ImGuiUpdate();

   std::weak_ptr<Util::Camera> GetCamera() { return camera_; };

 private:
   CLEYERA::Manager::CameraManager *cameraManager_ = nullptr;

 protected:
   std::string name_ = "";

   //std::function<void> ImGuiFunc_ = nullptr;

   /// <summary>
   /// 切り替えたいときこの関数を呼び出す
   /// </summary>
   void CameraChange();

   std::shared_ptr<CLEYERA::Util::Camera> camera_ = nullptr;

   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 degreeRotate_ = {};
   Math::Vector::Vec3 translate_ = {0.0f, 0.0f, -16.0f};
};

} // namespace Component
} // namespace CLEYERA