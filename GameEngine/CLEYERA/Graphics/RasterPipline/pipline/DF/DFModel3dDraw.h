#pragma once
#include "../RasterPiplineCompornent.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

namespace system {

class DFModel3dDraw : public RasterPiplineCompornent {
 public:
   DFModel3dDraw() {};
   ~DFModel3dDraw() {};

   void SettingShader() override;
   void SettingRootParam() override;
   void SettingSampler() override;
   void SettingInput() override;

 private:
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA