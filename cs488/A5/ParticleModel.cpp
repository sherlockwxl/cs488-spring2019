#include "ParticleModel.hpp"
#include <algorithm> 
#include <iostream>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
ParticleModel::ParticleModel(){};
ParticleModel::ParticleModel(GLfloat lifeTime, glm::vec4 particle_color):
    lifeTime(lifeTime),
    particle_color(particle_color){};


// update will be triggered every frame
void ParticleModel::update(){
    // remove dead ones
    particle_v.erase(std::remove_if(particle_v.begin(), particle_v.end(), 
                       [](const particle & p) { return p.remainLife < 0.0f; }), particle_v.end());
    // update living ones
    for(int i = 0 ; i < particle_v.size(); i++){

        int randdirectionX = (rand() % 3) - 1; 
        int randdirectionZ = (rand() % 3) - 1; 
        double randomx = rand() % 10 * 0.05f;
        double randomz = rand() % 10 * 0.05f;
        particle& particle = particle_v[i];
        // adjust speed for gravity
        particle.v += glm::vec3(randomx * randdirectionX, -0.098f, randomz * randdirectionZ);
        particle.trans = glm::translate(particle.v) * particle.trans;
        particle.remainLife -= 0.01f;
    }

}


void ParticleModel::addParticle(glm::mat4 trans){
    //std::cout<<"add particle called "<< trans<<std::endl;

    for(int i = 0 ; i < 15; i++){
        particle particle = {trans, glm::vec3(0.0f), lifeTime};
        particle_v.push_back(particle);
    }
}