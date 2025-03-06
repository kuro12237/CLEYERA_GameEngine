#pragma once
#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXDSVDescripter : public DXDescripterComponent {
public:
  DXDSVDescripter(const std::string &name) : DXDescripterComponent(name) {};
  ~DXDSVDescripter() {};

  void Create() override;

private:
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA