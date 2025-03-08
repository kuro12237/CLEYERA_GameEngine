#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include"../../DX/DXManager.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

struct SVertex {

   Math::Vector::Vec3 pos = {};
};

/// <summary>
/// 3d頂点
/// </summary>
class Vertex {
 public:
   Vertex() {};
   ~Vertex() {};

   void Init();
   \

 private:
   std::unique_ptr<Base::DX::DXBufferResource<SVertex>> buf_ = nullptr;
   std::vector<SVertex> vertexData_ = {};
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA