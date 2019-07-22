#include "ball.hpp"
ball::ball(){
    status = 0;
};

void ball::update(){
    if(status == 1){
        glm::vec4 temp = glm::vec4(speed * id, 0.0f , 0.0f, 0.0f);
        temp = trackBallRotationMatrix * temp;
        m_rootNode->translate(glm::vec3(temp));
    }
}

void ball::release(glm::mat4 location){
    if(status == 0){
        m_rootNode->trans[3][0] = location[3][0];
        m_rootNode->trans[3][1] = location[3][1];
        m_rootNode->trans[3][2] = location[3][2];
        m_rootNode->trans[3][3] = location[3][3];
        glm::vec4 temp = glm::vec4(speed * id * 2, speed * -0.2f * 10 , 0.0f, 0.0f);
        temp = trackBallRotationMatrix * temp;
        m_rootNode->translate(glm::vec3(temp));
        status = 1;
    }
    
}
void ball::hit(){
    status = 0;
}