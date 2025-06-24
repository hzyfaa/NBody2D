#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <vector>

#include "Body.h"

namespace Utils
{
constexpr float tau = 2.0f * M_PI;

inline std::mt19937 &getRng()
{
  thread_local std::mt19937 rng(std::random_device{}());
  return rng;
}

inline float randomFloat(const float min = 0.0f, const float max = 1.0f)
{
  thread_local std::uniform_real_distribution<float> dist;
  return min + (max - min) * dist(getRng());
}

inline Body spiralParticle(const float &arm, const float &arms,
                           const float &tightness)
{
  const float distance = std::pow(randomFloat(), 1.5f) * 150.0f + 30.0f;
  const float angle = tau * arm / arms + tightness * std::log(distance / 30.0f);

  float sin_angle, cos_angle;
  __sincosf(angle, &sin_angle, &cos_angle);

  Vec2 position = Vec2(cos_angle, sin_angle) * distance;
  Vec2 velocity =
      Vec2(-sin_angle, cos_angle) * std::sqrt(1e6f / distance) * 0.7f;

  return {position, velocity};
}

inline std::vector<Body> spiral(const std::size_t n, const int arms = 5,
                                const float tightness = 0.4f)
{
  std::vector<Body> bodies;
  bodies.reserve(n);
  bodies.emplace_back(1e6f, 20.0f, Vec2(), Vec2());

  for (std::size_t i = 1; i < n; i++)
  {
    Body b = spiralParticle(static_cast<float>(i % arms), arms, tightness);
    bodies.emplace_back(b);
  }

  return bodies;
}

inline std::vector<Body> disc(const std::size_t n)
{
  constexpr float i_radius = 25.0f;
  const float o_radius = std::sqrt(static_cast<float>(n)) * 5.0f;
  const float t_sq = (i_radius / o_radius) * (i_radius / o_radius);

  std::vector<Body> bodies;
  bodies.reserve(n);
  bodies.emplace_back(1e6f, i_radius, Vec2(), Vec2());

  std::vector<Body> temp_bodies;
  temp_bodies.reserve(n - 1);

  while (temp_bodies.size() < n - 1)
  {
    const float x = randomFloat();
    const float angle = x * tau;
    float sin_angle, cos_angle;
    __sincosf(angle, &sin_angle, &cos_angle);

    const float r = x * (1.0f - t_sq) + t_sq;
    const float radius = o_radius * std::sqrt(r);

    temp_bodies.emplace_back(Vec2(cos_angle, sin_angle) * radius,
                             Vec2(sin_angle, -cos_angle));
  }

  bodies.insert(bodies.end(), temp_bodies.begin(), temp_bodies.end());

  std::ranges::sort(bodies, [](const Body &a, const Body &b)
                    { return a.position.mag_sq() < b.position.mag_sq(); });

  float enclosed_mass = 1e6f;

  for (auto it = bodies.begin() + 1; it != bodies.end(); ++it)
  {
    enclosed_mass += it->mass;
    const float dist = it->position.magnitude();
    it->velocity *= std::sqrt(enclosed_mass / dist);
  }

  return bodies;
}
} // namespace Utils
#endif
