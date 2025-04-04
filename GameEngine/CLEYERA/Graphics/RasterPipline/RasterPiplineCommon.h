#pragma once
#include "RasterEnum.h"
#include "pipline/RasterPiplineCompornent.h"

#include"../../SystemLogManager/ConvertString.h"

#include "pipline/DF/DFModel3dDraw.h"
#include"pipline/Line/Line3dDraw.h"

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

   template <typename T> std::weak_ptr<T> Getpipline(RasterPipline_Mode mode) { return dynamic_pointer_cast<T>(piplines_[mode]); }

 private:
   std::map<RasterPipline_Mode, std::shared_ptr<RasterPiplineCompornent>> piplines_;
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA