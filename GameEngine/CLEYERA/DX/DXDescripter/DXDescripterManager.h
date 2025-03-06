#pragma once
#include"../../pch/Pch.h"

namespace CLEYERA {
namespace Base {
namespace DX {

enum class SRV_TYPE { SRV, UAV };

class DXRTVDescripter;

/// <summary>
/// でスクリプタ管理クラス
/// </summary>
class DXDescripterManager {
 public:
   static DXDescripterManager *GetInstance() {
      static DXDescripterManager instance;
      return &instance;
   }

   size_t RTVAddPtr(ID3D12Resource *buf, D3D12_RENDER_TARGET_VIEW_DESC desc);
   void RTVRelease(size_t index);

   size_t CreateSRV();

#pragma region Set
   void SetRTVDescripter(std::weak_ptr<DXRTVDescripter> rtv) { rtvDescripter_ = rtv; }
#pragma endregion

 private:
   std::weak_ptr<DXRTVDescripter> rtvDescripter_;

   DXDescripterManager() = default;
   ~DXDescripterManager() = default;
   DXDescripterManager(const DXDescripterManager &) = delete;
   DXDescripterManager &operator=(const DXDescripterManager &) = delete;
};
} // namespace DX
} // namespace Base
} // namespace CLEYERA