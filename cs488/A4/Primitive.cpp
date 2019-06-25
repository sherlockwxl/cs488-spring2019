// Spring 2019

#include "Primitive.hpp"

bool rootsValidation(size_t res, double roots[2]){
    if(res <= 0){
        return false;
    }
    if(std::max(roots[0], roots[1]) < 0)
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
    std::cout << " Cube Sphere called"<<std::endl;
    glm::vec3 centerPos =  glm::vec3(0.0f, 0.0f, 0.0f);
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(glm::vec3(ray.direction), glm::vec3(ray.start) - centerPos);
    float c = glm::dot( glm::vec3(ray.start) - centerPos,  glm::vec3(ray.start) - centerPos) - 1 * 1;

    double roots[2];
   // std::cout << " NonhierBox check try solve " <<a<< " " << b << " " << c << std::endl;
    size_t res = quadraticRoots(a, b, c, roots);
    //std::cout << " NonhierBox check slove res:  " <<res<< std::endl;
    intersection int_res = {};
    if(!rootsValidation(res, roots)){
        int_res.t = -1;// for no intesection
    }else{
       
        if(std::min(roots[0], roots[1]) < 0){
            int_res.t = std::max(roots[0], roots[1]);
        }else{
            int_res.t =  std::min(roots[0], roots[1]);
        }
        int_res.norm_v = glm::vec3(glm::normalize(ray.start + float(int_res.t) * (ray.direction - ray.start)));
        //std::cout << " NonhierBox check slove res:  " <<res<< " " << int_res.t << " " << glm::to_string(int_res.norm_v)<<std::endl;
    }

    return int_res;

}
Cube::~Cube()
{
}

intersection Cube::checkIntersection(const Ray & ray){
    std::cout << " Cube check called"<<std::endl;
    glm::vec4 centerPos =  glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    double a = glm::dot(ray.direction - ray.start, ray.direction - ray.start);
    double b = 2 * glm::dot(ray.direction - ray.start, ray.start - centerPos);
    double c = glm::dot(ray.start - centerPos, ray.start - centerPos) - 1;

    double roots[2];
    size_t res = quadraticRoots(a, b, c, roots);
    intersection int_res = {};
    if(!rootsValidation(res, roots)){
        int_res.t = -1;// for no intesection
    }else{
        if(std::min(roots[0], roots[1]) < 0){
            int_res.t = std::max(roots[0], roots[1]);
        }else{
            int_res.t =  std::min(roots[0], roots[1]);
        }
        int_res.norm_v = glm::vec3(glm::normalize(ray.start + float(int_res.t) * (ray.direction - ray.start)));
    }

    return int_res;

}
NonhierSphere::~NonhierSphere()
{
}

intersection NonhierSphere::checkIntersection(const Ray & ray){
    //cout << " will ray trace " << glm::to_string(ray.start) << " dir" << glm::to_string(ray.direction) <<endl;
    glm::vec3 centerPos =  m_pos;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(glm::vec3(ray.direction), glm::vec3(ray.start) - centerPos);
    float c = glm::dot( glm::vec3(ray.start) - centerPos,  glm::vec3(ray.start) - centerPos) - m_radius * m_radius;

    double roots[2];
   // std::cout << " NonhierBox check try solve " <<a<< " " << b << " " << c << std::endl;
    size_t res = quadraticRoots(a, b, c, roots);
    //std::cout << " NonhierBox check slove res:  " <<res<< std::endl;
    intersection int_res = {};
    if(!rootsValidation(res, roots)){
        int_res.t = -1;// for no intesection
    }else{
       
        if(std::min(roots[0], roots[1]) < 0){
            int_res.t = (float)std::max(roots[0], roots[1]);
        }else{
            int_res.t =  (float)std::min(roots[0], roots[1]);
        }
        int_res.norm_v = glm::vec3(glm::normalize(centerPos - glm::vec3(ray.start + float(int_res.t) * (ray.direction)) ));
        //int_res.norm_v = glm::vec3(glm::normalize(ray.start + float(int_res.t) * (ray.direction)));
        //std::cout << " NonhierBox check slove res:  " <<res<< " " << int_res.t << " " << glm::to_string(int_res.norm_v)<<std::endl;
    }

    return int_res;

}


NonhierBox::~NonhierBox()
{
}


intersection NonhierBox::checkIntersection(const Ray & ray){
    cout << " will ray trace " << glm::to_string(ray.start) << " dir" << glm::to_string(ray.direction) <<endl;
    glm::vec4 centerPos =  glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    double a = glm::dot(ray.direction - ray.start, ray.direction - ray.start);
    double b = 2 * glm::dot(ray.direction - ray.start, ray.start - centerPos);
    double c = glm::dot(ray.start - centerPos, ray.start - centerPos) - 1;

    double roots[2];
     std::cout << " NonhierBox check try solve " <<std::endl;
    size_t res = quadraticRoots(a, b, c, roots);
     std::cout << " NonhierBox check solved "<< res <<std::endl;
    intersection int_res = {};
    if(!rootsValidation(res, roots)){
        int_res.t = -1;// for no intesection
    }else{
        if(std::min(roots[0], roots[1]) < 0){
            int_res.t = std::max(roots[0], roots[1]);
        }else{
            int_res.t =  std::min(roots[0], roots[1]);
        }
        int_res.norm_v = glm::vec3(glm::normalize(ray.start + float(int_res.t) * (ray.direction - ray.start)));
    }

    return int_res;

}