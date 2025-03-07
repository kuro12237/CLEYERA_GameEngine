#pragma once
#include "../../pch/Pch.h"

#include "../DXDescripter/DXDescripterManager.h"

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
   ~DXBufferResource() {
      if (isRtvUse_)
         descripterManager_->RTVRelease(rtvHandleIndex_);
      if (isSrvUse_)
         descripterManager_->SRV_UAVReleace(srvHandleIndex_);
      if (isDsvUse_)
         descripterManager_->DSVRelease(dsvHandleIndex_);
   }

   void Init();

   void Update();

   void RegisterRTV(D3D12_RENDER_TARGET_VIEW_DESC desc) {
      rtvHandleIndex_ = descripterManager_->RTVAddPtr(buffer_.Get(), desc);
      isRtvUse_ = true;
   }

   void RegisterSRV(D3D12_SHADER_RESOURCE_VIEW_DESC desc) {
      srvHandleIndex_ = descripterManager_->SRVAddCreatePtr(buffer_.Get(), desc);
      isSrvUse_ = true;
   }

   void RegisterUAV(D3D12_SHADER_RESOURCE_VIEW_DESC desc) {
      srvHandleIndex_ = descripterManager_->UAVAddPtr(buffer_.Get(), desc);
      isSrvUse_ = true;
   }

   void RegisterDSV(D3D12_DEPTH_STENCIL_VIEW_DESC desc) {
      dsvHandleIndex_ = descripterManager_->DSVAddPtr(buffer_.Get(), desc);
      isDsvUse_ = true;
   }

#pragma region Set
   void SetDevice(ID3D12Device5 *device) { device_ = device; }
   void SetParam(const T &param) { param_ptr_ = param; }
   void SetResource(ComPtr<ID3D12Resource> resource) { buffer_ = std::move(resource); };
#pragma endregion

#pragma region Get

   ID3D12Resource *GetResource() const { return buffer_.Get(); }
   size_t GetRTVIndex() { return rtvHandleIndex_; }
   size_t GetSRVIndex() { return srvHandleIndex_; }
   size_t GetDSVIndex() { return dsvHandleIndex_; }

#pragma endregion

   void CreateBuffer(D3D12_HEAP_PROPERTIES heapParam, D3D12_HEAP_FLAGS HeapFlags, D3D12_RESOURCE_DESC pDesc, D3D12_RESOURCE_STATES state, D3D12_CLEAR_VALUE value);

 private:
   size_t instanceNum_ = 1;

   bool isRtvUse_ = false;
   size_t rtvHandleIndex_ = 0;

   bool isSrvUse_ = false;
   size_t srvHandleIndex_ = 0;

   bool isDsvUse_ = false;
   size_t dsvHandleIndex_ = 0;

   const T *param_ptr_ = nullptr;
   ComPtr<ID3D12Resource> buffer_ = nullptr;

   DXDescripterManager *descripterManager_ = nullptr;
   ID3D12Device5 *device_;
};

template <typename T> inline void DXBufferResource<T>::Init() { descripterManager_ = DXDescripterManager::GetInstance(); }

template <typename T> inline void DXBufferResource<T>::Update() {}

template <typename T> inline void DXBufferResource<T>::CreateBuffer(D3D12_HEAP_PROPERTIES heapParam, D3D12_HEAP_FLAGS HeapFlags, D3D12_RESOURCE_DESC pDesc, D3D12_RESOURCE_STATES state, D3D12_CLEAR_VALUE value) {

   HRESULT hr = device_->CreateCommittedResource(&heapParam, HeapFlags, &pDesc, state, &value, IID_PPV_ARGS(&buffer_));
   assert(SUCCEEDED(hr));
}

} // namespace DX
} // namespace Base
} // namespace CLEYERA