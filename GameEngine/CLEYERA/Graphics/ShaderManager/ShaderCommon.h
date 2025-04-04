#pragma once
#include "../RasterPipline/RasterEnum.h"
#include "Shaders/ShaderCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Shader {

namespace system {

struct ShaderTag {
   std::string PiplineName = "NONE";
   std::string PS = "NONE";           // Pixel Shader
   std::string VS = "NONE";           // Vertex Shader
   std::string DS = "NONE";           // Domain Shader
   std::string HS = "NONE";           // Hull Shader
   std::string GS = "NONE";           // Geometry Shader
   std::string CS = "NONE";           // Compute Shader
   std::string RAYGEN = "NONE";       // Ray Generation Shader
   std::string MISS = "NONE";         // Miss Shader
   std::string CLOSEST_HIT = "NONE";  // Closest Hit Shader
   std::string ANY_HIT = "NONE";      // Any Hit Shader
   std::string INTERSECTION = "NONE"; // Intersection Shader

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShaderTag, PiplineName, PS, VS, DS, HS, GS, CS, RAYGEN, MISS, CLOSEST_HIT, ANY_HIT, INTERSECTION)
};

class ShaderCommon {
 public:
   ShaderCommon() {};
   ~ShaderCommon() {};

   void Init();

   IDxcBlob *GetBlob(CLEYERA::Graphics::RasterPipline_Mode pipMode, Shader::ShaderMode shaderMode) { return compornemts_[pipMode]->GetShader(shaderMode); };

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