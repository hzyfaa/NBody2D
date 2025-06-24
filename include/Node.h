#ifndef NODE_H
#define NODE_H
#include <iostream>

#include "Quad.h"
#include "Vec2.h"

struct Node
{
  Quad quad;
  std::size_t next;
  std::size_t children = 0;
  float mass = 0.0f;
  Vec2 position = Vec2();

  Node(const Quad t_quad, const std::size_t t_next)
      : quad(t_quad), next(t_next) {};

  [[nodiscard]] bool isBranch() const { return children != 0; };
  [[nodiscard]] bool isLeaf() const { return children == 0; };
  [[nodiscard]] bool isEmpty() const { return mass == 0.0f; };
};

#endif
