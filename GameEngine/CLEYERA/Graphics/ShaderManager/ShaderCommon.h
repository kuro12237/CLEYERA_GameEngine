#pragma once
#include "Shaders/ShaderCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

namespace system {

struct ShaderTag {
   std::string PiplineName;
   std::string PS;           // Pixel Shader
   std::string VS;           // Vertex Shader
   std::string DS;           // Domain Shader
   std::string HS;           // Hull Shader
   std::string GS;           // Geometry Shader
   std::string CS;           // Compute Shader
   std::string RAYGEN;       // Ray Generation Shader
   std::string MISS;         // Miss Shader
   std::string CLOSEST_HIT;  // Closest Hit Shader
   std::string ANY_HIT;      // Any Hit Shader
   std::string INTERSECTION; // Intersection Shader

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShaderTag,PiplineName, PS, VS, DS, HS, GS, CS, RAYGEN, MISS, CLOSEST_HIT, ANY_HIT, INTERSECTION)
};

class ShaderCommon {
 public:
   ShaderCommon() {};
   ~ShaderCommon() {};

   void Init();

   IDxcBlob *GetBlob(Graphics::RasterPipline_Mode pipMode, Shader::ShaderMode shaderMode) { return compornemts_[pipMode]->GetShader(shaderMode); };

   IDxcIncludeHandler *GetIncludeHandler() { return includeHandler_.Get(); }
   IDxcUtils *GetUtils() { return utils_.Get(); }
   IDxcCompiler3 *getCompiler() { return compiler_.Get(); }

   ShaderTag GetFIleName(RasterPipline_Mode mode) { return fileNames_[mode]; }
 private:
   void LoadJson();

   void SetShaderName(const ShaderTag &tag);

   ShaderMode TagHandler(std::string tag);

   RasterPipline_Mode RasterHandler(std::string tag);

   std::string filePath_ = "Resources/Shaders/LoadFilesName.json";

   ComPtr<IDxcIncludeHandler> includeHandler_ = nullptr;
   ComPtr<IDxcUtils> utils_ = nullptr;
   ComPtr<IDxcCompiler3> compiler_ = nullptr;

   std::map<RasterPipline_Mode, ShaderTag> fileNames_;

   std::map<RasterPipline_Mode, std::shared_ptr<ShaderCompornent>> compornemts_;
};

} // namespace system
} // namespace Shader
} // namespace Graphics
} // namespace CLEYERA