#include "physics/physics_world.h"

namespace physics {

PhysicsWorld::PhysicsWorld(Stadium stadium, float gravity,
                            float slopeStrength)
    : stadium(stadium), gravity(gravity), slopeStrength(slopeStrength) {}

void PhysicsWorld::addBody(RigidBody body) { bodies.push_back(body); }

const std::vector<RigidBody> &PhysicsWorld::getBodies() const {
  return bodies;
}

const Stadium &PhysicsWorld::getStadium() const { return stadium; }

void PhysicsWorld::stepBody(RigidBody &body, float dt) const {
  glm::vec2 gradient = stadium.gradientAt(body.getPosition());

  // 1. Slope: accelerate "downhill", i.e. opposite the gradient.
  glm::vec2 slopeAcceleration = -gradient * gravity * slopeStrength;

  // 2. Linear friction: opposes velocity, proportional to speed and to
  // the bey's own friction coefficient. Approximates normal-force-scaled
  // kinetic friction without needing a separate normal-force calculation
  // for this flat-ish prototype.
  glm::vec2 frictionAcceleration =
      -body.getVelocity() * body.getLinearFriction();

  glm::vec2 acceleration = slopeAcceleration + frictionAcceleration;

  glm::vec2 newVelocity = body.getVelocity() + acceleration * dt;
  glm::vec2 newPosition = body.getPosition() + newVelocity * dt;

  body.setVelocity(newVelocity);
  body.setPosition(newPosition);

  // 3. Spin decay: stamina loss, always working to bring |spinRate| to 0.
  float spinRate = body.getSpinRate();
  float spinSign = (spinRate > 0.0f) ? 1.0f : ((spinRate < 0.0f) ? -1.0f : 0.0f);
  float decay = body.getSpinFriction() * dt;

  float newSpinRate = spinRate - spinSign * decay;
  // Don't let decay overshoot past zero and flip the sign.
  if (spinSign * newSpinRate < 0.0f) {
    newSpinRate = 0.0f;
  }
  body.setSpinRate(newSpinRate);

  body.setSpinAngle(body.getSpinAngle() + newSpinRate * dt);
}

void PhysicsWorld::step(float dt) {
  for (RigidBody &body : bodies) {
    stepBody(body, dt);
  }
}

} // namespace physics
