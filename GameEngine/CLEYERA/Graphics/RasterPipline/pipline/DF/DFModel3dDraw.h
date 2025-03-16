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

   void SettingRootParam() override;
   virtual void SettingSampler() override;
   virtual void SettingInput() override;

 private:
};

} // namespace system
} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA