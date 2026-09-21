#include "render/window.h"

#include <glad/gl.h>

#include <iostream>

// Entry point for the Beyblade X physics sim. Separate from BeybladeXEngine
// (the combo/deck CRUD app) since the two have very different runtime
// loops. For now this just opens a window and clears the screen each
// frame, to prove the GLFW + GLAD + OpenGL pipeline is wired up correctly
// before any stadium/bey rendering or physics is added on top.
int main() {
  try {
    render::Window window(1280, 720, "Beyblade X Sim");

    while (!window.shouldClose()) {
      window.pollEvents();

      glClearColor(0.08f, 0.09f, 0.11f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      window.swapBuffers();
    }
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
