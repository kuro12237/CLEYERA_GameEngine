#pragma once
#include "DX/DXBufferResource/DXBufferResource.h"
#include "math.h"

namespace CLEYERA {

namespace Sprite2d {

namespace System {

struct Mesh2d {

  Math::Vector::Vec4 vertex = {};
};

class SpriteMesh {
public:
  SpriteMesh();
  ~SpriteMesh() {};

  void Create();

  void Transfar();

  void CommandVB();


private:
  std::unique_ptr<Base::DX::DXBufferResource<Mesh2d>> buf_ = nullptr;
  std::vector<Mesh2d> mesh_;
};

} // namespace System

} // namespace Sprite2d

} // namespace CLEYERA
