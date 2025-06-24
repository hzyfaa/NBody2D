#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>

#include "Node.h"

class Quadtree
{
  static constexpr int ROOT = 0;

public:
  Quadtree(const float t_theta_sq, const float t_epsilon_sq)
      : theta_sq(t_theta_sq), epsilon_sq(t_epsilon_sq) {};

  float theta_sq;
  float epsilon_sq;

  std::vector<Node> nodes;
  std::vector<std::size_t> parents;

  void clear(Quad quad);

  void insert(Vec2 body_position, float body_mass);

  std::size_t subdivide(std::size_t node);

  void propagate();

  Vec2 acceleration(Vec2 position);
};

#endif
