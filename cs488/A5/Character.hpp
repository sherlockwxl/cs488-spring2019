
#ifndef CHARACTER
#define CHARACTER

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "SceneNode.hpp"
#include "AnimationModel.hpp"
#include "KeyFrameHandler.hpp"

#include "cs488-framework/OpenGLImport.hpp"

#include "irrklang/irrKlang.h"

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
        int id;
        GLfloat v_upOrDown = 0.0f;
        GLfloat v_forOrBack = 0.0f;
        GLfloat v_leftOrRight = 0.0f;
        GLfloat mass;
        GLfloat u = 0.1f;
        int persistence = 20;
        GLfloat g = 0.098f;
        std::shared_ptr<SceneNode> m_rootNode;
        std::shared_ptr<SceneNode> other_rootNode;
        std::shared_ptr<SceneNode> leftFoot_Node;
        std::shared_ptr<SceneNode> rightFoot_Node;
        std::shared_ptr<SceneNode> ground_Node;
        std::vector<int> geoIndexVector;
        std::vector<int> other_geoIndexVector;
        glm::mat4 trackBallRotationMatrix;
        bool isOntheGround;
        int moveUpOrDown; // 1 for up; 0 for neither; -1 for down 
        int moveLeftOrRight; // -1 for left; 0 for neither; 1 for right
        int jump = 2; // 0 for rest state, 1 for jump called; 2 for during jump
        int moveUpFrameCounter;
        int moveLeftFrameCounter;
        Character *enemy;
        AnimationModel *animationModel;
        KeyFrameHandler *keyFrameHandler;
        std::vector<glm::vec3> ori_joint_angle;

        int animationDuration;
        int movementDuration;

        int status;// 0 for default, -1 for attack, 1 for defence


        Character(SceneNode m_rootNode);
        Character();
        void move(int direction, int type); // 0 for left; 1 for right; 2 for up; 3 for down; type: 0 for start 1 for end
        void update();
        bool checkCollisions();
        void checkOntheGround();
        bool isCollision(SceneNode * LeftNode, SceneNode * RightNode);
        SceneNode * findNodeById(SceneNode& rootNode, unsigned int id);
        box getBoundingBox(SceneNode * node);
        void gotHit(int NodeId);

        irrklang::ISoundEngine *SoundEngine;
        irrklang::ISound *chracterWalkSound;
        irrklang::vec3df getPosition();

        void hitwithLeftHand();
        void hitwithLeftLeg();
        void stopMovement();
        void stopAnimation();
        void updateAllNodeStatus();
        void updatecurrentStatus();
};


#endif