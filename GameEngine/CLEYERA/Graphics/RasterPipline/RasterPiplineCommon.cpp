#include "RasterPiplineCommon.h"

void CLEYERA::Graphics::Raster::system::RasterPiplineCommon::Init() {

   using mode = RasterPipline_Mode;

   piplines_[mode::DF_MODEL3d] = std::make_shared<system::DFModel3dDraw>();
   piplines_[mode::DF_MODEL3d]->SetMode(mode::DF_MODEL3d);

   for (auto obj : piplines_) {

      auto it = obj.second;

      it->Init();

      it->Create();
   }
}