#include "render/shader.h"

#include <glad/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace render {

std::string Shader::readFile(const std::string &path) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("Shader: failed to open " + path);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

unsigned int Shader::compile(unsigned int type, const std::string &source) {
  unsigned int shaderId = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shaderId, 1, &src, nullptr);
  glCompileShader(shaderId);

  int success{};
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    int logLength{};
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> log(logLength);
    glGetShaderInfoLog(shaderId, logLength, nullptr, log.data());
    throw std::runtime_error("Shader: compile error: " +
                              std::string(log.data(), log.size()));
  }

  return shaderId;
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  unsigned int vertexId = compile(GL_VERTEX_SHADER, readFile(vertexPath));
  unsigned int fragmentId =
      compile(GL_FRAGMENT_SHADER, readFile(fragmentPath));

  programId = glCreateProgram();
  glAttachShader(programId, vertexId);
  glAttachShader(programId, fragmentId);
  glLinkProgram(programId);

  int success{};
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  if (!success) {
    int logLength{};
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> log(logLength);
    glGetProgramInfoLog(programId, logLength, nullptr, log.data());
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    throw std::runtime_error("Shader: link error: " +
                              std::string(log.data(), log.size()));
  }

  glDeleteShader(vertexId);
  glDeleteShader(fragmentId);
}

Shader::~Shader() { glDeleteProgram(programId); }

void Shader::use() const { glUseProgram(programId); }

unsigned int Shader::getId() const { return programId; }

void Shader::setMat4(const std::string &name, const float *matrixPtr) const {
  int location = glGetUniformLocation(programId, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, matrixPtr);
}

void Shader::setVec3(const std::string &name, float x, float y,
                      float z) const {
  int location = glGetUniformLocation(programId, name.c_str());
  glUniform3f(location, x, y, z);
}

void Shader::setFloat(const std::string &name, float value) const {
  int location = glGetUniformLocation(programId, name.c_str());
  glUniform1f(location, value);
}

} // namespace render
