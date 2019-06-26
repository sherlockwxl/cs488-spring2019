// Spring 2019

#include "Primitive.hpp"
#include <tuple>
using namespace std;
using namespace glm;
double exp_test_glo_2 = 0.01;
tuple<int, int, int> cubeIndexPair[12] = {
	{0, 1, 2},//bot
	{2, 3, 0},
	{0, 4, 7},//left
    {7, 3, 0},
    {1, 0, 4},//front
    {4, 5, 1},
    {1, 2, 5},//right
    {6, 2, 5},
    {2, 3, 7},//back
    {7, 6, 2},
    {4, 7, 6},//top
    {6, 5, 4}
}; 


static const glm::vec3 cube_vertex[8]=
{
	//bot x y z
	glm::vec3(-1.0f,  -1.0f, -1.0f), //0
	glm::vec3(-1.0f,  -1.0f,  1.0f), //1
	glm::vec3( 1.0f,  -1.0f,  1.0f), //2
	glm::vec3( 1.0f,  -1.0f, -1.0f), //3
	//top
	glm::vec3(-1.0f,  1.0f,  -1.0f), //4
	glm::vec3(-1.0f,  1.0f,   1.0f), //5
	glm::vec3( 1.0f,  1.0f,   1.0f), //6
	glm::vec3( 1.0f,  1.0f,  -1.0f), //7
};


double checkTriInterct(const Ray ray, glm::vec3 P0, glm::vec3 P1, glm::vec3 P2) {
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

	if((t>exp_test_glo_2) && (beta >= 0) && (gamma >= 0) && (beta + gamma <= 1) ){
        //cout<<"found"<<t<<endl;
		return t;
    }
	else
		return -1;
}


bool rootsValidation(size_t res, double roots[2]){
    if(res <= 0){
        return false;
    }
    if(std::max(roots[0], roots[1]) < exp_test_glo_2)
    {
        return false;
    }

    return true;

}


Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
}

intersection Sphere::checkIntersection(const Ray & ray){

    glm::vec3 centerPos =  glm::vec3(0.0f, 0.0f, 0.0f);
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(glm::vec3(ray.direction), glm::vec3(ray.start) - centerPos);
    float c = glm::dot( glm::vec3(ray.start) - centerPos,  glm::vec3(ray.start) - centerPos) - 1 * 1;

    double roots[2];
    size_t res = quadraticRoots(a, b, c, roots);
    intersection int_res = {};
    if(!rootsValidation(res, roots)){
        int_res.t = -1;// for no intesection
    }else{
       
        if(std::min(roots[0], roots[1]) < 0){
            int_res.t = (float)std::max(roots[0], roots[1]);
        }else{
            int_res.t =  (float)std::min(roots[0], roots[1]);
        }
        int_res.norm_v = glm::vec3(glm::normalize( glm::vec3(ray.start + float(int_res.t) * (ray.direction)) - centerPos ));
        //int_res.norm_v = glm::vec3(glm::normalize(ray.start + float(int_res.t) * (ray.direction)));
        //std::cout << " NonhierBox check slove res:  " <<res<< " " << int_res.t << " " << glm::to_string(int_res.norm_v)<<std::endl;
    }
    return int_res;

}
Cube::~Cube()
{
}

intersection Cube::checkIntersection(const Ray & ray){

    glm::vec3 m_pos =  glm::vec3(0.0f, 0.0f, 0.0f);
    double m_size = 1.0f;
    static glm::vec3 cube_vertex_nonhierBox[8];
    cube_vertex_nonhierBox[0] = m_pos;
    cube_vertex_nonhierBox[1] = m_pos + (float)m_size * glm::vec3(1.0f, 0.0f, 0.0f);
    cube_vertex_nonhierBox[2] = m_pos + (float)m_size * glm::vec3(1.0f, 0.0f, 1.0f);
    cube_vertex_nonhierBox[3] = m_pos + (float)m_size * glm::vec3(0.0f, 0.0f, 1.0f);
    cube_vertex_nonhierBox[4] = m_pos + (float)m_size * glm::vec3(0.0f, 1.0f, 0.0f);
    cube_vertex_nonhierBox[5] = m_pos + (float)m_size * glm::vec3(1.0f, 1.0f, 0.0f);
    cube_vertex_nonhierBox[6] = m_pos + (float)m_size * glm::vec3(1.0f, 1.0f, 1.0f);
    cube_vertex_nonhierBox[7] = m_pos + (float)m_size * glm::vec3(0.0f, 1.0f, 1.0f);
    // check all 12 tri
    intersection int_res = {};
    int_res.t = -1;
    for (int i = 0; i < 11; i++){
        double  temp_res = checkTriInterct(ray, cube_vertex_nonhierBox[std::get<0>(cubeIndexPair[i])],
                                        cube_vertex_nonhierBox[std::get<1>(cubeIndexPair[i])],
                                        cube_vertex_nonhierBox[std::get<2>(cubeIndexPair[i])]);
        if(temp_res >= exp_test_glo_2 && (int_res.t == -1 || (temp_res < int_res.t ))){
            int_res.t = temp_res;
            switch (i){
                case (0):
                case (1):
                    int_res.norm_v = glm::vec3(0.0f, -1.0f, 0.0f);
                    break;
                case (2):
                case (3):
                    int_res.norm_v = glm::vec3(-1.0f, 0.0f, 0.0f);
                    break;
                case (4):
                case (5):
                    int_res.norm_v = glm::vec3(0.0f, 0.0f, -1.0f);
                    break;
                case (6):
                case (7):
                    int_res.norm_v = glm::vec3(1.0f, 0.0f, 0.0f);
                    break;
                case (8):
                case (9):
                    int_res.norm_v = glm::vec3(0.0f, 0.0f, 1.0f);
                    break;
                case (10):
                case (11):
                    int_res.norm_v = glm::vec3(0.0f, 1.0f, 0.0f);
                    break;
            }
        } 
    }
    return int_res;

}
NonhierSphere::~NonhierSphere()
{
}

intersection NonhierSphere::checkIntersection(const Ray & ray){
    glm::vec3 centerPos =  m_pos;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(glm::vec3(ray.direction), glm::vec3(ray.start) - centerPos);
    float c = glm::dot( glm::vec3(ray.start) - centerPos,  glm::vec3(ray.start) - centerPos) - m_radius * m_radius;

    double roots[2];
    size_t res = quadraticRoots(a, b, c, roots);
    intersection int_res = {};
    if(!rootsValidation(res, roots)){
        int_res.t = -1;// for no intesection
    }else{
       
        if(std::min(roots[0], roots[1]) < 0){
            int_res.t = (float)std::max(roots[0], roots[1]);
        }else{
            int_res.t =  (float)std::min(roots[0], roots[1]);
        }
        int_res.norm_v = glm::vec3(glm::normalize( glm::vec3(ray.start + float(int_res.t) * (ray.direction)) - centerPos ));
        //int_res.norm_v = glm::vec3(glm::normalize(ray.start + float(int_res.t) * (ray.direction)));
        //std::cout << " NonhierBox check slove res:  " <<res<< " " << int_res.t << " " << glm::to_string(int_res.norm_v)<<std::endl;
    }
    return int_res;

}


NonhierBox::~NonhierBox()
{
}


intersection NonhierBox::checkIntersection(const Ray & ray){

    static glm::vec3 cube_vertex_nonhierBox[8];
    cube_vertex_nonhierBox[0] = m_pos;
    cube_vertex_nonhierBox[1] = m_pos + (float)m_size * glm::vec3(1.0f, 0.0f, 0.0f);
    cube_vertex_nonhierBox[2] = m_pos + (float)m_size * glm::vec3(1.0f, 0.0f, 1.0f);
    cube_vertex_nonhierBox[3] = m_pos + (float)m_size * glm::vec3(0.0f, 0.0f, 1.0f);
    cube_vertex_nonhierBox[4] = m_pos + (float)m_size * glm::vec3(0.0f, 1.0f, 0.0f);
    cube_vertex_nonhierBox[5] = m_pos + (float)m_size * glm::vec3(1.0f, 1.0f, 0.0f);
    cube_vertex_nonhierBox[6] = m_pos + (float)m_size * glm::vec3(1.0f, 1.0f, 1.0f);
    cube_vertex_nonhierBox[7] = m_pos + (float)m_size * glm::vec3(0.0f, 1.0f, 1.0f);
    // check all 12 tri
    intersection int_res = {};
    int_res.t = -1;
    for (int i = 0; i < 11; i++){
        double  temp_res = checkTriInterct(ray, cube_vertex_nonhierBox[std::get<0>(cubeIndexPair[i])],
                                        cube_vertex_nonhierBox[std::get<1>(cubeIndexPair[i])],
                                        cube_vertex_nonhierBox[std::get<2>(cubeIndexPair[i])]);
        if(temp_res >= exp_test_glo_2 && (int_res.t == -1 || (temp_res < int_res.t ))){
            int_res.t = temp_res;
            switch (i){
                case (0):
                case (1):
                    int_res.norm_v = glm::vec3(0.0f, -1.0f, 0.0f);
                    break;
                case (2):
                case (3):
                    int_res.norm_v = glm::vec3(-1.0f, 0.0f, 0.0f);
                    break;
                case (4):
                case (5):
                    int_res.norm_v = glm::vec3(0.0f, 0.0f, -1.0f);
                    break;
                case (6):
                case (7):
                    int_res.norm_v = glm::vec3(1.0f, 0.0f, 0.0f);
                    break;
                case (8):
                case (9):
                    int_res.norm_v = glm::vec3(0.0f, 0.0f, 1.0f);
                    break;
                case (10):
                case (11):
                    int_res.norm_v = glm::vec3(0.0f, 1.0f, 0.0f);
                    break;
            }
        } 
    }
    return int_res;

}