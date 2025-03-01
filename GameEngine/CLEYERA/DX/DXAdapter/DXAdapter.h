#pragma once
#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

/// <summary>
/// DXAdapetrクラス
/// </summary>
class DXAdapter : public DXComponent {
public:
  DXAdapter() = default;
  ~DXAdapter() = default;

  void Create() override;

private:
  ComPtr<IDXGIAdapter4> adapter_ = nullptr;
};
} // namespace CLEYERA::Base::DX