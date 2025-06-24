#include "Simulation.h"

#include "Quad.h"

void Simulation::update()
{
  handleCollisions();
  updatePositions();
  attract();
  updateVelocities();
};

void Simulation::updatePositions()
{
  for (Body &body : bodies)
  {
    body.updatePosition(dt);
    body.storeAcceleration();
  }
}

void Simulation::attract()
{
  const Quad quad = Quad::newContaining(bodies);
  qtree.clear(quad);
  for (const Body &body : bodies)
    qtree.insert(body.position, body.mass);
  qtree.propagate();
  for (Body &body : bodies)
  {
    body.acceleration = qtree.acceleration(body.position);
  }
};

void Simulation::updateVelocities()
{
  for (Body &body : bodies)
  {
    body.updateVelocity(dt);
  }
}

void Simulation::handleCollisions()
{
  for (size_t i = 0; i < bodies.size(); ++i)
  {
    for (size_t j = i + 1; j < bodies.size(); ++j)
    {
      Body &a = bodies[i];
      Body &b = bodies[j];

      Vec2 delta = b.position - a.position;
      const float dist = delta.magnitude();

      if (const float min_dist = a.radius + b.radius; dist < min_dist)
      {
        Vec2 normal = delta.normal();

        Vec2 relative_vel = b.velocity - a.velocity;

        float impulse = -(1.0f + response_coefficient) * relative_vel.dot(normal);
        impulse /= (1.0f / a.mass + 1.0f / b.mass);
        a.velocity -= (impulse * normal) / a.mass;
        b.velocity += (impulse * normal) / b.mass;

        const float overlap = (min_dist - dist) * position_correction;
        const Vec2 correction = normal * overlap;
        const float total_mass = a.mass + b.mass;

        a.position -= correction * (b.mass / total_mass);
        b.position += correction * (a.mass / total_mass);
      }
    }
  }
}
