#pragma once
#include "../../DX/DXManager.h"
#include "../../WIn/WinApp.h"
#include "../../pch/Pch.h"

class ShaderTable {
 public:
   ShaderTable() {};
   ~ShaderTable() {};

   void Init();

   void SetStateObj(ComPtr<ID3D12StateObject> obj) { stateObject_ = obj; }

   D3D12_DISPATCH_RAYS_DESC GetDispatchRayDesc() { return dispatchRayDesc; }

 private:
   UINT RoundUp(size_t size, UINT align) { return UINT(size + align - 1) & ~(align - 1); }

   D3D12_DISPATCH_RAYS_DESC dispatchRayDesc;
   ID3D12Device5 *device_ = nullptr;
   ComPtr<ID3D12StateObject> stateObject_ = nullptr;

   std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<int32_t>> shaderTable_ = nullptr;
};
