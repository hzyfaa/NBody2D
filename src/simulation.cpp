#include "simulation.h"

#include <algorithm>
#include <cmath>

Simulation::Simulation(float dt) : timestep(dt) {}

void Simulation::addBody(const sf::Vector2f& pos, const sf::Vector2f& vel) {
  bodies.emplace_back(pos, vel);
}

void Simulation::activateBody(const sf::Vector2f& vel) {
  bodies.back().setVelocity(vel);
  bodies.back().activate();
}

// VV method
void Simulation::update() {
  // *** update position of body using current acceleration and velocity ***
  for (auto& body : bodies) {
    body.updatePosition(timestep);
    body.storeAcceleration();
  }
  // compute new acceleration
  computeAccelerations();

  // update velocity
  for (auto& body : bodies) {
    body.updateVelocity(timestep);
  }
}

const std::vector<Body>& Simulation::getBodies() const { return bodies; }

void Simulation::computeAccelerations() {
  // compute new acceleration
  for (size_t i = 0; i < bodies.size(); ++i) {
    if (!bodies[i].isActive()) continue;
    for (size_t j = 0; j < bodies.size(); ++j) {
      // skip self or non active bodies
      if (i == j || !bodies[j].isActive()) continue;
      // acceleration = (G * m_j * r) / |r|^3
      // * gravitational constant = 1
      sf::Vector2f r = bodies[j].getPosition() - bodies[i].getPosition();
      float magSq = r.x * r.x + r.y * r.y;
      float mag = std::sqrt(magSq);
      if (mag > 0) {
        bodies[i].addAcceleration(((bodies[j].getMass() / magSq * mag) * r));
      }
    }
  }
}

void Simulation::clearOffScreenBodies(const sf::RenderWindow& window) {
  bodies.erase(std::remove_if(bodies.begin(), bodies.end(),
                              [&window](const Body& b) {
                                sf::Vector2f pos = b.getPosition();
                                return pos.x < 0 || pos.y < 0 ||
                                       pos.x > window.getSize().x ||
                                       pos.y > window.getSize().y;
                              }),
               bodies.end());
}