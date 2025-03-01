#include "DXCommon.h"
#include "DXManager.h"

using namespace CLEYERA::Base::DX;

void DXCommon::Create() {

  dxManager_ = DXManager::GetInstance();

#ifdef _DEBUG

  debugLayer_ = std::make_shared<DXDebugLayer>(VAR_NAME(DXDebugLayer));
  componentList_.push_back(debugLayer_);

#endif // _DEBUG

  factory_ = std::make_shared<DXFactory>(VAR_NAME(DXFactory));
  componentList_.push_back(factory_);
  adapter_ = std::make_shared<DXAdapter>(VAR_NAME(DXAdapter));
  componentList_.push_back(adapter_);
  device_ = std::make_shared<DXDevice>(VAR_NAME(DXDevice));
  componentList_.push_back(device_);

#ifdef _DEBUG
  infoQueue_ = std::make_shared<DXInfoQueue>(VAR_NAME(DXInfoQueue));
  componentList_.push_back(infoQueue_);
#endif // _DEBUG

  commandQueue_ = std::make_shared<DXCommandQueue>(VAR_NAME(DXCommandQueue));
  componentList_.push_back(commandQueue_);
  commandAllcator_ =
      std::make_shared<DXCommandAllocator>(VAR_NAME(DXCommandAllocator));
  componentList_.push_back(commandAllcator_);

  commandList_ = std::make_shared<DXCommandList>(VAR_NAME(DXCommandList));
  componentList_.push_back(commandList_);

  swapChain_ = std::make_shared<DXSwapChain>(VAR_NAME(DXSwapChain));
  componentList_.push_back(swapChain_);

  for (auto &obj : componentList_) {
    obj.lock()->AddObserver(logManager_);
  }

#ifdef _DEBUG

  debugLayer_->Create();
  dxManager_->SetDebugLayer(debugLayer_);

#endif // _DEBUG

  factory_->Create();
  dxManager_->SetFactory(factory_);

  adapter_->Create();
  dxManager_->SetAdapter(adapter_);

  device_->Create();
  dxManager_->SetDevice(device_);

#ifdef _DEBUG

  infoQueue_->Create();
  dxManager_->SetInfoQueue(infoQueue_);

#endif // _DEBUG

  commandQueue_->Create();
  dxManager_->SetCommandQueue(commandQueue_);

  commandAllcator_->Create();
  dxManager_->SetCommandAllocator(commandAllcator_);

  commandList_->Create();
  dxManager_->SetCommandList(commandList_);

  swapChain_->Create();
  dxManager_->SetSwapChain(swapChain_);
}

void CLEYERA::Base::DX::DXCommon::Finalize() {
  swapChain_.reset();
  commandList_.reset();
  commandAllcator_.reset();
  commandQueue_.reset();
#ifdef _DEBUG
  infoQueue_.reset();
#endif // _DEBUG

  device_.reset();
  adapter_.reset();
  factory_.reset();

#ifdef _DEBUG
  debugLayer_.reset();
#endif // _DEBUG

  ComPtr<IDXGIDebug1> debug;
  if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
    debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
    debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
    debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
  }
}
