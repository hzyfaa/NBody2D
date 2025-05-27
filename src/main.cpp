#include <SFML/Graphics.hpp>
#include <vector>

#include "simulation.h"

int main() {
  int width = 700;
  int height = 700;
  int fps = 60;

  // setup
  sf::RenderWindow window(sf::VideoMode(width, height), "N-Body Simulation",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(fps);
  Simulation simulation(width, height);
  sf::Event event{};

  // variables for tracking mouse drag
  bool isDragging = false;
  sf::Vector2f dragStart, dragEnd;

  // *** main loop ***
  while (window.isOpen()) {
    // handle events
    while (window.pollEvent(event)) {
      // exit app
      if (event.type == sf::Event::Closed) window.close();

      // left mouse: spawn body and begin tracking drag
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        dragStart = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        isDragging = true;
        // * new body at the drag start position (initially static)
        simulation.addBody(dragStart, {0.f, 0.f});
      }

      // mouse release: launch body with initial velocity
      if (event.type == sf::Event::MouseButtonReleased &&
          event.mouseButton.button == sf::Mouse::Left && isDragging) {
        dragEnd = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        simulation.activateBody(dragEnd - dragStart);
        isDragging = false;
      }
    }

    // ** update **
    simulation.update();

    // get bodies which is iterated through to draw later
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