#pragma once

#include <string>

namespace render {

// Compiles and links a vertex + fragment shader pair loaded from disk into
// a GL program. Kept intentionally small for the prototype: no uniform
// caching or hot-reload yet.
class Shader {
private:
  unsigned int programId{};

public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  ~Shader();

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  void use() const;
  unsigned int getId() const;

  void setMat4(const std::string &name, const float *matrixPtr) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setFloat(const std::string &name, float value) const;

private:
  static unsigned int compile(unsigned int type, const std::string &source);
  static std::string readFile(const std::string &path);
};

} // namespace render
