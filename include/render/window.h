#pragma once

#include <string>

struct GLFWwindow;

namespace render {

// Owns a GLFW window + OpenGL 3.3 core context and loads GL function
// pointers via GLAD on construction. One of these should exist for the
// lifetime of the sim.
class Window {
private:
  GLFWwindow *handle{nullptr};
  int width{};
  int height{};

public:
  Window(int width, int height, const std::string &title);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool shouldClose() const;
  void pollEvents() const;
  void swapBuffers() const;

  int getWidth() const;
  int getHeight() const;
  GLFWwindow *getHandle() const;
};

} // namespace render
