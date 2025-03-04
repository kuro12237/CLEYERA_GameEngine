#pragma once
#include "../DXBufferResource/DXBufferResource.h"
#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

/// <summary>
///
/// </summary>
class DXSwapChain : public DXComponent {
public:
  DXSwapChain(const std::string &name) : DXComponent(name) {};
  ~DXSwapChain() = default;

  void Create() override;

  void Begin();

#pragma region Get

  IDXGISwapChain4 *GetSwapChain() { return swapChain_.Get(); }

#pragma endregion

private:
  /// <summary>
  /// swapChain
  /// </summary>
  void CreateResources();

  static const size_t swapChainCount_ = 2;

  DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
  ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

  std::array<std::unique_ptr<DXBufferResource<uint32_t>>,swapChainCount_> resources_;
};
} // namespace CLEYERA::Base::DX