// Spring 2019

#pragma once

#include <glm/glm.hpp>
#include <algorithm>
#include <iostream>
#include "polyroots.hpp"
//debug
#include <glm/gtx/string_cast.hpp>


using namespace std;

struct Ray{
	glm::vec4 start;
	glm::vec4 direction;
};

struct intersection{
  double t;
  glm::vec3 norm_v;
};

class Primitive {
public:
  bool isPlane = false; // used to disable bounding volume for plane

  virtual ~Primitive();
  virtual intersection checkIntersection(const Ray &ray) = 0;
  
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual intersection checkIntersection(const Ray &ray);
};

class Cube : public Primitive {
public:
  virtual ~Cube();
  virtual intersection checkIntersection(const Ray &ray);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual intersection checkIntersection(const Ray &ray);

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
  virtual intersection checkIntersection(const Ray &ray);

private:
  glm::vec3 m_pos;
  double m_size;
};
