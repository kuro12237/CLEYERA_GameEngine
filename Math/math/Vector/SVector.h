#pragma once

namespace Math::Vector {

/// <summary>
/// Vector2
/// </summary>
struct Vec2 {

  float x = 0.0f, y = 0.0f;

  void Init() { x = 0.0f, y = 0.0f; }

  // ���Z�I�y���[�^�[
  Vec2 operator+(const Vec2 &other) const {
    return Vec2{x + other.x, y + other.y};
  }

  // ���Z�I�y���[�^�[
  Vec2 operator-(const Vec2 &other) const {
    return Vec2{x - other.x, y - other.y};
  }

  // ��Z�I�y���[�^�[
  Vec2 operator*(const Vec2 &other) const {
    return Vec2{x * other.x, y * other.y};
  }

  // ����Z�I�y���[�^�[
  Vec2 operator/(const Vec2 &other) const {
    return Vec2{x / other.x, y / other.y};
  }
};

/// <summary>
/// Vector3
/// </summary>
struct Vec3 {
  float x = 0.0f, y = 0.0f, z = 0.0f;

  void Init() { x = 0.0f, y = 0.0f, z = 0.0f; }
  // ���Z�I�y���[�^�[
  Vec3 operator+(const Vec3 &other) const {
    return Vec3{x + other.x, y + other.y, z + other.z};
  }

  // ���Z�I�y���[�^�[
  Vec3 operator-(const Vec3 &other) const {
    return Vec3{x - other.x, y - other.y, z - other.z};
  }

  // ��Z�I�y���[�^�[
  Vec3 operator*(const Vec3 &other) const {
    return Vec3{x * other.x, y * other.y, z * other.z};
  }

  // ����Z�I�y���[�^�[
  Vec3 operator/(const Vec3 &other) const {
    return Vec3{x / other.x, y / other.y, z / other.z};
  }
};

/// <summary>
/// Vector4
/// </summary>
struct Vec4 {
  float x = 0, y = 0, z = 0, w = 0;

  void Init() { x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; }

  // ���Z�I�y���[�^�[
  Vec4 operator+(const Vec4 &other) const {
    return Vec4{x + other.x, y + other.y, z + other.z, w + other.w};
  }

  // ���Z�I�y���[�^�[
  Vec4 operator-(const Vec4 &other) const {
    return Vec4{x - other.x, y - other.y, z - other.z, w - other.w};
  }

  // ��Z�I�y���[�^�[
  Vec4 operator*(const Vec4 &other) const {
    return Vec4{x * other.x, y * other.y, z * other.z, w * other.w};
  }

  // ����Z�I�y���[�^�[
  Vec4 operator/(const Vec4 &other) const {
    return Vec4{x / other.x, y / other.y, z / other.z, w / other.w};
  }
};

} // namespace Math::Vector