#pragma once

#include "physics/rigid_body.h"
#include "physics/stadium.h"

#include <vector>

namespace physics {

// Owns the stadium and all beys currently in play, and advances them by a
// fixed timestep each call to step(). No rendering dependency at all -
// this can be driven headlessly (see src/physics_main.cpp) or from a
// render loop later.
//
// Per-body forces modeled each step, in order:
//   1. Slope force  - the stadium's height field gradient accelerates the
//                      bey "downhill", same as a ball on a curved dish.
//   2. Linear friction - opposes velocity, scaled by the bey's own
//                         friction coefficient (tip-dependent).
//   3. Spin decay    - drains spinRate over time (this is "stamina").
//
// Not yet modeled (left as follow-up work): bey-vs-bey collisions, the
// stadium's outer wall bounce, and spin-to-translation coupling
// (precession/curving paths as spin decays).
class PhysicsWorld {
private:
  Stadium stadium;
  std::vector<RigidBody> bodies;

  float gravity{};       // m/s^2, drives slope force magnitude
  float slopeStrength{}; // extra tunable multiplier on top of gravity

public:
  PhysicsWorld(Stadium stadium, float gravity = 9.81f,
               float slopeStrength = 4.0f);

  void addBody(RigidBody body);
  const std::vector<RigidBody> &getBodies() const;
  const Stadium &getStadium() const;

  // Advances every body by dt seconds. Call with a fixed dt (e.g. 1/120s)
  // for stable behavior at high spin rates.
  void step(float dt);

private:
  void stepBody(RigidBody &body, float dt) const;
};

} // namespace physics
