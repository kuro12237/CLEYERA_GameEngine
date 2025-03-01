#pragma once
#include "DXComponent.h"

#include "DXAdapter/DXAdapter.h"
#include "DXDevice/DXDevice.h"
#include "DXFactory/DXFactory.h"

namespace CLEYERA::Base::DX {

class DXCommon : public DXComponent {
public:
  DXCommon() {};
  ~DXCommon() {};

  void Create() override;
#pragma region Get

  std::shared_ptr<DXFactory> GetFactory() { return factory_; }
  std::shared_ptr<DXAdapter> GetAdapter() { return adapter_; }
  std::shared_ptr<DXDevice> GetDevice() { return device_; }
   
#pragma endregion


private:
  std::shared_ptr<DXFactory> factory_ = nullptr;
  std::shared_ptr<DXAdapter> adapter_ = nullptr;
  std::shared_ptr<DXDevice> device_ = nullptr;
};

} // namespace CLEYERA::Base::DX