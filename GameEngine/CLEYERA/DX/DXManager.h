#pragma once
#include"DXDevice/DXDevice.h"
#include"DXAdapter/DXAdapter.h"
#include"DXFactory/DXFactory.h"
#include"../pch/Pch.h"

namespace CLEYERA::Base::DX {

class DXCommon;

/// <summary>
///
/// </summary>
class DXManager {
public:
  static DXManager *GetInstance() {
    static DXManager instance;
    return &instance;
  }


#pragma region Set
  void SetAdapter(std::weak_ptr<DXAdapter> adapter) {
    adapter_ = adapter;
  }
  void SetFactory(std::weak_ptr<DXFactory> factory) {
    factory_ = factory;
  }
  void SetDevice(std::weak_ptr<DXDevice> device) {
    device_=device;
  }

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