#pragma once
#include "../../../pch/Pch.h"
#include "../../RasterPipline/RasterEnum.h"
#include "../ShaderEnum.h"


namespace CLEYERA {

namespace Graphics {

namespace Shader {

class ShaderCompornent {
 public:
   ShaderCompornent() {};
   virtual ~ShaderCompornent() {};

   void Init();

 private:

	 std::map<CLEYERA::Graphics::Shader::ShaderMode,std::string> shaderName;


};


}}}