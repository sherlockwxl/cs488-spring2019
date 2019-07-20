#ifndef KEYFRAME
#define KEYFRAME


#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;
class KeyFrame{

public:
    string KeyFrameName;
    string KeyFrameTargetJointName;
    int totalTime;
    int type; // 0 for translation; 1 for rotation
    glm::vec3 rotationTarget;
    glm::vec3 translationTarget;
    int order; // 1 for x first, -1 for y first

    KeyFrame(string KeyFrameName, string KeyFrameTargetJointName, int totalTime, int type, // 0 for translation; 1 for rotation
    int order,
    glm::vec3 rotationTarget,
    glm::vec3 translationTarget)
    : KeyFrameName(KeyFrameName),
    KeyFrameTargetJointName(KeyFrameTargetJointName),
	  totalTime(totalTime),
      type(type),
      order(order),
      rotationTarget(rotationTarget),
      translationTarget(translationTarget){

    };


};

#endif