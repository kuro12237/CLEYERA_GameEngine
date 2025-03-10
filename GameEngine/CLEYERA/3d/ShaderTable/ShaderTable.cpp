#include "ShaderTable.h"

void ShaderTable::Init() {

   device_ = CLEYERA::Base::DX::DXManager::GetInstance()->GetDevice();

   shaderTable_ = std::make_unique<CLEYERA::Base::DX::DXBufferResource<int32_t>>();
   shaderTable_->SetDevice(device_);
   shaderTable_->Init();

   // 各シェーダーレコードは Shader Identifier を保持する.
   UINT recordSize = D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

   // グローバルのルートシグネチャ以外の情報を持たないのでレコードサイズはこれだけ.

   // あとはアライメント制約を保つようにする.
   recordSize = RoundUp(recordSize, D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT);

   // シェーダーテーブルのサイズを求める.
   UINT raygenSize = 1 * recordSize;   // 今1つの Ray Generation シェーダー.
   UINT missSize = 1 * recordSize;     // 今1つの Miss シェーダー.
   UINT hitGroupSize = 1 * recordSize; // 今1つの HitGroup を使用.

   // 各テーブルの開始位置にアライメント制約があるので調整する.
   auto tableAlign = D3D12_RAYTRACING_SHADER_TABLE_BYTE_ALIGNMENT;
   UINT raygenRegion = RoundUp(raygenSize, tableAlign);
   UINT missRegion = RoundUp(missSize, tableAlign);
   UINT hitgroupRegion = RoundUp(hitGroupSize, tableAlign);

   // シェーダーテーブル確保.
   auto tableSize = raygenRegion + missRegion + hitgroupRegion;
   shaderTable_->DFCreateBuffer(tableSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_HEAP_TYPE_UPLOAD);
   
   
   ComPtr<ID3D12StateObjectProperties> rtsoProps;
   stateObject_.As(&rtsoProps);

   // 各シェーダーレコードを書き込んでいく.
   void *mapped = nullptr;
   shaderTable_->Map(&mapped);

   uint8_t *pStart = static_cast<uint8_t *>(mapped);

   // RayGeneration 用のシェーダーレコードを書き込み.
   auto rgsStart = pStart;
   {
      uint8_t *p = rgsStart;
      auto id = rtsoProps->GetShaderIdentifier(L"mainRayGen");
      if (id == nullptr) {
         throw std::logic_error("Not found ShaderIdentifier");
      }
      memcpy(p, id, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
      p += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

      // ローカルルートシグネチャ使用時には他のデータを書き込む.
   }

   // Miss Shader 用のシェーダーレコードを書き込み.
   auto missStart = pStart + raygenRegion;
   {
      uint8_t *p = missStart;
      auto id = rtsoProps->GetShaderIdentifier(L"mainMS");
      if (id == nullptr) {
         throw std::logic_error("Not found ShaderIdentifier");
      }
      memcpy(p, id, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
      p += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

      // ローカルルートシグネチャ使用時には他のデータを書き込む.
   }

   const wchar_t *DefaultHitgroup = L"DefaultHitGroup";
   // Hit Group 用のシェーダーレコードを書き込み.
   auto hitgroupStart = pStart + raygenRegion + missRegion;
   {
      uint8_t *p = hitgroupStart;
      auto id = rtsoProps->GetShaderIdentifier(DefaultHitgroup);
      if (id == nullptr) {
         throw std::logic_error("Not found ShaderIdentifier");
      }
      memcpy(p, id, D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES);
      p += D3D12_SHADER_IDENTIFIER_SIZE_IN_BYTES;

      // ローカルルートシグネチャ使用時には他のデータを書き込む.
   }


   // DispatchRays のために情報をセットしておく.
   auto startAddress = shaderTable_->GetResource()->GetGPUVirtualAddress();

   auto &shaderRecordRG = dispatchRayDesc.RayGenerationShaderRecord;
   shaderRecordRG.StartAddress = startAddress;
   shaderRecordRG.SizeInBytes = raygenSize;
   startAddress += raygenRegion;

   auto &shaderRecordMS = dispatchRayDesc.MissShaderTable;
   shaderRecordMS.StartAddress = startAddress;
   shaderRecordMS.SizeInBytes = missSize;
   shaderRecordMS.StrideInBytes = recordSize;
   startAddress += missRegion;

   auto &shaderRecordHG = dispatchRayDesc.HitGroupTable;
   shaderRecordHG.StartAddress = startAddress;
   shaderRecordHG.SizeInBytes = hitGroupSize;
   shaderRecordHG.StrideInBytes = recordSize;
   startAddress += hitgroupRegion;

   dispatchRayDesc.Width = CLEYERA::Base::Win::WinApp::GetKWindowWidth();
   dispatchRayDesc.Height = CLEYERA::Base::Win::WinApp::GetKWindowHeight();
   dispatchRayDesc.Depth = 1;
}