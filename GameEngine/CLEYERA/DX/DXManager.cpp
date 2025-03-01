#include "DXManager.h"

void CLEYERA::Base::DX::DXManager::SetPtr(DXCommon *common)
{
  device_ = common->GetDevice();
  adapter_ = common->GetAdapter();
  factory_ = common->GetFactory();
}