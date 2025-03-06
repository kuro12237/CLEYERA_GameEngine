#include "DXDescripterManager.h"
#include "DXRTVDescripter.h"
#include"DXSRVDescripter.h"
#include"DXDSVDescripter.h"

size_t CLEYERA::Base::DX::DXDescripterManager::RTVAddPtr(ID3D12Resource *buf, D3D12_RENDER_TARGET_VIEW_DESC desc) { return rtvDescripter_.lock()->AddPtr(buf, desc); }

void CLEYERA::Base::DX::DXDescripterManager::RTVRelease(size_t index) {

   rtvDescripter_.lock()->Release(index);
}

size_t CLEYERA::Base::DX::DXDescripterManager::SRVAddPtr(ID3D12Resource *buf, D3D12_SHADER_RESOURCE_VIEW_DESC desc) {return  srvDescripter_.lock()->AddSRVPtr(buf, desc); }

size_t CLEYERA::Base::DX::DXDescripterManager::UAVAddPtr(ID3D12Resource *buf, D3D12_UNORDERED_ACCESS_VIEW_DESC desc) { return srvDescripter_.lock()->AddUAVPtr(buf, desc); }

void CLEYERA::Base::DX::DXDescripterManager::SRV_UAVReleace(size_t index) { srvDescripter_.lock()->Release(index); }

size_t CLEYERA::Base::DX::DXDescripterManager::DSVAddPtr(ID3D12Resource *buf, D3D12_DEPTH_STENCIL_VIEW_DESC desc) { return dsvDescripter_.lock()->AddPtr(buf,desc); }

void CLEYERA::Base::DX::DXDescripterManager::DSVRelease(size_t index) { dsvDescripter_.lock()->Release(index); }
