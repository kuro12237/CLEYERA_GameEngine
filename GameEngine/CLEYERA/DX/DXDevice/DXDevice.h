#pragma once
#include "../SystemLogComponent.h"

namespace CLEYERA::Base::DX {

using Microsoft::WRL::ComPtr;

/// <summary>
/// DirectXDevice
/// </summary>
class DXDevice : public DXComponent {
public:
  bool Create() override;

private:
  ComPtr<ID3D12Device5> device_ = nullptr;
};
} // namespace CLEYERA::Base::DX