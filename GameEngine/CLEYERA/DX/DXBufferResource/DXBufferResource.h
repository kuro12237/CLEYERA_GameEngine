#pragma once
#include "../../pch/Pch.h"

#include "../DXCommand/DXCommandManager.h"
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

   void Init(size_t instanceNum = 1);

   void Update();

   void Map();

   void Map(void **p);

   void UnMap();

   void ComputeRootDescripterTable(UINT num);

   void RegisterRTV(D3D12_RENDER_TARGET_VIEW_DESC desc) {
      rtvHandleIndex_ = descripterManager_->RTVAddPtr(buffer_.Get(), desc);
      isRtvUse_ = true;
   }

   void RegisterSRV(D3D12_SHADER_RESOURCE_VIEW_DESC desc) {
      srvHandleIndex_ = descripterManager_->SRVAddCreatePtr(buffer_.Get(), desc);
      isSrvUse_ = true;
   }

   void RegisterUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC desc) {
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
   void SetParam(std::vector<T> param);

   void SetResource(ComPtr<ID3D12Resource> resource) { buffer_ = std::move(resource); };
#pragma endregion

#pragma region Get

   ID3D12Resource *GetResource() const { return buffer_.Get(); }
   size_t GetRTVIndex() { return rtvHandleIndex_; }
   size_t GetSRVIndex() { return srvHandleIndex_; }
   size_t GetDSVIndex() { return dsvHandleIndex_; }

#pragma endregion

   void CreateBuffer(D3D12_HEAP_PROPERTIES heapParam, D3D12_HEAP_FLAGS HeapFlags, D3D12_RESOURCE_DESC pDesc, D3D12_RESOURCE_STATES state, const D3D12_CLEAR_VALUE *value);
   void DFCreateBuffer(size_t size, D3D12_RESOURCE_FLAGS flags, D3D12_RESOURCE_STATES initialState, D3D12_HEAP_TYPE heapType);
   void CreateTexture2d(Math::Vector::Vec2 size, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flags, D3D12_RESOURCE_STATES initialState, D3D12_HEAP_TYPE heapType);

   void WriteMemory(const void *pData, size_t dataSize);

 private:
   size_t instanceNum_ = 1;

   bool isRtvUse_ = false;
   size_t rtvHandleIndex_ = 0;

   bool isSrvUse_ = false;
   size_t srvHandleIndex_ = 0;

   bool isDsvUse_ = false;
   size_t dsvHandleIndex_ = 0;

   T *param_ptr_ = nullptr;
   ComPtr<ID3D12Resource> buffer_ = nullptr;

   DXDescripterManager *descripterManager_ = nullptr;
   ID3D12Device5 *device_;
};

template <typename T> inline void DXBufferResource<T>::Init(size_t instanceNum) {
   instanceNum_ = instanceNum;
   descripterManager_ = DXDescripterManager::GetInstance();
}

template <typename T> inline void DXBufferResource<T>::Update() {}

template <typename T> inline void DXBufferResource<T>::Map() { buffer_->Map(0, nullptr, reinterpret_cast<void **>(&this->param_ptr_)); }

template <typename T> inline void DXBufferResource<T>::Map(void **p) { buffer_->Map(0, nullptr, p); }

template <typename T> inline void DXBufferResource<T>::UnMap() {}

template <typename T> inline void DXBufferResource<T>::ComputeRootDescripterTable(UINT num) {

   
   auto list = Base::DX::DXCommandManager::GetInstace();
   D3D12_GPU_DESCRIPTOR_HANDLE handle = descripterManager_->GetSRVGPUHandle(srvHandleIndex_);
   list->ComputeDescripterTable(num, handle);
}

template <typename T> inline void DXBufferResource<T>::SetParam(std::vector<T> param) {

   for (size_t i = 0; i < this->instanceNum_; i++) {

      param_ptr_[i] = param[i];
   }
}

template <typename T> inline void DXBufferResource<T>::CreateBuffer(D3D12_HEAP_PROPERTIES heapParam, D3D12_HEAP_FLAGS HeapFlags, D3D12_RESOURCE_DESC pDesc, D3D12_RESOURCE_STATES state, const D3D12_CLEAR_VALUE *value) {

   HRESULT hr = device_->CreateCommittedResource(&heapParam, HeapFlags, &pDesc, state, value, IID_PPV_ARGS(&buffer_));
   assert(SUCCEEDED(hr));
}

template <typename T> inline void DXBufferResource<T>::DFCreateBuffer(size_t size, D3D12_RESOURCE_FLAGS flags, D3D12_RESOURCE_STATES initialState, D3D12_HEAP_TYPE heapType) {

   D3D12_HEAP_PROPERTIES heapProps{};
   if (heapType == D3D12_HEAP_TYPE_DEFAULT) {
      heapProps = D3D12_HEAP_PROPERTIES{D3D12_HEAP_TYPE_DEFAULT, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};
   }
   if (heapType == D3D12_HEAP_TYPE_UPLOAD) {
      heapProps = D3D12_HEAP_PROPERTIES{D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};
   }

   HRESULT hr;
   D3D12_RESOURCE_DESC resDesc{};
   resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
   resDesc.Alignment = 0;
   resDesc.Width = size;

   resDesc.Height = 1;
   resDesc.DepthOrArraySize = 1;
   resDesc.MipLevels = 1;
   resDesc.Format = DXGI_FORMAT_UNKNOWN;
   resDesc.SampleDesc = {1, 0};
   resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
   resDesc.Flags = flags;

   hr = device_->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc, initialState, nullptr, IID_PPV_ARGS(buffer_.ReleaseAndGetAddressOf()));
   assert(SUCCEEDED(hr));
}

template <typename T> inline void DXBufferResource<T>::CreateTexture2d(Math::Vector::Vec2 size, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flags, D3D12_RESOURCE_STATES initialState, D3D12_HEAP_TYPE heapType) {

   D3D12_HEAP_PROPERTIES heapProps{};
   if (heapType == D3D12_HEAP_TYPE_DEFAULT) {
      heapProps = D3D12_HEAP_PROPERTIES{D3D12_HEAP_TYPE_DEFAULT, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};
   }
   if (heapType == D3D12_HEAP_TYPE_UPLOAD) {
      heapProps = D3D12_HEAP_PROPERTIES{D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};
   }
   HRESULT hr;
   D3D12_RESOURCE_DESC resDesc{};
   resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
   resDesc.Alignment = 0;
   resDesc.Width = static_cast<UINT>(size.x);
   resDesc.Height = static_cast<UINT>(size.y);
   resDesc.DepthOrArraySize = 1;
   resDesc.MipLevels = 1;
   resDesc.Format = format;
   resDesc.SampleDesc = {1, 0};
   resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
   resDesc.Flags = flags;

   hr = device_->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc, initialState, nullptr, IID_PPV_ARGS(&buffer_));
   assert(SUCCEEDED(hr));
}

template <typename T> inline void DXBufferResource<T>::WriteMemory(const void *pData, size_t dataSize) {

   if (buffer_ == nullptr) {
      assert(true);
      return;
   }
   void *mapped = nullptr;
   D3D12_RANGE range{0, dataSize};
   HRESULT hr = buffer_->Map(0, &range, &mapped);
   if (SUCCEEDED(hr)) {
      memcpy(mapped, pData, dataSize);
      buffer_->Unmap(0, &range);
   }
}

} // namespace DX
} // namespace Base
} // namespace CLEYERA