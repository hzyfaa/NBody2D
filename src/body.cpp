#include "body.h"

Body::Body(const sf::Vector2f pos, const sf::Vector2f vel)
    : mass(DEFAULT_MASS),
      velocity(vel),
      acceleration(0.f, 0.f),
      prevAcceleration(0.f, 0.f),
      active(false) {
  shape.setRadius(DEFAULT_RADIUS);
  shape.setOrigin(DEFAULT_RADIUS, DEFAULT_RADIUS);
  shape.setFillColor(DEFAULT_COLOR);
  shape.setPosition(pos);
}

void Body::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool Body::isActive() const { return active; }

void Body::activate() { active = true; }

float Body::getMass() const { return mass; }

sf::Vector2f Body::getPosition() const { return shape.getPosition(); }

const sf::Vector2f& Body::getVelocity() const { return velocity; }

void Body::setVelocity(const sf::Vector2f& v) { velocity = v; }

void Body::addAcceleration(const sf::Vector2f& a) { acceleration += a; }

void Body::storeAcceleration() {
  prevAcceleration = acceleration;
  acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Body::updatePosition(const float dt) {
  if (!active) return;
  // P_t+1 = P_t + (V_t * dt) + ((A_t)/2 * dt^2)
  shape.move(velocity * dt + 0.5f * acceleration * dt * dt);
}

void Body::updateVelocity(const float dt) {
  if (!active) return;
  // V_t+1 = V_t + ((A_t + A_t+1)/2 * dt)
  velocity += 0.5f * (prevAcceleration + acceleration) * dt;
}