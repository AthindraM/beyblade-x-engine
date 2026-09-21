#include "physics/rigid_body.h"

#include <cmath>

namespace physics {

RigidBody::RigidBody(const std::string &name, glm::vec2 position,
                      glm::vec2 velocity, float spinAngle, float spinRate,
                      float mass, float radius, float linearFriction,
                      float spinFriction)
    : name(name), position(position), velocity(velocity),
      spinAngle(spinAngle), spinRate(spinRate), mass(mass), radius(radius),
      linearFriction(linearFriction), spinFriction(spinFriction) {}

const std::string &RigidBody::getName() const { return name; }

glm::vec2 RigidBody::getPosition() const { return position; }

glm::vec2 RigidBody::getVelocity() const { return velocity; }

float RigidBody::getSpinAngle() const { return spinAngle; }

float RigidBody::getSpinRate() const { return spinRate; }

float RigidBody::getMass() const { return mass; }

float RigidBody::getRadius() const { return radius; }

float RigidBody::getLinearFriction() const { return linearFriction; }

float RigidBody::getSpinFriction() const { return spinFriction; }

void RigidBody::setPosition(glm::vec2 newPosition) { position = newPosition; }

void RigidBody::setVelocity(glm::vec2 newVelocity) { velocity = newVelocity; }

void RigidBody::setSpinAngle(float newSpinAngle) { spinAngle = newSpinAngle; }

void RigidBody::setSpinRate(float newSpinRate) { spinRate = newSpinRate; }

bool RigidBody::isSpunOut(float epsilon) const {
  return std::abs(spinRate) <= epsilon;
}

} // namespace physics
