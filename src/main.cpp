#include <SFML/Graphics.hpp>
#include <vector>

#include "simulation.h"

int main() {
  // window for rendering the simulation
  sf::RenderWindow window(sf::VideoMode(900, 900), "N-Body Simulation");
  // set frame rate to 60 FPS
  window.setFramerateLimit(60);
  // initialize the simulation object
  Simulation simulation;
  // variables used for tracking mouse drag
  bool isDragging = false;
  sf::Vector2f dragStart, dragEnd;

  // *** main loop ***
  while (window.isOpen()) {
    sf::Event event;
    // handle events
    while (window.pollEvent(event)) {
      // exit app
      if (event.type == sf::Event::Closed) window.close();
      // left mouse click: spawn a new body and begin tracking drag
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        dragStart = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        isDragging = true;
        // * new body at the drag start position (initially static)
        simulation.addBody(dragStart, {0.f, 0.f});
      }

      // mouse release : launch body with initial velocity
      if (event.type == sf::Event::MouseButtonReleased &&
          event.mouseButton.button == sf::Mouse::Left && isDragging) {
        dragEnd = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        simulation.activateBody(dragEnd - dragStart);
        isDragging = false;
      }
    }
    // update physics
    simulation.update();
    // remove bodies outside canvas
    simulation.clearOffScreenBodies(window);
    // return bodies vector
    const auto& bodies = simulation.getBodies();
    // clear screen + render state
    window.clear();
    for (const auto& body : bodies) body.draw(window);
    // draw visual vector line while user is dragging
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