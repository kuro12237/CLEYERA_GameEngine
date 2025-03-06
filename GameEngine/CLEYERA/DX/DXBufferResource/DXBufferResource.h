#pragma once
#include "../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

/// <summary>
///
/// </summary>
template <typename T> class DXBufferResource {
 public:
   DXBufferResource() {};
   ~DXBufferResource() {};

   void Update();

#pragma region Set
   void SetDevice(ID3D12Device5* device) { device_ = device; }
   void SetParam(const T &param) { param_ptr_ = param; }
   void SetResource(ComPtr<ID3D12Resource> resource) { buffer_ = std::move(resource); };
#pragma endregion

#pragma region Get

   ID3D12Resource *GetResource()const { return buffer_.Get(); }

#pragma endregion

   void CreateBuffer(D3D12_HEAP_PROPERTIES heapParam, D3D12_HEAP_FLAGS HeapFlags, D3D12_RESOURCE_DESC pDesc, D3D12_RESOURCE_STATES state, D3D12_CLEAR_VALUE value);

 private:
   size_t instanceNum_ = 1;

   const T *param_ptr_ = nullptr;
   ComPtr<ID3D12Resource> buffer_ = nullptr;

   ID3D12Device5* device_;
};

template <typename T> inline void DXBufferResource<T>::Update() {}

template <typename T> inline void DXBufferResource<T>::CreateBuffer(D3D12_HEAP_PROPERTIES heapParam, D3D12_HEAP_FLAGS HeapFlags, D3D12_RESOURCE_DESC pDesc, D3D12_RESOURCE_STATES state, D3D12_CLEAR_VALUE value) {

   HRESULT hr = device_->CreateCommittedResource(&heapParam, HeapFlags, &pDesc, state, &value, IID_PPV_ARGS(&buffer_));
   assert(SUCCEEDED(hr));
}

} // namespace DX
} // namespace Base
} // namespace CLEYERA