#pragma once
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../DX/DXManager.h"

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

   void Update();

#pragma region Get

   std::vector<SVertex> &GetVertexdata() { return vertexData_; }
   uint32_t GetByteSize() { return bytesSize_; }
   Base::DX::DXBufferResource<SVertex> *GetResource() { return buf_.get(); }

#pragma endregion

 private:
   std::unique_ptr<Base::DX::DXBufferResource<SVertex>> buf_ = nullptr;
   std::vector<SVertex> vertexData_ = {};

   uint32_t bytesSize_ = 0;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA