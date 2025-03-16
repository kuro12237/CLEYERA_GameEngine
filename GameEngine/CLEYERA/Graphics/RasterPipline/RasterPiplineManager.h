#pragma once
#include "RasterPiplineCommon.h"

namespace CLEYERA {

namespace Graphics {

namespace Raster {

/// <summary>
/// ラスタ描画のパイプライン管理クラス
/// </summary>
class RasterPiplineManager {
 public:
   static RasterPiplineManager *GetInstance();

#pragma region Set
   void SetCommon(std::weak_ptr<Raster::system::RasterPiplineCommon> c) { common_ = c; };
#pragma endregion

   template <typename T> std::weak_ptr<T> GetPipline(Graphics::RasterPipline_Mode mode) { return common_.lock()->Getpipline<T>(mode); }

 private:
   std::weak_ptr<Raster::system::RasterPiplineCommon> common_;

#pragma region Single

   RasterPiplineManager() = default;
   ~RasterPiplineManager() = default;
   RasterPiplineManager(const RasterPiplineManager &) = delete;
   RasterPiplineManager &operator=(const RasterPiplineManager &) = delete;

#pragma endregion
};

} // namespace Raster
} // namespace Graphics
} // namespace CLEYERA