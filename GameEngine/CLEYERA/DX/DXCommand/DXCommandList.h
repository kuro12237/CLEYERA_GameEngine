#pragma once
#include "../DXComponent.h"

namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

class DXCommandList : public DXComponent {
public:
  DXCommandList(const std::string &name) : DXComponent(name) {};
  ~DXCommandList() {};

  void Create() override;

  void End();

#pragma region Get
  ID3D12GraphicsCommandList *GetCommandList() { return commandlist_.Get(); }

#pragma endregion

private:
  ComPtr<ID3D12GraphicsCommandList> commandlist_;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA