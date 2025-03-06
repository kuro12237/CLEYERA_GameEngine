#pragma once
#include "../DXBufferResource/DXBufferResource.h"
#include "../DXComponent.h"

#include"../DXCommand/DXCommandManager.h"

#include "../DXDescripter/DXDescripterManager.h"


namespace CLEYERA {
namespace Base {
namespace DX {

using Microsoft::WRL::ComPtr;

/// <summary>
///
/// </summary>
class DXSwapChain : public DXComponent {
 public:
   DXSwapChain(const std::string &name) : DXComponent(name) {};
   ~DXSwapChain() = default;

   void Create() override;

   void RegisterRTV();

   void Begin();

#pragma region Get

   IDXGISwapChain4 *GetSwapChain() { return swapChain_.Get(); }
   ID3D12Resource *GetSwapChainResource(size_t index)const { return resources_[index]->GetResource(); }
   size_t GetSwapChainCount() { return swapChainCount_; }

#pragma endregion

 private:
   /// <summary>
   /// swapChain
   /// </summary>
   void CreateResources();

   static const size_t swapChainCount_ = 2;
   DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
   ComPtr<IDXGISwapChain4> swapChain_ = nullptr;


   std::array<std::unique_ptr<DXBufferResource<uint32_t>>, swapChainCount_> resources_;

   DXCommandManager *commandManager_ = nullptr;
   DXDescripterManager *descripterManager_ = nullptr;

   
  D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};

};
} // namespace DX
} // namespace Base
} // namespace CLEYERA