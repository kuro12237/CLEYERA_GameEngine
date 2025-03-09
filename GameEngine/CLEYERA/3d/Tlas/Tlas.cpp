#include "Tlas.h"

void CLEYERA::Model3d::system::Tlas::Init() {

   ID3D12Device5 *device = Base::DX::DXManager::GetInstance()->GetDevice();

   D3D12_RAYTRACING_INSTANCE_DESC instanceDesc{};

   Math::Matrix::Mat3x4 mat;
   mat.Identity();

   memcpy(&instanceDesc.Transform, &mat, sizeof(Math::Matrix::Mat3x4));
   instanceDesc.InstanceID = 0;
   instanceDesc.InstanceMask = 0xFF;
   instanceDesc.InstanceContributionToHitGroupIndex = 0;
   instanceDesc.Flags = D3D12_RAYTRACING_INSTANCE_FLAG_NONE;
   instanceDesc.AccelerationStructure = blas_->GetGPUVirtualAddress();

   std::unique_ptr<CLEYERA::Base::DX::DXBufferResource<int32_t>> instanceDescBuf = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   auto dxManager = Base::DX::DXManager::GetInstance();

   instanceDescBuf->SetDevice(dxManager->GetDevice());

   instanceDescBuf->DFCreateBuffer(sizeof(instanceDesc), D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);
   instanceDescBuf->WriteMemory(&instanceDesc, sizeof(instanceDesc));

   D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC buildASDesc{};
   auto &inputs = buildASDesc.Inputs; // D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS
   inputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;
   inputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
   inputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
   inputs.NumDescs = 1;

   // 必要なメモリ量を求める.
   D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO tlasPrebuild{};
   device->GetRaytracingAccelerationStructurePrebuildInfo(&inputs, &tlasPrebuild);

   // スクラッチバッファを確保.
   std::unique_ptr<Base::DX::DXBufferResource<int32_t>> tlasScratch = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   tlasScratch->SetDevice(device);
   tlasScratch->Init();

   tlasScratch->DFCreateBuffer(tlasPrebuild.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COMMON, D3D12_HEAP_TYPE_DEFAULT);

   // コマンドリストでリソースの状態を変更
   D3D12_RESOURCE_BARRIER barrier = {};
   barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
   barrier.Transition.pResource = tlasScratch->GetResource();
   barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
   barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
   barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
   ID3D12GraphicsCommandList4 *list = Base::DX::DXCommandManager::GetInstace()->GetCommandList();
   list->ResourceBarrier(1, &barrier);


     // BLAS 用メモリ(バッファ)を確保.
   buf_ = std::make_unique<Base::DX::DXBufferResource<int32_t>>();
   buf_->SetDevice(device);
   buf_->Init();
   buf_->DFCreateBuffer(tlasPrebuild.ResultDataMaxSizeInBytes, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, D3D12_HEAP_TYPE_DEFAULT);

   // Acceleration Structure 構築.
   buildASDesc.Inputs.InstanceDescs = instanceDescBuf->GetResource()->GetGPUVirtualAddress();
   buildASDesc.ScratchAccelerationStructureData = tlasScratch->GetResource()->GetGPUVirtualAddress();
   buildASDesc.DestAccelerationStructureData = buf_->GetResource()->GetGPUVirtualAddress();

   // コマンドリストに積んで実行する.

   list->BuildRaytracingAccelerationStructure(&buildASDesc, 0, nullptr);

   std::unique_ptr<Base::DX::DXBarrier> barrier_ = std::make_unique<Base::DX::DXBarrier>();

   barrier_->Init();
   barrier_->SetBuffer(buf_->GetResource());
   barrier_->SetBarrierType(0, D3D12_RESOURCE_BARRIER_TYPE_UAV);
   barrier_->Barrier();

   
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
   srvDesc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
   srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
   srvDesc.RaytracingAccelerationStructure.Location = buf_->GetResource()->GetGPUVirtualAddress();
   buf_->RegisterSRV(srvDesc);

   auto commandManager = Base::DX::DXCommandManager::GetInstace();
   commandManager->CommandClose();
}