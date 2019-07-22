
#ifndef BALL
#define BALL
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "SceneNode.hpp"
#include <glm/glm.hpp>
#include <memory>

class ball{
    public:
        std::shared_ptr<SceneNode> m_rootNode;
        int status; // 0 for defualt 1 for released
        int id; // 1 for player 1; -1 for player 2
        glm::mat4 trackBallRotationMatrix;
        GLfloat speed = 0.3f;
        ball();
        void update();
        void release(glm::mat4 location);
        void hit();
};


#endif