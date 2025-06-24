#include "Renderer.h"

void Renderer::update() const
{
  drawBodies();
  if (is_dragging)
    handleBodySpawn();
}

void Renderer::drawBodies() const
{
  for (const auto &body : simulation.bodies)
  {
    const Vec2 body_position = worldToScreen(body.position);

    sf::CircleShape shape(body.radius * scale);
    shape.setOrigin(body.radius * scale, body.radius * scale);
    shape.setPosition(body_position.x, body_position.y);
    shape.setFillColor(sf::Color::White);

    window.draw(shape);
  }
}

void Renderer::handleBodySpawn() const
{
  drawVector();
  drawStaticBody();
}

void Renderer::drawVector() const
{
  const sf::Vector2i drag_end = sf::Mouse::getPosition(window);

  sf::VertexArray line(sf::Lines, 2);
  line[0].position = sf::Vector2f(drag_start.x, drag_start.y);
  line[1].position = sf::Vector2f(drag_end.x, drag_end.y);
  line[0].color = sf::Color::Green;
  line[1].color = sf::Color::Green;

  window.draw(line);
}

void Renderer::drawStaticBody() const
{
  const float radius = 1.0f;

  sf::CircleShape shape(radius * scale);
  shape.setOrigin(radius * scale, radius * scale);
  shape.setPosition(drag_start.x, drag_start.y);
  shape.setFillColor(sf::Color::White);

  window.draw(shape);
}

Vec2 Renderer::worldToScreen(const Vec2 &world_pos) const
{
  const float half_width = window.getSize().x / 2.0f;
  const float half_height = window.getSize().y / 2.0f;
  return Vec2(half_width + (world_pos.x - offset.x) * scale,
              half_height - (world_pos.y - offset.y) * scale);
}

Vec2 Renderer::screenToWorld(const Vec2 &screen_pos) const
{
  const float half_width = window.getSize().x / 2.0f;
  const float half_height = window.getSize().y / 2.0f;
  return Vec2(
      (screen_pos.x - half_width) / scale + offset.x,
      (half_height - screen_pos.y) / scale + offset.y
  );
}

void Renderer::handlePress()
{
  const sf::Vector2i position = sf::Mouse::getPosition(window);
  drag_start = Vec2(position.x, position.y);
  is_dragging = true;
}

void Renderer::handleRelease()
{
  const Vec2 drag_end =
      Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

  Vec2 position = screenToWorld({drag_start.x, drag_start.y});
  Vec2 velocity = screenToWorld(drag_end) - position;

  simulation.bodies.emplace_back(position, velocity);

  is_dragging = false;
}