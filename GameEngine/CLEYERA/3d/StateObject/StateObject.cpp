#include "StateObject.h"

void CLEYERA::Model3d::system::PiplineStateObject::Init() {

    device_ = Base::DX::DXManager::GetInstance()->GetDevice();

   std::vector<D3D12_STATE_SUBOBJECT> subobjects;
   subobjects.reserve(9);

   ///シェーダー読み込み
   std::vector<char> shader= ShaderManager::CompileShader("Resources/Shaders/triangleShader.hlsl");


   D3D12_EXPORT_DESC exports[] = {
       {L"mainRayGen", nullptr, D3D12_EXPORT_FLAG_NONE},
       {L"mainMS", nullptr, D3D12_EXPORT_FLAG_NONE},
       {L"mainCHS", nullptr, D3D12_EXPORT_FLAG_NONE},
   };

   D3D12_DXIL_LIBRARY_DESC dxilLibDesc{};
   dxilLibDesc.DXILLibrary = D3D12_SHADER_BYTECODE{shader.data(), shader.size()};
   dxilLibDesc.NumExports = _countof(exports);
   dxilLibDesc.pExports = exports;

   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY, &dxilLibDesc});

   // ヒットグループの設定
   D3D12_HIT_GROUP_DESC hitGroupDesc{};
   hitGroupDesc.Type = D3D12_HIT_GROUP_TYPE_TRIANGLES;
   hitGroupDesc.ClosestHitShaderImport = L"mainCHS";
   hitGroupDesc.HitGroupExport = CLEYERA::Graphics::HitGroup::ALL;
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP, &hitGroupDesc});

   // グローバルルートシグネチャ設定
   D3D12_GLOBAL_ROOT_SIGNATURE rootSignatureGlobal{};
   rootSignatureGlobal.pGlobalRootSignature = globalRootSignature_;
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE, &rootSignatureGlobal});

  
    // ローカル Root Signature 設定
   //closedHit
   D3D12_LOCAL_ROOT_SIGNATURE rootSignatureLocal{};
   rootSignatureLocal.pLocalRootSignature = this->closetHitRootSignature_;
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE, &rootSignatureLocal});

   const wchar_t *symbols[] = {CLEYERA::Graphics::HitGroup::ALL};
   D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION assoc{};
   assoc.NumExports = _countof(symbols);
   assoc.pExports = symbols;
   assoc.pSubobjectToAssociate = &subobjects.back();
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION, &assoc});

   ///RayGen
   D3D12_LOCAL_ROOT_SIGNATURE lrsRayGen{};
   lrsRayGen.pLocalRootSignature = this->rayGenRootSignature_;
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE, &lrsRayGen});
   const wchar_t *symbolsRGS[] = {L"mainRayGen"};
   D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION assoc2{};
   assoc2.NumExports = _countof(symbolsRGS);
   assoc2.pExports = symbolsRGS;
   assoc2.pSubobjectToAssociate = &subobjects.back();
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION, &assoc2});


   // シェーダー設定
   D3D12_RAYTRACING_SHADER_CONFIG shaderConfig{};
   shaderConfig.MaxPayloadSizeInBytes = sizeof(Math::Vector::Vec3);
   shaderConfig.MaxAttributeSizeInBytes = sizeof(Math::Vector::Vec2);
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_SHADER_CONFIG, &shaderConfig});

   // パイプライン設定
   D3D12_RAYTRACING_PIPELINE_CONFIG pipelineConfig{};
   pipelineConfig.MaxTraceRecursionDepth = 1;
   subobjects.emplace_back(D3D12_STATE_SUBOBJECT{D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG, &pipelineConfig});

   // ステートオブジェクトの生成
   D3D12_STATE_OBJECT_DESC stateObjDesc{};
   stateObjDesc.Type = D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE;
   stateObjDesc.NumSubobjects = UINT(subobjects.size());
   stateObjDesc.pSubobjects = subobjects.data();

   HRESULT hr = device_->CreateStateObject(&stateObjDesc, IID_PPV_ARGS(stateObject_.ReleaseAndGetAddressOf()));
   assert(SUCCEEDED(hr));
 
}