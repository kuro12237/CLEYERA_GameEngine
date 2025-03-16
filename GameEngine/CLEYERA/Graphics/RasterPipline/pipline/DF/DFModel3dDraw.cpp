#include "DFModel3dDraw.h"

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingShader() {



}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingRootParam() {

   this->rootParam_.resize(2);

   // worldTransformvs
   rootParam_[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
   rootParam_[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
   rootParam_[0].Descriptor.ShaderRegister = 0;
   // view行列ps
   rootParam_[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
   rootParam_[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
   rootParam_[1].Descriptor.ShaderRegister = 1;
}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingSampler() {}

void CLEYERA::Graphics::Raster::system::DFModel3dDraw::SettingInput() {

	// Output
   inputElementDesc_.resize(2);
   inputElementDesc_[0].SemanticName = "POSITION";
   inputElementDesc_[0].SemanticIndex = 0;
   inputElementDesc_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
   inputElementDesc_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

   inputElementDesc_[1].SemanticName = "NORMAL";
   inputElementDesc_[1].SemanticIndex = 0;
   inputElementDesc_[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
   inputElementDesc_[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;


}
