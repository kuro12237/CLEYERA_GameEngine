#pragma once
#include "BaseMaterial3d.h"

namespace CLEYERA {
namespace Model3d {
namespace Material {

struct ColorMaterialData {

  Math::Vector::Vec4 color_;
};


class ColorMaterial:public MaterialBase<ColorMaterialData> {
public:
  ColorMaterial() {};
  ~ColorMaterial() {};

private:
}; // namespace Materialclass ColorMaterial
} // namespace Material
} // namespace Model
} // namespace CLEYERA