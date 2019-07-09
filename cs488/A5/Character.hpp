
#ifndef CHARACTER
#define CHARACTER

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "SceneNode.hpp"

#include "cs488-framework/OpenGLImport.hpp"

struct box{
    GLfloat min_x;
    GLfloat max_x;
    GLfloat min_y;
    GLfloat max_y;
    GLfloat min_z;
    GLfloat max_z;
};
using namespace std;
class Character{
    public:
        GLfloat v_start = 0.1f;
        int persistence = 20;
        std::shared_ptr<SceneNode> m_rootNode;
        std::shared_ptr<SceneNode> other_rootNode;
        std::vector<int> geoIndexVector;
        std::vector<int> other_geoIndexVector;
        glm::mat4 trackBallRotationMatrix;
        int moveUpOrDown; // 1 for up; 0 for neither; -1 for down 
        int moveLeftOrRight; // -1 for left; 0 for neither; 1 for right
        int moveUpFrameCounter;
        int moveLeftFrameCounter;
        Character(SceneNode m_rootNode);
        Character();
        void move(int direction, int type); // 0 for left; 1 for right; 2 for up; 3 for down; type: 0 for start 1 for end
        void update();
        bool checkCollisions();
        bool isCollision(SceneNode * LeftNode, SceneNode * RightNode);
        SceneNode * findNodeById(SceneNode& rootNode, unsigned int id);
};


#endif