#include "DXCommon.h"

using namespace CLEYERA::Base::DX;

void DXCommon::Create() {

  factory_ = std::make_shared<DXFactory>(VAR_NAME(DXFactory));
  componentList_.push_back(factory_);
  adapter_ = std::make_shared<DXAdapter>(VAR_NAME(DXAdapter));
  componentList_.push_back(adapter_);
  device_ = std::make_shared<DXDevice>(VAR_NAME(DXDevice));
  componentList_.push_back(device_);

  for ( auto & obj : componentList_ )
  {
    obj.lock()->AddObserver(logManager_);
  }

  factory_->Create();
  adapter_->Create();
  device_->Create();

}