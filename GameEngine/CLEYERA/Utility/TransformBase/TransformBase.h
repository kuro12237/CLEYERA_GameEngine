#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

class TransformBase {
 public:
   TransformBase() {};
   virtual ~TransformBase() {};

   virtual void Init() {};

   virtual void Update() {};

   Math::Vector::Vec3 GetWorldPos();
   Math::Vector::Vec3 GetWorldRotate();
   Math::Vector::Vec3 GetWorldScale();

   Math::Vector::Vec3 GetScale() const { return *scale_; }
   Math::Vector::Vec3 GetRotate() const { return *rotate_; }
   Math::Vector::Vec3 GetTranslate() const { return *translate_; }

   void SetScale(const Math::Vector::Vec3 &s) { scale_ = &s; }
   void SetRotate(const Math::Vector::Vec3 &r) { rotate_ = &r; }
   void SetTranslate(const Math::Vector::Vec3 &t) { translate_ = &t; }

 protected:
   const Math::Vector::Vec3 *scale_ = nullptr;
   const Math::Vector::Vec3 *rotate_ = nullptr;
   const Math::Quaternon::Qua *qua_ = nullptr;
   const Math::Vector::Vec3 *translate_ = nullptr;

   Math::Matrix::Mat4x4 mat_ = {};

 private:
};

} // namespace Util
} // namespace CLEYERA