// Spring 2019

#include "PhongMaterial.hpp"

PhongMaterial::PhongMaterial(
	const glm::vec3& kd, const glm::vec3& ks, double shininess )
	: m_kd(kd)
	, m_ks(ks)
	, m_shininess(shininess)
{}

PhongMaterial::~PhongMaterial()
{}


glm::vec3 PhongMaterial::get_m_kd(){
	return m_kd;
}


glm::vec3 PhongMaterial::get_m_ks(){
	return m_ks;
}

double PhongMaterial::get_m_shine(){
	return m_shininess;
}
