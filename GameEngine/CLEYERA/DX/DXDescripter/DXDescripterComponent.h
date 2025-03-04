#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

class DXDescripterComponent : public DXComponent {
public:
  DXDescripterComponent(const std::string &name) : DXComponent(name) {}
  virtual ~DXDescripterComponent() {};

  virtual void Create() = 0;

protected:
  void CreateDescripter(const D3D12_DESCRIPTOR_HEAP_TYPE &type,
                        bool shaderVisible);

  ComPtr<ID3D12DescriptorHeap> descripter_ = nullptr;

  int32_t descripterSize_ = 1024;

  D3D12_DESCRIPTOR_HEAP_TYPE type_;
  size_t handleIndex_ = 0;

  D3D12_CPU_DESCRIPTOR_HANDLE rtvCPUStartHandle_;
  D3D12_GPU_DESCRIPTOR_HANDLE rtvGPUStartHandle_;

  std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvCPUHandles_;
  std::vector<D3D12_GPU_DESCRIPTOR_HANDLE> rtvGPUHandles_;

private:
};

} // namespace CLEYERA::Base::DX