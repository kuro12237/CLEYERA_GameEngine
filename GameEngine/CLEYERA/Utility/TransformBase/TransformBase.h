#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace system {

struct SCamera {

   Math::Matrix::Mat4x4 matProj_ = {};
   Math::Matrix::Mat4x4 mtxProjInv_ = {};
   Math::Matrix::Mat4x4 matView_ = {};
   Math::Matrix::Mat4x4 mtxViewInv_ = {};
   Math::Matrix::Mat4x4 mtxVP_ = {};
   Math::Matrix::Mat4x4 orthographic = {};
   Math::Vector::Vec4 cameraPos_ = {};
};
struct forWorldMat {
   Math::Matrix::Mat4x4 worldMat_ = {};
   Math::Matrix::Mat4x4 worldMatInv_ = {};
   Math::Matrix::Mat4x4 WPV_ = {};
};
} // namespace system

class TransformBase {
 public:
   TransformBase();
   virtual ~TransformBase() {};

   void TransformUpdate();

   Math::Vector::Vec3 GetWorldPos();
   Math::Vector::Vec3 GetWorldRotate();
   Math::Vector::Vec3 GetWorldScale();

   Math::Vector::Vec3 GetScale() const { return *scale_; }
   Math::Vector::Vec3 GetRotate() const { return *rotate_; }
   Math::Vector::Vec3 GetTranslate() const { return *translate_; }
   Math::Matrix::Mat4x4 GetMat() const { return mat_; }
   const Math::Matrix::Mat3x4 &GetMat3x4() const { return forGpumat_; }

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
  
 
   // ray
   Math::Matrix::Mat3x4 forGpumat_ = {};
};

} // namespace Util
} // namespace CLEYERA