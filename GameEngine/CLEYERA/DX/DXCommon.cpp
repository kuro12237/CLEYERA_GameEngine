#include "DXCommon.h"

using namespace CLEYERA::Base::DX;

void DXCommon::Create() {

  factory_ = std::make_shared<DXFactory>();
  adapter_ = std::make_shared<DXAdapter>();
  device_ = std::make_shared<DXDevice>();

  factory_->Create();
  adapter_->Create();
  device_->Create();

}