#pragma once
#include "../../pch/Pch.h"
#include"../../DX/DXManager.h"
#include"../../Graphics/ShaderManager/ShaderManager.h"

namespace CLEYERA {
namespace Model3d {
namespace system {

/// <summary>
///
/// </summary>
class PiplineStateObject {
 public:
   PiplineStateObject() {};
   ~PiplineStateObject() {};

   void Init();

#pragma region Set

   void SetGlobalRootSignature(ID3D12RootSignature *r) { globalRootSignature_ = r; }
#pragma endregion

   #pragma region get
   ComPtr<ID3D12StateObject> GetStateObject() { return stateObject_; }

#pragma endregion



 private:
   ID3D12RootSignature *globalRootSignature_ = nullptr;
   ID3D12Device5 *device_ = nullptr;

   Microsoft::WRL::ComPtr<ID3D12StateObject> stateObject_;
};

} // namespace system
} // namespace Model3d
} // namespace CLEYERA