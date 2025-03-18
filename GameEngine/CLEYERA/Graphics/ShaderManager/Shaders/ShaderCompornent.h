#pragma once
#include "../../../pch/Pch.h"
#include "../../RasterPipline/RasterEnum.h"
#include "../ShaderEnum.h"

#include "../../../SystemLogManager/SystemLogManager.h"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

namespace system {

class ShaderCommon;

class ShaderCompornent {
 public:
   ShaderCompornent() {};
   virtual ~ShaderCompornent() {};

   void Init(ShaderCommon *manager);

   ComPtr<IDxcBlob> CompilerShaderFanc(const std::wstring &filePath, const wchar_t *profile);

   void ShaderFilePath(Shader::ShaderMode mode, std::string name) { shaderFilePath_[name] = mode; }

   IDxcBlob *GetShader(Shader::ShaderMode mode) { return shaders_[mode].Get(); }

   void SetRasterMode(RasterPipline_Mode mode) { rasterMode_ = mode; }

 private:
   RasterPipline_Mode rasterMode_;

   IDxcIncludeHandler *includeHandler_ = nullptr;
   IDxcUtils *utils_ = nullptr;
   IDxcCompiler3 *compiler_ = nullptr;

   std::map<std::string, Shader::ShaderMode> shaderFilePath_;
   std::map<CLEYERA::Graphics::Shader::ShaderMode, ComPtr<IDxcBlob>> shaders_;
};
} // namespace system

} // namespace Shader
} // namespace Graphics
} // namespace CLEYERA