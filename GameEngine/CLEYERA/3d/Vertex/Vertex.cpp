#include "Vertex.h"

void CLEYERA::Model3d::system::Vertex::Init() {

   vertexData_.resize(3);

   vertexData_[0].pos = {-0.5f, -0.5f, 0.0f};
   vertexData_[1].pos = {0.5f, -0.5f, 0.0f};
   vertexData_[2].pos = {0.0f, 0.75f, 0.0f};

   buf_ = std::make_unique<Base::DX::DXBufferResource<SVertex>>();
   buf_->SetDevice(Base::DX::DXManager::GetInstance()->GetDevice());

   buf_->Init(vertexData_.size());

   bytesSize_ = static_cast<uint32_t>(sizeof(SVertex) * vertexData_.size());

   D3D12_HEAP_PROPERTIES heapParam;

   heapParam = D3D12_HEAP_PROPERTIES{D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};

   D3D12_RESOURCE_DESC resDesc{};
   resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
   resDesc.Alignment = 0;
   resDesc.Width = bytesSize_;
   resDesc.Height = 1;
   resDesc.DepthOrArraySize = 1;
   resDesc.MipLevels = 1;
   resDesc.Format = DXGI_FORMAT_UNKNOWN;
   resDesc.SampleDesc = {1, 0};
   resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
   resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

   buf_->CreateBuffer(heapParam, D3D12_HEAP_FLAG_NONE, resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr);

   buf_->Map();
   buf_->SetParam(vertexData_);
}

void CLEYERA::Model3d::system::Vertex::Update() {

   buf_->Map();
   buf_->SetParam(vertexData_);
   buf_->UnMap();
}
