#pragma once

#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

/// <summary>
/// DXAdapetrクラス
/// </summary>
class DXFactory : public DXComponent {
public:
  DXFactory() = default;
  ~DXFactory() = default;

  void Create() override;



private:
  ComPtr<IDXGIFactory7> factory_ = nullptr;
};
} // namespace CLEYERA::Base::DX