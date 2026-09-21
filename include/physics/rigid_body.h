#pragma once

#include <glm/glm.hpp>
#include <string>

namespace physics {

// State of a single spinning bey in the stadium. This is a plain state
// container; PhysicsWorld owns the actual integration/forces so this stays
// easy to unit test and easy to hand to a renderer later.
//
// Note "spin" here is rotation about the vertical (stadium-normal) axis,
// which is what drives friction/stamina loss and knockback resistance.
// It's tracked separately from linear position/velocity.
class RigidBody {
private:
  std::string name{};

  glm::vec2 position{};   // meters, stadium-local
  glm::vec2 velocity{};   // meters/second

  float spinAngle{};      // radians, current facing/rotation
  float spinRate{};       // radians/second, signed: + = counterclockwise

  float mass{};            // kg
  float radius{};          // contact radius, meters
  float linearFriction{};  // dimensionless coefficient, opposes velocity
  float spinFriction{};    // dimensionless coefficient, drains spinRate

public:
  RigidBody(const std::string &name, glm::vec2 position, glm::vec2 velocity,
            float spinAngle, float spinRate, float mass, float radius,
            float linearFriction, float spinFriction);

  const std::string &getName() const;

  glm::vec2 getPosition() const;
  glm::vec2 getVelocity() const;
  float getSpinAngle() const;
  float getSpinRate() const;
  float getMass() const;
  float getRadius() const;
  float getLinearFriction() const;
  float getSpinFriction() const;

  void setPosition(glm::vec2 newPosition);
  void setVelocity(glm::vec2 newVelocity);
  void setSpinAngle(float newSpinAngle);
  void setSpinRate(float newSpinRate);

  // True once spin has decayed to (near) zero - a common "knocked out by
  // stamina loss" condition, distinct from being knocked out of the
  // stadium by getPosition() exceeding the stadium radius.
  bool isSpunOut(float epsilon = 0.05f) const;
};

} // namespace physics
