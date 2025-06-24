#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "Simulation.h"

int main()
{
  constexpr uint32_t width = 700;
  constexpr uint32_t height = 700;
  constexpr uint32_t fps = 60;

  sf::RenderWindow window(sf::VideoMode(width, height), "N-Body Simulation",
                          sf::Style::Titlebar | sf::Style::Close);

  window.setFramerateLimit(fps);

  Simulation simulation;
  Renderer renderer(window, simulation);

  // *** main loop ***
  while (window.isOpen())
  {
    sf::Event event{};
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
        break;
      }
      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          renderer.handlePress();
        }
      }
      if (event.type == sf::Event::MouseButtonReleased)
      {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          renderer.handleRelease();
        }
      }
    }

    simulation.update();
    window.clear();
    renderer.update();
    window.display();
  }

  return 0;
}
