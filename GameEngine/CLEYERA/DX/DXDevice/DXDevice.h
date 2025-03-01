#pragma once
#include "../DXComponent.h"

namespace CLEYERA::Base::DX {

using Microsoft::WRL::ComPtr;

/// <summary>
/// DirectXDevice
/// </summary>
class DXDevice : public DXComponent {
public:
  void Create() override;

#pragma region Get

  ID3D12Device5 *GetDevice() { return device_.Get(); }

#pragma endregion

private:
  ComPtr<ID3D12Device5> device_ = nullptr;
};
} // namespace CLEYERA::Base::DX