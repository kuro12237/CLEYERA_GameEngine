#pragma once
#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

/// <summary>
/// DXAdapetrクラス
/// </summary>
class DXFactory : public DXComponent {
public:
  DXFactory(const std::string &name) : DXComponent(name) {};
  ~DXFactory() = default;

  void Create() override;

#pragma region Get

  IDXGIFactory7 *GetFactory() { return factory_.Get(); }
#pragma endregion

private:
  ComPtr<IDXGIFactory7> factory_ = nullptr;
};
} // namespace CLEYERA::Base::DX