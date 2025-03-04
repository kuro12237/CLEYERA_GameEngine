#pragma once
#include "../../pch/Pch.h"
#include "../DXDevice/DXDevice.h"

namespace CLEYERA::Base::DX {
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
  void SetDevice(const std::weak_ptr<DXDevice> &device) { device_ = device; }
  void SetParam(const T &param) { param_ptr_ = param; }
#pragma endregion

#pragma region Get

  ComPtr<ID3D12Resource> GetResource() { return buffer_; }

#pragma endregion

  void CreateBuffer(const D3D12_HEAP_PROPERTIES &heapParam,
                    D3D12_HEAP_FLAGS HeapFlags,
                    const D3D12_RESOURCE_DESC &pDesc,
                    D3D12_RESOURCE_STATES &state,
                    const D3D12_CLEAR_VALUE &value);

private:
  size_t instanceNum_ = 1;

  const T *param_ptr_ = nullptr;
  ComPtr<ID3D12Resource> buffer_ = nullptr;

  std::weak_ptr<DXDevice> device_;
};

template <typename T> inline void DXBufferResource<T>::Update() {}

template <typename T>
inline void DXBufferResource<T>::CreateBuffer(
    const D3D12_HEAP_PROPERTIES &heapParam, D3D12_HEAP_FLAGS HeapFlags,
    const D3D12_RESOURCE_DESC &pDesc, D3D12_RESOURCE_STATES &state,
    const D3D12_CLEAR_VALUE &value) {

  ComPtr<ID3D12Device5> device;
  HRESULT hr = device->CreateCommittedResource(
      heapParam, HeapFlags, pDesc, state, &value, IID_PPV_ARGS(&buffer_));
  assert(SUCCEEDED(hr));
}

} // namespace CLEYERA::Base::DX