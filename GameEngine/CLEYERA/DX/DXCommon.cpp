#include "DXCommon.h"
#include "DXManager.h"

using namespace CLEYERA::Base::DX;

void DXCommon::Create() {

  dxManager_ = DXManager::GetInstance();

  factory_ = std::make_shared<DXFactory>(VAR_NAME(DXFactory));
  componentList_.push_back(factory_);
  adapter_ = std::make_shared<DXAdapter>(VAR_NAME(DXAdapter));
  componentList_.push_back(adapter_);
  device_ = std::make_shared<DXDevice>(VAR_NAME(DXDevice));
  componentList_.push_back(device_);

  for (auto &obj : componentList_) {
    obj.lock()->AddObserver(logManager_);
  }

  factory_->Create();
  dxManager_->SetFactory(factory_);

  adapter_->Create();
  dxManager_->SetAdapter(adapter_);

  device_->Create();
  dxManager_->SetDevice(device_);
}

void CLEYERA::Base::DX::DXCommon::Finalize() {

  device_.reset();
  adapter_.reset();
  factory_.reset();
}
