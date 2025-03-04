#pragma once
#include "DXComponent.h"

#include "../SystemLogManager/SystemLogManager.h"
#include"DXDebugLayer/DXDebugLayer.h"
#include"DXInfoQueue/DXInfoQueue.h"
#include "DXAdapter/DXAdapter.h"
#include "DXDevice/DXDevice.h"
#include "DXFactory/DXFactory.h"
#include"DXCommand/DXCommandAllocator.h"
#include"DXCommand/DXCommandList.h"
#include"DXCommand/DXCommandQueue.h"
#include"DXSwapChain/DXSwapChain.h"

#include"DXDescripter/DXRTVDescripter.h"

namespace CLEYERA::Base::DX {

class DXCommon : public DXComponent {
public:
  DXCommon(const std::string &name) : DXComponent(name) {};
  ~DXCommon() {};

  void Create() override;

  void Finalize();

#pragma region Get

  std::shared_ptr<DXFactory> GetFactory() { return factory_; }
  std::shared_ptr<DXAdapter> GetAdapter() { return adapter_; }
  std::shared_ptr<DXDevice> GetDevice() { return device_; }

#pragma endregion

#pragma region Set

  void SetLogManager(const std::shared_ptr<LogManager::SystemLogManager> &l) {
    logManager_ = l;
  }
#pragma endregion

private:
  std::weak_ptr<LogManager::SystemLogManager> logManager_;

  std::list<std::weak_ptr<DXComponent>> componentList_;

  std::shared_ptr<DXRTVDescripter> rtvDescripter_ = nullptr;
  std::shared_ptr<DXSwapChain> swapChain_ = nullptr;

  std::shared_ptr<DXCommandList> commandList_ = nullptr;
  std::shared_ptr<DXCommandAllocator> commandAllcator_ = nullptr;
  std::shared_ptr<DXCommandQueue> commandQueue_ = nullptr;
  std::shared_ptr<DXFactory> factory_ = nullptr;
  std::shared_ptr<DXAdapter> adapter_ = nullptr;
  std::shared_ptr<DXDevice> device_ = nullptr;

#ifdef _DEBUG

  std::shared_ptr<DXInfoQueue> infoQueue_ = nullptr;
  std::shared_ptr<DXDebugLayer> debugLayer_ = nullptr;
#endif // _DEBUG

};

} // namespace CLEYERA::Base::DX