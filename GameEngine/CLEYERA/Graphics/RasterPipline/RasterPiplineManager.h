#pragma once

namespace CLEYERA {

namespace Graphics {

namespace Raster {

/// <summary>
/// ラスタ描画のパイプライン管理クラス
/// </summary>
class RasterPiplineManager {
 public:
#pragma region Set

   void SetCommon();

#pragma endregion

 private:




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