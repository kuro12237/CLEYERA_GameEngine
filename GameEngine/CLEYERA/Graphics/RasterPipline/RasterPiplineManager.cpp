#include "RasterPiplineManager.h"

using namespace CLEYERA;

using namespace Graphics;

using namespace Raster;

RasterPiplineManager *CLEYERA::Graphics::Raster::RasterPiplineManager::GetInstance() {
   static RasterPiplineManager instance;
   return &instance;
}