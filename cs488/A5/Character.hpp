
#ifndef CHARACTER
#define CHARACTER

#include <memory>
#include <glm/glm.hpp>
#include "SceneNode.hpp"

using namespace std;
class Character{
    public:
        std::shared_ptr<SceneNode> m_rootNode;
        bool moveUpOrDown; // 1 for up; 0 for neither; -1 for down 
        bool moveLeftOrRight; // -1 for left; 0 for neither; 1 for right
        Character(SceneNode m_rootNode);
};


#endif