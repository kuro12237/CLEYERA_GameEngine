#pragma once

#include "../DXComponent.h"

namespace CLEYERA::Base::DX {
using Microsoft::WRL::ComPtr;

class DXCommandQueue : public DXComponent {
public:
  DXCommandQueue(const std::string &name) : DXComponent(name) {};
  ~DXCommandQueue() {};

  void Create() override;

#pragma region Get
  ID3D12CommandQueue *GetCommandQueue() { return commandQueue_.Get(); }

#pragma endregion

private:
  D3D12_COMMAND_QUEUE_DESC queueDesc{};
  ComPtr<ID3D12CommandQueue> commandQueue_;
};

} // namespace CLEYERA::Base::DX