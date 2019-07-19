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
        
    void addKeyFrameforLeftHit(AnimationModel &animationModel);
    void addKeyFrameforRunForward(AnimationModel &animationModel);

};