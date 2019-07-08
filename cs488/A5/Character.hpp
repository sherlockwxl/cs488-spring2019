
#ifndef CHARACTER
#define CHARACTER

#include <memory>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include "SceneNode.hpp"
struct box{
    GLfloat min_x;
    GLfloat max_x;
    GLfloat min_y;
    GLfloat max_y;
    GLfloat min_z;
    GLfloat max_z;
}
using namespace std;
class Character{
    public:
        GLfloat v_start = 0.1f;
        int persistence = 20;
        std::shared_ptr<SceneNode> m_rootNode;
        glm::mat4 trackBallRotationMatrix;
        int moveUpOrDown; // 1 for up; 0 for neither; -1 for down 
        int moveLeftOrRight; // -1 for left; 0 for neither; 1 for right
        int moveUpFrameCounter;
        int moveLeftFrameCounter;
        Character(SceneNode m_rootNode);
        Character();
        void move(int direction, int type); // 0 for left; 1 for right; 2 for up; 3 for down; type: 0 for start 1 for end
        void update();
        void checkCollisions();
        bool isCollision(SceneNode LeftNode, SceneNode RightNode);
};


#endif