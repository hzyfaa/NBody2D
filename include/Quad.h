#ifndef QUAD_H
#define QUAD_H
#include "Body.h"
#include "Vec2.h"
#include <vector>

class Quad
{
public:
  Quad(const Vec2 &t_center, const float t_size)
      : center(t_center), size(t_size)
  {
  }

  Vec2 center;
  float size;

  static Quad newContaining(const std::vector<Body> &bodies);

  [[nodiscard]] int findQuad(const Vec2 &pos) const;

  [[nodiscard]] std::array<Quad, 4> subdivide() const;
};

#endif
