#pragma once
#include "../../pch/Pch.h"
#include "../../DX/DXBufferResource/DXBufferResource.h"
#include "../../DX/DXManager.h"
#include "../Blas/Blas.h"

namespace CLEYERA {

namespace Model3d {

namespace system {

/// <summary>
/// 頂点データ
/// </summary>
struct S2Vertex {

   Math::Vector::Vec4 pos = {};
   Math::Vector::Vec2 texCoord = {};
   Math::Vector::Vec3 normal = {};
};

/// <summary>
/// modelのメッシュデータ
/// </summary>
struct VertexData {

   std::vector<S2Vertex> vertices;
   std::vector<uint32_t> indecs;
};

} // namespace system

/// <summary>
/// メッシュのデータ
/// </summary>
class MeshData {
 public:
   MeshData() {};
   ~MeshData() {};

   /// <summary>
   /// データ作成
   /// </summary>
   void Create(aiMesh *mesh);


#pragma region Get

   system::VertexData GetData() const { return data_; }

#pragma endregion

 private:
   system::VertexData data_ = {};

   ID3D12Device5 *device_ = nullptr;

   std::unique_ptr < Base::DX::DXBufferResource<system::S2Vertex>> vertBuf_ = nullptr;
   std::unique_ptr<Base::DX::DXBufferResource<uint32_t>> indexBuf_ = nullptr;

   std::unique_ptr<system::Blas> blas_ = nullptr;

};

} // namespace Model3d

} // namespace CLEYERA