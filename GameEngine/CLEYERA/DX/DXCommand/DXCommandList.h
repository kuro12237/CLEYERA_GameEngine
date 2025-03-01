#pragma once
#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

class DXCommandList : public DXComponent {
public:
  DXCommandList(const std::string &name) : DXComponent(name) {};
  ~DXCommandList() {};

  void Create() override;

#pragma region Get
  ID3D12CommandList *GetCommandList() { return commandlist_.Get(); }

#pragma endregion

private:
  ComPtr<ID3D12CommandList> commandlist_;
};

} // namespace CLEYERA::Base::DX