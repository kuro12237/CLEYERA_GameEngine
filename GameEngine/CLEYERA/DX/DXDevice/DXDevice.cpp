#include "DXDevice.h"

using namespace CLEYERA::Base::DX;


void DXDevice::Create() {
  D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0};

  const char *featureLevelStrings[] = {"12.2", "12.1", "12.0"};

  for (size_t i = 0; i < _countof(featureLevels); i++) {
    HRESULT hr =
        D3D12CreateDevice(nullptr, featureLevels[i], IID_PPV_ARGS(&device_));
    if (SUCCEEDED(hr)) {

      break;
    }
  }
}