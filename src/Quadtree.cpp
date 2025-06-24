#include "Quadtree.h"

#include <ostream>
#include <ranges>

void Quadtree::clear(Quad quad)
{
  nodes.clear();
  parents.clear();
  nodes.emplace_back(quad, 0);
};

void Quadtree::insert(const Vec2 body_position, const float body_mass)
{
  std::size_t node = ROOT;

  while (nodes[node].isBranch())
  {
    const int quad = nodes[node].quad.findQuad(body_position);
    node = nodes[node].children + quad;
  }

  if (nodes[node].isEmpty())
  {
    nodes[node].position = body_position;
    nodes[node].mass = body_mass;
    return;
  }

  const Vec2 p = nodes[node].position;
  const float m = nodes[node].mass;

  if (body_position == p)
  {
    nodes[node].mass += body_mass;
    return;
  }

  while (true)
  {
    const std::size_t children = subdivide(node);
    const int q1 = nodes[node].quad.findQuad(p);
    const int q2 = nodes[node].quad.findQuad(body_position);

    if (q1 == q2)
    {
      node = children + q1;
    }
    else
    {
      const std::size_t n1 = children + q1;
      const std::size_t n2 = children + q2;
      nodes[n1].position = p;
      nodes[n1].mass = m;
      nodes[n2].position = body_position;
      nodes[n2].mass = body_mass;
      return;
    }
  }
};

std::size_t Quadtree::subdivide(const std::size_t node)
{
  parents.push_back(node);
  const std::size_t children = nodes.size();
  nodes[node].children = children;

  std::array<std::size_t, 4> next_nodes = {
      {children + 1, children + 2, children + 3, nodes[node].next}};

  std::array<Quad, 4> quads = nodes[node].quad.subdivide();

  for (int i = 0; i < 4; i++)
  {
    nodes.emplace_back(quads[i], next_nodes[i]);
  }

  return children;
};

void Quadtree::propagate()
{
  for (const unsigned long node : std::ranges::reverse_view(parents))
  {
    const std::size_t i = nodes[node].children;

    nodes[node].position = (nodes[i].position * nodes[i].mass) +
                           (nodes[i + 1].position * nodes[i + 1].mass) +
                           (nodes[i + 2].position * nodes[i + 2].mass) +
                           (nodes[i + 3].position * nodes[i + 3].mass);

    nodes[node].mass = nodes[i].mass + nodes[i + 1].mass + nodes[i + 2].mass +
                       nodes[i + 3].mass;

    if (const float mass = nodes[node].mass; mass > 0)
    {
      nodes[node].position /= mass;
    }
  }
};

Vec2 Quadtree::acceleration(const Vec2 position)
{
  auto result = Vec2();
  std::size_t node = ROOT;

  while (true)
  {
    Node &n = nodes[node];
    Vec2 d = n.position - position;

    if (const float d_sq = d.mag_sq();
        n.isLeaf() || (n.quad.size * n.quad.size) < (d_sq * theta_sq))
    {
      const float denom = (d_sq + epsilon_sq) * std::sqrt(d_sq);
      const float min =
          (denom == 0) ? std::numeric_limits<float>::max() : (n.mass / denom);

      result += d * min;

      if (n.next == 0)
        break;

      node = n.next;
    }
    else
    {
      node = n.children;
    }
  }
  return result;
};