#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

class DXRTVDescripter : public DXDescripterComponent {
public:
  DXRTVDescripter(const std::string &name) : DXDescripterComponent(name) {};
  ~DXRTVDescripter() {};

  void Create() override;

private:

  D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};


};
} // namespace CLEYERA::Base::DX