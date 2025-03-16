#pragma once
#include "pipline/RasterPiplineCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

/// <summary>
/// パイプラインの作成クラス
/// </summary>
class RasterPiplineCommon {
 public:
   RasterPiplineCommon() {};
   ~RasterPiplineCommon() {};

   void Init();

 private:

   std::map<Shader::ShaderMode, std::weak_ptr<RasterPiplineCompornent>> piplines_;
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA