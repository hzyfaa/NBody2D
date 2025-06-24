#ifndef VEC2_H
#define VEC2_H
#include <cmath>

struct Vec2
{
  float x = 0.0f;
  float y = 0.0f;

  constexpr Vec2() noexcept = default;
  constexpr Vec2(const float t_x, const float t_y) noexcept : x(t_x), y(t_y) {}

  constexpr Vec2 operator+(const Vec2 &other) const noexcept
  {
    return {x + other.x, y + other.y};
  }

  constexpr Vec2 &operator+=(const Vec2 &other) noexcept
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  constexpr Vec2 operator-(const Vec2 &other) const noexcept
  {
    return {x - other.x, y - other.y};
  }

  constexpr Vec2 &operator-=(const Vec2 &other) noexcept
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  constexpr Vec2 operator*(float scalar) const noexcept
  {
    return {x * scalar, y * scalar};
  }

  constexpr Vec2 &operator*=(float scalar) noexcept
  {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  constexpr Vec2 operator/(float scalar) const noexcept
  {
    const float inv_scalar = 1.0f / scalar;
    return {x * inv_scalar, y * inv_scalar};
  }

  constexpr Vec2 &operator/=(float scalar) noexcept
  {
    const float inv_scalar = 1.0f / scalar;
    x *= inv_scalar;
    y *= inv_scalar;
    return *this;
  }

  constexpr bool operator==(const Vec2 &other) const noexcept
  {
    return x == other.x && y == other.y;
  }

  constexpr bool operator!=(const Vec2 &other) const noexcept
  {
    return !(*this == other);
  }

  [[nodiscard]] constexpr float mag_sq() const noexcept
  {
    return x * x + y * y;
  }

  [[nodiscard]] float magnitude() const noexcept { return std::sqrt(mag_sq()); }

  [[nodiscard]] Vec2 normal() const noexcept
  {
    const float mag2 = mag_sq();
    const float inv_mag = mag2 > 0.0f ? 1.0f / std::sqrt(mag2) : 0.0f;
    return {x * inv_mag, y * inv_mag};
  }

  [[nodiscard]] constexpr float dot(const Vec2 &other) const noexcept
  {
    return x * other.x + y * other.y;
  }
};

constexpr Vec2 operator*(float scalar, const Vec2 &vec) noexcept
{
  return vec * scalar;
}

constexpr Vec2 operator/(float scalar, const Vec2 &vec) noexcept
{
  return {scalar / vec.x, scalar / vec.y};
}

#endif
