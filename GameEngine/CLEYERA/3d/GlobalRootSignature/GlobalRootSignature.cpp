#include "GlobalRootSignature.h"

void CLEYERA::Model3d::system::GlobalRootSignature::Init() {

   ID3D12Device5 *device = Base::DX::DXManager::GetInstance()->GetDevice();

   std::array<D3D12_ROOT_PARAMETER, 3> rootParams{};

   // TLAS を t0 レジスタに割り当てて使用する設定.
   D3D12_DESCRIPTOR_RANGE descRangeTLAS{};
   descRangeTLAS.BaseShaderRegister = 0;
   descRangeTLAS.NumDescriptors = 1;
   descRangeTLAS.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;

   // 出力バッファ(UAV) を u0 レジスタに割り当てて使用する設定.
   D3D12_DESCRIPTOR_RANGE descRangeOutput{};
   descRangeOutput.BaseShaderRegister = 0;
   descRangeOutput.NumDescriptors = 1;
   descRangeOutput.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;

   rootParams[0] = D3D12_ROOT_PARAMETER{};
   rootParams[1] = D3D12_ROOT_PARAMETER{};
   rootParams[2] = D3D12_ROOT_PARAMETER{};

   rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[0].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[0].DescriptorTable.pDescriptorRanges = &descRangeTLAS;

   rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
   rootParams[1].DescriptorTable.NumDescriptorRanges = 1;
   rootParams[1].DescriptorTable.pDescriptorRanges = &descRangeOutput;

   rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
   rootParams[2].Descriptor.ShaderRegister = 0;
   rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

   D3D12_ROOT_SIGNATURE_DESC rootSigDesc{};
   rootSigDesc.NumParameters = UINT(rootParams.size());
   rootSigDesc.pParameters = rootParams.data();

   HRESULT hr;
   Microsoft::WRL::ComPtr<ID3DBlob> blob, errBlob;
   hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &errBlob);
   assert(SUCCEEDED(hr));

   hr = device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(rootSignature_.ReleaseAndGetAddressOf()));
   assert(SUCCEEDED(hr));
}

void CLEYERA::Model3d::system::GlobalRootSignature::Render() {

   auto list = CLEYERA::Base::DX::DXCommandManager::GetInstace()->GetCommandList();
   list->SetComputeRootSignature(rootSignature_.Get());
}
