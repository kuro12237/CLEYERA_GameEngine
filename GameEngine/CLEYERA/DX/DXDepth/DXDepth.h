#pragma once
#include "../DXBufferResource/DXBufferResource.h"
#include "../../WIn/WinApp.h"

namespace CLEYERA {
namespace Base {
namespace DX {

class DXDepth {
public:
  DXDepth() {};
  ~DXDepth() {};

  void Init();

private:
  Win::WinApp *winApp_ = nullptr;
  std::unique_ptr<DXBufferResource<int32_t>> buf_ = nullptr;
};

} // namespace DX
} // namespace Base
} // namespace CLEYERA