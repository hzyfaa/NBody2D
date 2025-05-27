#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "body.h"

class Simulation {
 private:
  std::vector<Body> bodies;
  int width;
  int height;
  float timestep = 1.0f / 60.0f;

 public:
  Simulation(int width, int height);
  void addBody(const sf::Vector2f& pos, const sf::Vector2f& vel);
  void update();
  void clearOffScreenBodies();
  const std::vector<Body>& getBodies() const;
  void activateBody(const sf::Vector2f& vel);
  void updateAccelerations();
  void updatePositions();
  void updateVelocities();
};

#endif