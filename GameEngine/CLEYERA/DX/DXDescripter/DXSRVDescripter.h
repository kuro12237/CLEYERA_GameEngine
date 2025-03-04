#pragma once
#include "../DXComponent.h"
#include "DXDescripterComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXSRVDescripter : public DXDescripterComponent {
public:
  DXSRVDescripter(const std::string &name) : DXDescripterComponent(name) {};
  ~DXSRVDescripter() {};

  void Create() override;

  void Begin();

  void End();

 
private:
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA