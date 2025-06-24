#ifndef BODY_H
#define BODY_H
#include "Vec2.h"

struct Body
{
  float mass;
  float radius;
  Vec2 position;
  Vec2 velocity;
  Vec2 acceleration = Vec2();
  Vec2 prev_acceleration = Vec2();

  Body(const Vec2 t_position, const Vec2 t_velocity)
      : mass(1.0f), radius(1.0f), position(t_position), velocity(t_velocity)
  {
  }

  Body(const float t_mass, const float t_radius, const Vec2 t_position,
       const Vec2 t_velocity)
      : mass(t_mass), radius(t_radius), position(t_position),
        velocity(t_velocity) {};

  void updatePosition(const float dt)
  {
    position = position + (velocity * dt) + ((acceleration * 0.5f) * dt * dt);
  }

  void storeAcceleration()
  {
    prev_acceleration = acceleration;
    acceleration = Vec2();
  }

  void updateVelocity(const float dt)
  {
    velocity += 0.5f * (prev_acceleration + acceleration) * dt;
  }
};

#endif