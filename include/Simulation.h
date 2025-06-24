#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>

#include "Body.h"
#include "Quadtree.h"
#include "Utils.h"

class Simulation
{
public:
  std::vector<Body> bodies = Utils::spiral(500);
  float dt = 1.0f / 60.0f;
  float theta = 0.5f;
  float epsilon = 0.1f;
  float position_correction = 0.1f;
  float response_coefficient = 0.90f;
  Quadtree qtree = Quadtree(theta * theta, epsilon *epsilon);

  void update();
  void updatePositions();
  void attract();
  void updateVelocities();
  void handleCollisions();
};

#endif
