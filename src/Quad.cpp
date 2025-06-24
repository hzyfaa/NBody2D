#include "Quad.h"

Quad Quad::newContaining(const std::vector<Body> &bodies)
{
  float min_x = std::numeric_limits<float>::max();
  float min_y = std::numeric_limits<float>::max();
  float max_x = std::numeric_limits<float>::lowest();
  float max_y = std::numeric_limits<float>::lowest();

  for (const auto &body : bodies)
  {
    min_x = std::min(min_x, body.position.x);
    min_y = std::min(min_y, body.position.y);
    max_x = std::max(max_x, body.position.x);
    max_y = std::max(max_y, body.position.y);
  }

  const Vec2 center = Vec2(min_x + max_x, min_y + max_y) * 0.5;
  const float size = std::max(max_x - min_x, max_y - min_y);

  return {center, size};
};

int Quad::findQuad(const Vec2 &pos) const
{
  return ((pos.y > center.y) << 1) | (pos.x > center.x);
};

std::array<Quad, 4> Quad::subdivide() const
{
  std::array quads = {*this, *this, *this, *this};
  for (int i = 0; i < 4; ++i)
  {
    quads[i].size *= 0.5f;
    quads[i].center.x += (static_cast<float>(i & 1) - 0.5f) * size;
    quads[i].center.y += (static_cast<float>(i >> 1) - 0.5f) * size;
  }
  return quads;
}