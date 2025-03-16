#include "RasterPiplineCompornent.h"

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::Init() { device_ = Base::DX::DXManager::GetInstance()->GetDevice(); }

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::Create() {

   SettingRootParam();
   SettingSampler();
   this->CreateRootSignature();

   SettingInput();
   SettingRaster();
   SettingDepth();
   SettingPipline();
   
   this->CreatePipline();
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::CreateRootSignature() {
   descriptionRootSignature_.pStaticSamplers = staticSamplers_.data();
   descriptionRootSignature_.NumStaticSamplers = staticSamplers_.size();
   descriptionRootSignature_.pParameters = rootParam_.data();
   descriptionRootSignature_.NumParameters = rootParam_.size();

   ComPtr<ID3DBlob> signatureBlob = nullptr;
   ComPtr<ID3DBlob> errorBlob = nullptr;
   HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature_, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
   assert(SUCCEEDED(hr));

   hr = device_->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
   assert(SUCCEEDED(hr));
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::CreatePipline() {

   pipelineStateDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

   HRESULT hr = device_->CreateGraphicsPipelineState(&pipelineStateDesc_, IID_PPV_ARGS(&GraphicsPipelineState_));
   assert(SUCCEEDED(hr));
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingRaster() {

   rasterizerDesc_.CullMode = D3D12_CULL_MODE_BACK;
   rasterizerDesc_.FillMode = D3D12_FILL_MODE_SOLID;
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingDepth() {
   despthStencilDesc_.DepthEnable = true;
   despthStencilDesc_.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
   despthStencilDesc_.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
}

void CLEYERA::Graphics::Raster::system::RasterPiplineCompornent::SettingPipline() {

   auto vs = shaders_[Shader::ShaderMode::VS];
   if (vs.Get()) {
      pipelineStateDesc_.VS = {vs->GetBufferPointer(), vs->GetBufferSize()};
   }
   auto ps = shaders_[Shader::ShaderMode::PS];
   if (ps.Get()) {
      pipelineStateDesc_.PS = {ps->GetBufferPointer(), ps->GetBufferSize()};
   }
   auto ds = shaders_[Shader::ShaderMode::DS];
   if (ds.Get()) {
      pipelineStateDesc_.DS = {ds->GetBufferPointer(), ds->GetBufferSize()};
   }
   auto hs = shaders_[Shader::ShaderMode::HS];
   if (hs.Get()) {
      pipelineStateDesc_.HS = {hs->GetBufferPointer(), hs->GetBufferSize()};
   }
   auto gs = shaders_[Shader::ShaderMode::GS];
   if (gs.Get()) {
      pipelineStateDesc_.GS = {gs->GetBufferPointer(), gs->GetBufferSize()};
   }

   pipelineStateDesc_.pRootSignature = rootSignature_.Get();
   pipelineStateDesc_.InputLayout = inputLayoutDesc;
   pipelineStateDesc_.BlendState = blendDesc_;
   pipelineStateDesc_.RasterizerState = rasterizerDesc_;
   pipelineStateDesc_.DepthStencilState = despthStencilDesc_;
   pipelineStateDesc_.DSVFormat = depthFormat_;

   pipelineStateDesc_.NumRenderTargets = 1;
   pipelineStateDesc_.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

   pipelineStateDesc_.SampleDesc.Count = 1;
   pipelineStateDesc_.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
}
