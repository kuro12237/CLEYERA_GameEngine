#pragma once
#include "SCollider.h"

namespace CLEYERA {

namespace Util {

namespace Collider {

namespace system {

namespace Func {

bool OBBCheck(const OBB &obb1, const OBB &obb2);

// 射影の重複チェック
bool TestAxis(const Math::Vector::Vec3 &axis, const OBB &obb1, const OBB &obb2);
// 頂点を軸に射影
std::pair<float, float> OBBProjection(const OBB &obb, const Math::Vector::Vec3 &axis);

bool ProjectionOverlap(const std::pair<float, float> &projection1, const std::pair<float, float> &projection2);

} // namespace Func
} // namespace system
} // namespace Collider
} // namespace Util
} // namespace CLEYERA