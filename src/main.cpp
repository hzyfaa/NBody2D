#include <SFML/Graphics.hpp>
#include <vector>

#include "simulation.h"

const float velocityScale = 1.0f;

int main() {
  sf::RenderWindow window(sf::VideoMode(900, 900), "N-Body Simulation");
  window.setFramerateLimit(60);

  Simulation simulation;

  bool isDragging = false;
  sf::Vector2f dragStart, dragEnd;

  // *** main loop ***
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      // on click : spawn new body
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        dragStart = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        isDragging = true;
        simulation.addBody(dragStart, {0.f, 0.f});
      }

      // on release : launch body with initial velocity
      if (event.type == sf::Event::MouseButtonReleased &&
          event.mouseButton.button == sf::Mouse::Left && isDragging) {
        dragEnd = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        simulation.activateBody(dragEnd - dragStart);
        isDragging = false;
      }
    }

    simulation.update();
    simulation.clearOffScreenBodies(window);

    const auto& bodies = simulation.getBodies();

    window.clear();

    for (const auto& body : bodies) body.draw(window);

    if (isDragging) {
      dragEnd = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
      sf::Vertex line[] = {sf::Vertex(dragStart, sf::Color::Green),
                           sf::Vertex(dragEnd, sf::Color::Green)};
      window.draw(line, 2, sf::Lines);
    }

    window.display();
  }

  return 0;
}