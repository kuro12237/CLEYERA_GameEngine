#include "DXFactory.h"

using namespace CLEYERA::Base::DX;

void DXFactory::Create() {

  HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory_));
  assert(SUCCEEDED(hr));
}