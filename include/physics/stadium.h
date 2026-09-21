#pragma once

#include <glm/glm.hpp>

namespace physics {

// Stadium floor model, kept deliberately minimal for now: a flat circular
// floor of a given radius. heightAt()/gradientAt() are still exposed with
// the same signatures they'll have once the real geometry (bowl curvature
// + the X-shaped gear-tooth ridge) is added, so PhysicsWorld and anything
// else built against Stadium won't need to change when that lands - only
// this class's internals will.
//
// TODO: reintroduce the bowl curvature and X-ridge/gear-teeth height
// field once the flat-floor physics loop (slope-less friction + spin
// decay + collisions) is working end to end.
class Stadium {
private:
  float radius{};

public:
  explicit Stadium(float radius);

  // Currently always 0 everywhere inside the stadium - flat floor.
  float heightAt(const glm::vec2 &position) const;

  // Currently always the zero vector - flat floor has no slope.
  glm::vec2 gradientAt(const glm::vec2 &position) const;

  float getRadius() const;

  // True if position is outside the stadium wall.
  bool isOutOfBounds(const glm::vec2 &position) const;
};

} // namespace physics
