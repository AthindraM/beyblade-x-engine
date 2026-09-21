#include "physics/physics_world.h"

#include <iomanip>
#include <iostream>

// Headless harness for the physics types: no window, no GL, just steps a
// couple of beys through a stadium and prints state over time. Useful for
// sanity-checking the height field / forces before any rendering exists,
// and as a starting point for real unit tests later.
int main() {
  // Flat circular floor for now - bowl curvature and the X-ridge come
  // later. Radius roughly matches a Beyblade X "Standard" type stadium.
  physics::Stadium stadium(/* radius */ 0.20f);

  physics::PhysicsWorld world(stadium);

  world.addBody(physics::RigidBody(
      "AttackerBey", /* position */ glm::vec2{0.10f, 0.0f},
      /* velocity */ glm::vec2{0.0f, 0.4f},
      /* spinAngle */ 0.0f, /* spinRate */ 60.0f,
      /* mass */ 0.032f, /* radius */ 0.02f,
      /* linearFriction */ 0.6f, /* spinFriction */ 1.2f));

  world.addBody(physics::RigidBody(
      "DefenderBey", /* position */ glm::vec2{-0.08f, 0.02f},
      /* velocity */ glm::vec2{0.0f, -0.1f},
      /* spinAngle */ 0.0f, /* spinRate */ -45.0f,
      /* mass */ 0.038f, /* radius */ 0.022f,
      /* linearFriction */ 0.5f, /* spinFriction */ 0.8f));

  constexpr float dt = 1.0f / 120.0f;
  constexpr float printInterval = 0.5f; // seconds
  float elapsed = 0.0f;
  float sinceLastPrint = 0.0f;

  std::cout << std::fixed << std::setprecision(4);

  while (elapsed < 8.0f) {
    world.step(dt);
    elapsed += dt;
    sinceLastPrint += dt;

    if (sinceLastPrint >= printInterval) {
      sinceLastPrint = 0.0f;
      std::cout << "t=" << elapsed << "s\n";
      for (const physics::RigidBody &body : world.getBodies()) {
        glm::vec2 pos = body.getPosition();
        std::cout << "  " << body.getName() << " pos=(" << pos.x << ", "
                  << pos.y << ") spinRate=" << body.getSpinRate()
                  << (body.isSpunOut() ? " [SPUN OUT]" : "")
                  << (stadium.isOutOfBounds(pos) ? " [OUT OF BOUNDS]" : "")
                  << '\n';
      }
    }
  }

  return 0;
}
