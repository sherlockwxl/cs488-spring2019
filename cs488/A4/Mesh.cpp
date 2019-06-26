// Spring 2019

#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"


double checkTriInterctV2(const Ray ray, glm::vec3 P0, glm::vec3 P1, glm::vec3 P2) {
    glm::vec3 a = glm::vec3(ray.start);
    glm::vec3 b = glm::vec3(ray.direction);
    glm::vec3 base1 = P1 - P0;
    glm::vec3 base2 = P2 - P0;
    glm::vec3 base3 = -1.0f * b;
    glm::vec3 R = a - P0;

    glm::mat3 D{base1, base2, base3};
    D = glm::transpose(D);
    glm::mat3 D1{R, base2, base3};
    D1 = glm::transpose(D1);
    glm::mat3 D2{base1, R, base3};
    D2 = glm::transpose(D2);
    glm::mat3 D3{base1, base2, R};	
    D3 = glm::transpose(D3);
	double beta = glm::determinant(D1)/glm::determinant(D);
	double gamma = glm::determinant(D2)/glm::determinant(D);
	double t = glm::determinant(D3)/glm::determinant(D);

	if((t>0.01) && (beta >= 0) && (gamma >= 0) && (beta + gamma <= 1) ){
        //cout<<"found"<<t<<endl;
		return t;
    }
	else
		return -1;
}



Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  /*
  
  for( size_t idx = 0; idx < mesh.m_verts.size(); ++idx ) {
  	const MeshVertex& v = mesh.m_verts[idx];
  	out << glm::to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << glm::to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << glm::to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}
intersection Mesh::checkIntersection(const Ray & ray){
	intersection int_res = {};
	int_res.t = -1;
	for(Triangle tri : m_faces){
		glm::vec3 P0 = m_vertices.at(tri.v1);
		glm::vec3 P1 = m_vertices.at(tri.v2);
		glm::vec3 P2 = m_vertices.at(tri.v3);
		double  temp_res  = checkTriInterctV2(ray, P0, P1, P2);
		if(temp_res >= 0.01 && (int_res.t == -1 || (temp_res < int_res.t ))){
			//cout<<"found"<<endl;
            int_res.t = temp_res;
			int_res.norm_v = glm::normalize(glm::cross(P1- P0, P2 - P0));
		}
	}
	return int_res;
}