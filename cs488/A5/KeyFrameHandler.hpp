#ifndef Key_FrameHandler
#define Key_FrameHandler
#include <vector>
#include <glm/glm.hpp>
#include "KeyFrame.hpp"
#include "AnimationModel.hpp"

using namespace std;

class AnimationModel;
class KeyFrameHandler{
    public:
        AnimationModel animationModel;
        KeyFrameHandler();
    
    // return duration
    int addKeyFrameforLeftHit(AnimationModel &animationModel, int character);// 1 for c1 2 for c2
    int addKeyFrameforRunForward(AnimationModel &animationModel, int character);
    void stopMovement(AnimationModel &animationModel, int character);
    void stopAnimation(AnimationModel &animationModel, int character);

};


#endif