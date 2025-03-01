#pragma once
#include "DXCommon.h"

namespace CLEYERA::Base::DX {

class DXCommon;

/// <summary>
///
/// </summary>
class DXManager {
public:
  static DXManager &GetInstance() {
    static DXManager instance;
    return instance;
  }

  /// <summary>
  /// common
  /// </summary>
  /// <param name="common"></param>
  void SetPtr(DXCommon *common);

#pragma region Set

#pragma endregion

#pragma region Get

  ID3D12Device5 *GetDevice() { return device_.lock()->GetDevice(); }
  IDXGIFactory7 *GetFactory() { return factory_.lock()->GetFactory(); }
  IDXGIAdapter4 *GetAdapter() { return adapter_.lock()->GetAdapter(); }

#pragma endregion

private:
  std::weak_ptr<DXAdapter> adapter_;
  std::weak_ptr<DXFactory> factory_;
  std::weak_ptr<DXDevice> device_;

#pragma region SIngle

  DXManager() = default;
  ~DXManager() = default;

  DXManager(const DXManager &) = delete;
  DXManager &operator=(const DXManager &) = delete;

#pragma endregion
};
} // namespace CLEYERA::Base::DX