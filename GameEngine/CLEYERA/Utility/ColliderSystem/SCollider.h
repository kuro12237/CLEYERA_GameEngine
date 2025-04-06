#pragma once

#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

namespace system {

struct OBB {

   Math::Vector::Vec3 center{};
   Math::Vector::Vec3 rotate{};
   std::array<Math::Vector::Vec3, 3> orientations{};
   Math::Vector::Vec3 size{};
};

} // namespace system
} // namespace Collider
} // namespace Util
} // namespace CLEYERA