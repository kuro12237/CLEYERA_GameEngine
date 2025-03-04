#pragma once
#include "../DXBufferResource/DXBufferResource.h"
#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

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
  ID3D12Resource *GetSwapChainResource(size_t index) {
    return resources_[index]->GetResource();
  }
  size_t GetSwapChainCount() { return swapChainCount_; }

#pragma endregion

private:
  /// <summary>
  /// swapChain
  /// </summary>
  void CreateResources();

  static const size_t swapChainCount_ = 2;

  DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
  ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

  std::array<std::unique_ptr<DXBufferResource<uint32_t>>, swapChainCount_>
      resources_;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA