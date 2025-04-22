#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "body.h"

class Simulation {
 private:
  std::vector<Body> bodies;
  float timestep;

 public:
  Simulation(float dt = 1.0f / 60.0f);
  void addBody(const sf::Vector2f& pos, const sf::Vector2f& vel);
  void update();
  void clearOffScreenBodies(const sf::RenderWindow& window);
  const std::vector<Body>& getBodies() const;
  void activateBody(const sf::Vector2f& vel);
  void computeAccelerations();
};

#endif