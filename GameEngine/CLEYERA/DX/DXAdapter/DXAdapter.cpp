#include "DXAdapter.h"

using namespace CLEYERA::Base::DX;

void DXAdapter::Create()
{
  IDXGIFactory7 *factory = DX::DXManager::GetInstance();
  for (UINT i = 0; factory_->EnumAdapterByGpuPreference(
                       i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                       IID_PPV_ARGS(&adapter_)) != DXGI_ERROR_NOT_FOUND;
       i++) {
    DXGI_ADAPTER_DESC3 adapterDesc{};
    HRESULT hr = adapter_->GetDesc3(&adapterDesc);
    assert(SUCCEEDED(hr));

    if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
        break;
    }
    adapter_ = nullptr;
  }
  assert(adapter_ != nullptr);

  DX::DXManager::GetInstance()
  NotifyObserversCreateComp();
}