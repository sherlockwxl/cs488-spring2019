


#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
class KeyFrame{

public:
    string KetFrameName;
    float lasttime;
    int type; // 0 for translation; 1 for rotation
    glm::vec3 rotationTarget;
    glm::vec3 translationTarget;

    KeyFrame(string name, 
    float lasttime,
    int type, // 0 for translation; 1 for rotation
    glm::vec3 rotationTarget,
    glm::vec3 translationTarget)
    : KetFrameName(name),
	  lasttime(lasttime),
      type(type),
      rotationTarget(rotationTarget),
      translationTarget(translationTarget){

    }

};