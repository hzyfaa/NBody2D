#include "simulation.h"

Simulation::Simulation(const int width, const int height)
    : width(width), height(height) {}

void Simulation::addBody(const sf::Vector2f& pos, const sf::Vector2f& vel) {
  bodies.emplace_back(pos, vel);
}

void Simulation::activateBody(const sf::Vector2f& vel) {
  bodies.back().setVelocity(vel);
  bodies.back().activate();
}

void Simulation::update() {
  updatePositions();
  updateAccelerations();
  updateVelocities();
  clearOffScreenBodies();
}

const std::vector<Body>& Simulation::getBodies() const { return bodies; }

void Simulation::updateAccelerations() {
  // compute new acceleration (a_t+1)
  for (size_t i = 0; i < bodies.size(); ++i) {
    if (!bodies[i].isActive()) continue;
    for (size_t j = 0; j < bodies.size(); ++j) {
      // skip self or non-active bodies
      if (i == j || !bodies[j].isActive()) continue;
      // acceleration = (G * m_j * r) / |r|^3
      // * gravitational constant = 1
      sf::Vector2f r = bodies[j].getPosition() - bodies[i].getPosition();
      const float magSq = r.x * r.x + r.y * r.y;
      if (const float mag = std::sqrt(magSq); mag > 0) {
        bodies[i].addAcceleration(bodies[j].getMass() / magSq * mag * r);
      }
    }
  }
}

void Simulation::clearOffScreenBodies() {
  // remove bodies outside of canvas
  std::erase_if(bodies, [this](const Body& b) {
    const sf::Vector2f pos = b.getPosition();
    return pos.x < 0 || pos.y < 0 || pos.x > width || pos.y > height;
  });
}

void Simulation::updatePositions() {
  //  update position of each body using current acceleration (a_t)
  for (auto& body : bodies) {
    body.updatePosition(timestep);
    // store current acceleration for velocity calculation
    body.storeAcceleration();
  }
}

void Simulation::updateVelocities() {
  //  use a(t) and a(t + Δt) to get new velocity
  for (auto& body : bodies) body.updateVelocity(timestep);
}
