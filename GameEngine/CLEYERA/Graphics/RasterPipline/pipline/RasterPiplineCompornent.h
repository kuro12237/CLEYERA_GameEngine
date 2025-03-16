#pragma once
#include "../../../DX/DXManager.h"
#include "../../../pch/Pch.h"
#include "../../ShaderManager/ShaderEnum.h"
#include "../RasterEnum.h"


namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class RasterPiplineCompornent {
 public:
   RasterPiplineCompornent() {};
   virtual ~RasterPiplineCompornent() {};

   void Init();

   void Create();

 private:
   void CreateRootSignature();
   void CreatePipline();

   ID3D12Device5 *device_ = nullptr;

   RasterPipline_Mode mode_;

 protected:
#pragma region Set
   void SetMode(RasterPipline_Mode mode) { mode_ = mode; }
#pragma endregion

   virtual void SettingShader() = 0;
   virtual void SettingRootParam() = 0;
   virtual void SettingSampler() = 0;
   virtual void SettingInput() = 0;
   virtual void SettingRaster();
   virtual void SettingDepth();
   virtual void SettingPipline();

   D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_{};
   std::vector<D3D12_ROOT_PARAMETER> rootParam_;
   std::vector<D3D12_DESCRIPTOR_RANGE> ganges_;
   std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplers_;
   std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDesc_;
   D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

   D3D12_RASTERIZER_DESC rasterizerDesc_{};
   D3D12_BLEND_DESC blendDesc_{};
   D3D12_DEPTH_STENCIL_DESC despthStencilDesc_;
   D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateDesc_{};

   DXGI_FORMAT depthFormat_ = DXGI_FORMAT_D24_UNORM_S8_UINT;

   std::map<CLEYERA::Graphics::Shader::ShaderMode, ComPtr<IDxcBlob>> shaders_;

   ComPtr<ID3D12PipelineState> GraphicsPipelineState_ = nullptr;
   ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA