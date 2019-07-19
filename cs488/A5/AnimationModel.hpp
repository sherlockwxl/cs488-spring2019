
#ifndef ANIMATION_MODEL
#define ANIMATION_MODEL

#include "KeyFrame.hpp"
#include "SceneNode.hpp"
#include "JointNode.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include "cs488-framework/OpenGLImport.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

class AnimationModel{
public:

// for character 1
    vector<SceneNode *> JointPointers_v_c1;
    vector<vector<KeyFrame>> keyFrame_v_ani_c1;
    vector<vector<KeyFrame>> keyFrame_v_move_c1;
    vector<int> durationCont_v_ani_c1;
    vector<int> durationCont_v_move_c1;
    std::vector<GLfloat> ori_joint_angle_c1;
// for character 2
    vector<SceneNode *> JointPointers_v_c2;
    vector<vector<KeyFrame>> keyFrame_v_ani_c2;
    vector<vector<KeyFrame>> keyFrame_v_move_c2;
    vector<int> durationCont_v_ani_c2;
    vector<int> durationCont_v_move_c2;
    std::vector<GLfloat> ori_joint_angle_c2;


    AnimationModel();
    void rotateJointHelper(GLfloat anglex, GLfloat angley, SceneNode & root, int type, int order);
    void recursiveRotate(glm::mat4 revserseTargetMatrix, SceneNode& root, glm::mat4 rotatematrix); 
    void update();
};

#endif