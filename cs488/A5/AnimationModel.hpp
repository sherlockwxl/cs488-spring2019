
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
    vector<SceneNode *> JointPointers_v;
    vector<vector<KeyFrame>> keyFrame_v;
    vector<int> durationCont_v;
    int countForLeftUpArm = 0;;


    AnimationModel();
    void rotateJointHelper(GLfloat anglex, GLfloat angley, SceneNode & root, int type, int order);
    void recursiveRotate(glm::mat4 revserseTargetMatrix, SceneNode& root, glm::mat4 rotatematrix); 
    void update();
};

#endif