#include "render/window.h"

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

namespace render {

namespace {

void framebufferSizeCallback(GLFWwindow *handle, int width, int height) {
  glViewport(0, 0, width, height);
}

} // namespace

Window::Window(int width, int height, const std::string &title)
    : width(width), height(height) {
  if (!glfwInit()) {
    throw std::runtime_error("Window: failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

  handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!handle) {
    glfwTerminate();
    throw std::runtime_error("Window: failed to create GLFW window");
  }

  glfwMakeContextCurrent(handle);
  glfwSetFramebufferSizeCallback(handle, framebufferSizeCallback);

  if (!gladLoadGL(glfwGetProcAddress)) {
    glfwDestroyWindow(handle);
    glfwTerminate();
    throw std::runtime_error("Window: failed to load OpenGL via GLAD");
  }

  glViewport(0, 0, width, height);

  std::cout << "Window: OpenGL context ready (" << glGetString(GL_VERSION)
            << ")\n";
}

Window::~Window() {
  if (handle) {
    glfwDestroyWindow(handle);
  }
  glfwTerminate();
}

bool Window::shouldClose() const { return glfwWindowShouldClose(handle); }

void Window::pollEvents() const { glfwPollEvents(); }

void Window::swapBuffers() const { glfwSwapBuffers(handle); }

int Window::getWidth() const { return width; }

int Window::getHeight() const { return height; }

GLFWwindow *Window::getHandle() const { return handle; }

} // namespace render
