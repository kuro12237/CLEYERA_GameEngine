#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXRTVDescripter : public DXDescripterComponent {
public:
  DXRTVDescripter(const std::string &name) : DXDescripterComponent(name) {};
  ~DXRTVDescripter() {};

  void Create() override;

  void Begin();

  void End();

  void SetBackBufferIndex(const UINT &index) { backBufferIndex_ = &index; }

private:
  D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};
  std::weak_ptr<DXSwapChain> swapChain_;

  const UINT *backBufferIndex_ = nullptr;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA