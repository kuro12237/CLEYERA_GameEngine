#include "VectorFunc.h"

using namespace Math::Vector;
using namespace Math::Matrix;

float Math::Vector::Func::Cot(float theta) { return (1.0f / tan(theta)); }

float Math::Vector::Func::degreesToRadians(float degrees) { return degrees * (float(std::numbers::pi) / 180.0f); }

float Math::Vector::Func::Length(const Vec2 &v) {
   float result{};
   result = sqrtf(v.x * v.x + v.y * v.y);
   return result;
}

float Math::Vector::Func::Length(const Vec3 &v) {
   float result{};
   result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
   return result;
}

Vec3 Math::Vector::Func::Normalize(const Vec3 &v) {

   float len = Length(v);
   if (len == 0)
      return v;

   return v / len;
}

Vec3 Math::Vector::Func::TransformNormal(const Vec3 &v, const Matrix::Mat4x4 &m) {
   Vec3 result{v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0], v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1], v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};

   return result;
}
