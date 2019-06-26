// Spring 2019

#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"

class PhongMaterial : public Material {
public:
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess);
  virtual ~PhongMaterial();
  glm::vec3 get_m_kd();
  glm::vec3 get_m_ks();
  double get_m_shine();
private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;

  double m_shininess;
};
