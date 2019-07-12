#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include <glm/glm.hpp>
#include <vector>
struct particle{
    glm::mat4 trans;
    glm::vec3 v;
    GLfloat remainLife;

};

class ParticleModel{
    public:
        GLfloat lifeTime;
        glm::vec4 particle_color;
        std::vector<particle> particle_v;

        ParticleModel();
        ParticleModel(GLfloat lifeTime, glm::vec4 particle_color);
        void update();
        void addParticle(glm::mat4 trans);
};
