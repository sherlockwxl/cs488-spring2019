


#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
class KeyFrame{

public:
    string KetFrameName;
    int totalTime;
    int type; // 0 for translation; 1 for rotation
    glm::vec2 rotationTarget;
    glm::vec3 translationTarget;
    int order; // 1 for x first, -1 for y first

    KeyFrame(string name, 
    int totalTime,
    int type, // 0 for translation; 1 for rotation
    int order,
    glm::vec2 rotationTarget,
    glm::vec3 translationTarget)
    : KetFrameName(name),
	  totalTime(totalTime),
      type(type),
      order(order),
      rotationTarget(rotationTarget),
      translationTarget(translationTarget){

    }

};