#include "physics/stadium.h"

namespace physics {

Stadium::Stadium(float radius) : radius(radius) {}

float Stadium::heightAt(const glm::vec2 & /*position*/) const { return 0.0f; }

glm::vec2 Stadium::gradientAt(const glm::vec2 & /*position*/) const {
  return glm::vec2{0.0f, 0.0f};
}

float Stadium::getRadius() const { return radius; }

bool Stadium::isOutOfBounds(const glm::vec2 &position) const {
  return glm::length(position) > radius;
}

} // namespace physics
