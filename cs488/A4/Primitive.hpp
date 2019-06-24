// Spring 2019

#pragma once

#include <glm/glm.hpp>
#include "polyroots.hpp"

struct Ray{
	glm::vec4 start;
	glm::vec4 target;
	glm::vec4 locAtDist(float dist){
		return start + (target - start)*dist;
	}
	Ray(glm::vec4 start, glm::vec4 target): start(start), target(target){}
};

class Primitive {
public:
  virtual ~Primitive();
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual double checkIntersection(const Ray ray, ) 
};

class Cube : public Primitive {
public:
  virtual ~Cube();
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size)
  {
  }
  
  virtual ~NonhierBox();

private:
  glm::vec3 m_pos;
  double m_size;
};
