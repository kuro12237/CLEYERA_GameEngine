#pragma once

#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

class DXCommandAllocator : public DXComponent {
public:
  DXCommandAllocator(const std::string &name) : DXComponent(name) {};
  ~DXCommandAllocator() {};

  void Create() override;

#pragma region Get
  ID3D12CommandAllocator *GetCommandAllocator() {
    return commandAllocator_.Get();
  }

#pragma endregion

private:
  ComPtr<ID3D12CommandAllocator> commandAllocator_;
};

} // namespace CLEYERA::Base::DX