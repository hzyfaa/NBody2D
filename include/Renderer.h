#ifndef RENDERER_H
#define RENDERER_H
#include "Simulation.h"
#include <SFML/Graphics.hpp>

class Renderer
{
public:
  Renderer(sf::RenderWindow &t_window, Simulation &t_simulation)
      : window(t_window), simulation(t_simulation)
  {
  }

  sf::RenderWindow &window;
  Simulation &simulation;

  Vec2 offset = Vec2();
  float scale{1.0};

  bool is_dragging = false;
  Vec2 drag_start;

  void update() const;

  void drawBodies() const;

  void handleBodySpawn() const;

  void drawVector() const;

  void drawStaticBody() const;

  void handlePress();
  void handleRelease();

  [[nodiscard]] Vec2 worldToScreen(const Vec2 &world_pos) const;
  [[nodiscard]] Vec2 screenToWorld(const Vec2 &screen_pos) const;
};

#endif