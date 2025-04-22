#ifndef BODY_H
#define BODY_H

#include <SFML/Graphics.hpp>

class Body {
 public:
  static constexpr float DEFAULT_RADIUS = 5.0f;
  static constexpr float DEFAULT_MASS = 1.0f;
  inline static const sf::Color DEFAULT_COLOR = sf::Color::White;

  Body(sf::Vector2f pos, sf::Vector2f vel);

  void draw(sf::RenderWindow& window) const;

  // body state
  bool isActive() const;
  void activate();

  // accessors
  float getMass() const;
  sf::Vector2f getPosition() const;
  const sf::Vector2f& getVelocity() const;

  // mutators
  void setVelocity(const sf::Vector2f& v);
  void addAcceleration(const sf::Vector2f& a);
  void storeAcceleration();
  void updatePosition(float dt);
  void updateVelocity(float dt);

 private:
  sf::CircleShape shape;
  float mass;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  sf::Vector2f prevAcceleration;
  bool active;
};

#endif