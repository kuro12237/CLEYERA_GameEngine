#pragma once
#include "../../pch/Pch.h"
#include "../RasterPipline/RasterEnum.h"
#include "ShaderEnum.h"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

class ShaderManager {
 public:
   ShaderManager() {};
   ~ShaderManager() {};

   void Init();

   static std::vector<char> CompileShader(const std::filesystem::path &hlslFilename);

   /// <summary>
   /// コンパイル関数
   /// </summary>
   IDxcBlob *CompilerShaderFanc(const std::wstring &filePath, const wchar_t *profile);

   IDxcBlob *GetShader(Graphics::RasterPipline_Mode pipMode, Shader::ShaderMode shaderMode) { return shaders_[pipMode]; }

 private:
   ComPtr<IDxcIncludeHandler> includeHandler_ = nullptr;
   ComPtr<IDxcUtils> utils_ = nullptr;
   ComPtr<IDxcCompiler3> compiler_ = nullptr;
   std::map<Graphics::RasterPipline_Mode,Graphics::Shader::ShaderMode> shaders_;
};
} // namespace Shader
} // namespace Graphics
} // namespace CLEYERA