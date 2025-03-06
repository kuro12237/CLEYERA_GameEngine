#include "DXDescripterManager.h"
#include"DXRTVDescripter.h"

size_t CLEYERA::Base::DX::DXDescripterManager::RTVAddPtr(ID3D12Resource *buf, D3D12_RENDER_TARGET_VIEW_DESC desc) { return rtvDescripter_.lock()->AddPtr(buf, desc); }

void CLEYERA::Base::DX::DXDescripterManager::RTVRelease(size_t index) { rtvDescripter_.lock()->Release(index); }
