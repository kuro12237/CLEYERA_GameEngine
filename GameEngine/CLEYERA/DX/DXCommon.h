#pragma once
#include "DXComponent.h"

#include "../SystemLogManager/SystemLogManager.h"
#include "DXAdapter/DXAdapter.h"
#include "DXDevice/DXDevice.h"
#include "DXFactory/DXFactory.h"

namespace CLEYERA::Base::DX {

class DXCommon : public DXComponent {
public:
  DXCommon(const std::string &name) : DXComponent(name) {};
  ~DXCommon() {};

  void Create() override;
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

  std::shared_ptr<DXFactory> factory_ = nullptr;
  std::shared_ptr<DXAdapter> adapter_ = nullptr;
  std::shared_ptr<DXDevice> device_ = nullptr;
};

} // namespace CLEYERA::Base::DX