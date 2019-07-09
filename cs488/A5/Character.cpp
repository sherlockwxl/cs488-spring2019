#include "Character.hpp"
#include "GeometryNode.hpp"
#include <glm/gtx/io.hpp>
Character::Character(){
    moveLeftOrRight = 0;
    moveUpOrDown = 0;
    moveUpFrameCounter = 0;
    moveLeftFrameCounter = 0;
}
Character::Character(SceneNode m_rootNode){
    m_rootNode = m_rootNode;
    moveLeftOrRight = 0;
    moveUpOrDown = 0;
    moveUpFrameCounter = 0;
    moveLeftFrameCounter = 0;
}

void Character::move(int direction, int type){

    switch (direction){
        case 0:  // move left

            if(moveLeftOrRight == -1 && type == 1){// to end
                moveLeftFrameCounter = persistence;
            }else{
                if(moveLeftOrRight == 1 && type == 1){
                    return;
                }
                moveLeftOrRight = -1;
                moveLeftFrameCounter = -1;
            }


            break;
        case 1:  // move right

            if(moveLeftOrRight == 1 && type == 1){// to end
                moveLeftFrameCounter = persistence;
            }else{
                if(moveLeftOrRight == -1 && type == 1){
                    return;
                }
                moveLeftOrRight = 1;
                moveLeftFrameCounter = -1;
            }

            break;
        case 3: // move up
            if(moveUpOrDown == 1 && type == 1){// to end
                moveUpFrameCounter = persistence;
            }else{
                if(moveUpOrDown == -1 && type == 1){
                    return;
                }
                moveUpOrDown = 1;
                moveUpFrameCounter = -1;
            }

            break;
        case 2: // move down

            if(moveUpOrDown == -1 && type == 1){// to end
                moveUpFrameCounter = persistence;
            }else{
                if(moveUpOrDown == 1 && type == 1){
                    return;
                }
                moveUpOrDown = -1;
                moveUpFrameCounter = -1;
            }

            break;
             
    }
}



void Character::update(){

    GLfloat v_up; 
    if(moveUpFrameCounter == -1){// keep moving
        v_up = v_start * 0.6;
    }else{
        v_up = v_start * (moveUpFrameCounter) /100;
    }
    
    GLfloat v_left;
    if(moveLeftFrameCounter == -1){// keep moving
        v_left = v_start * 0.6;
    }else{
        v_left = v_start * (moveLeftFrameCounter) /100;
    }
     
    glm::vec4 temp = glm::vec4(v_left * moveLeftOrRight, 0.0f , v_up * moveUpOrDown, 0.0f);
	temp = trackBallRotationMatrix * temp;
   // std::cout<<"translate " <<temp<<std::endl;
    m_rootNode->translate(glm::vec3(temp));
    if(moveUpFrameCounter > 0 ){
        moveUpFrameCounter--;
    }
    if(moveLeftFrameCounter > 0){
        moveLeftFrameCounter--;
    }
    if(moveUpFrameCounter == 0){
        moveUpOrDown = 0;
    }
    if(moveLeftFrameCounter == 0){
        moveLeftOrRight = 0;
    }
    if(checkCollisions()){
        m_rootNode->translate(glm::vec3(temp * -1.0f));
        moveUpFrameCounter = 0;
        moveLeftFrameCounter = 0;
        moveLeftOrRight = 0;
        moveUpOrDown = 0;
    }
    
}

// check if two geometry node has collision
// meshid 0 cube; meshid 1 sephere
bool Character::isCollision(SceneNode * LeftNode, SceneNode * RightNode){

    GeometryNode * LeftGeoNode = static_cast<GeometryNode *>(LeftNode);
    GeometryNode * RightGeoNode = static_cast<GeometryNode *>(RightNode);
    //build box for each node
    //cout<<LeftNode->trans<<endl;
    glm::vec3 left_trans = glm::vec3(LeftNode->trans[3][0], LeftNode->trans[3][1], LeftNode->trans[3][2]);
    left_trans = glm::vec3( glm::vec4(left_trans,0.0f) * glm::inverse(trackBallRotationMatrix) );
    glm::vec3 right_trans = glm::vec3(RightNode->trans[3][0], RightNode->trans[3][1], RightNode->trans[3][2]);
    right_trans = glm::vec3(glm::vec4(right_trans, 0.0f) * glm::inverse(trackBallRotationMatrix) );
    GLfloat leftMult;
    GLfloat rightMult;
    if(LeftGeoNode->meshId == "cube"){
        leftMult = 0.5f;
    }else{
        leftMult = 1.0f;
    }

    if(RightGeoNode->meshId == "cube"){
        rightMult = 0.5f;
    }else{
        rightMult = 1.0f;
    }
    
    box leftBox = { std::min(left_trans.x - LeftNode->trans[0][0]*leftMult,  left_trans.x + LeftNode->trans[0][0]*leftMult),
                    std::max(left_trans.x - LeftNode->trans[0][0]*leftMult,  left_trans.x + LeftNode->trans[0][0]*leftMult),
                    std::min(left_trans.y - LeftNode->trans[1][1]*leftMult,  left_trans.y + LeftNode->trans[1][1]*leftMult),
                    std::max(left_trans.y - LeftNode->trans[1][1]*leftMult,  left_trans.y + LeftNode->trans[1][1]*leftMult),
                    std::min(left_trans.z - LeftNode->trans[2][2]*leftMult,  left_trans.z + LeftNode->trans[2][2]*leftMult),
                    std::max(left_trans.z - LeftNode->trans[2][2]*leftMult,  left_trans.z + LeftNode->trans[2][2]*leftMult)};
    box rightBox = { std::min(right_trans.x - RightNode->trans[0][0]*leftMult,  right_trans.x + RightNode->trans[0][0]*leftMult),
                    std::max(right_trans.x - RightNode->trans[0][0]*leftMult,  right_trans.x + RightNode->trans[0][0]*leftMult),
                    std::min(right_trans.y - RightNode->trans[1][1]*leftMult,  right_trans.y + RightNode->trans[1][1]*leftMult),
                    std::max(right_trans.y - RightNode->trans[1][1]*leftMult,  right_trans.y + RightNode->trans[1][1]*leftMult),
                    std::min(right_trans.z - RightNode->trans[2][2]*leftMult,  right_trans.z + RightNode->trans[2][2]*leftMult),
                    std::max(right_trans.z - RightNode->trans[2][2]*leftMult,  right_trans.z + RightNode->trans[2][2]*leftMult)};

    if( (leftBox.min_x <= rightBox.max_x && leftBox.max_x >= rightBox.min_x) &&
         (leftBox.min_y <= rightBox.max_y && leftBox.max_y >= rightBox.min_y) &&
         (leftBox.min_z <= rightBox.max_z && leftBox.max_z >= rightBox.min_z))
         {
              cout<<LeftNode->trans<<endl;
              cout<<RightNode->trans<<endl;
              cout<<"left y : " << leftBox.min_y << " max y : " << leftBox.max_y<<endl;
              cout<<"right y : " << rightBox.min_y << " max  y : " << rightBox.max_y<<endl;
              cout<<"left x : " << leftBox.min_x << " max x : " << leftBox.max_x<<endl;
              cout<<"right x : " << rightBox.min_x << " max  x : " << rightBox.max_x<<endl;
              exit(0);
         }
    return (leftBox.min_x <= rightBox.max_x && leftBox.max_x >= rightBox.min_x) &&
         (leftBox.min_y <= rightBox.max_y && leftBox.max_y >= rightBox.min_y) &&
         (leftBox.min_z <= rightBox.max_z && leftBox.max_z >= rightBox.min_z);
}

bool Character::checkCollisions(){

    for(auto const& id: geoIndexVector) {
        SceneNode * node = findNodeById(*m_rootNode, id);
        for(auto const& other_id: other_geoIndexVector){
            SceneNode * other_node = findNodeById(*other_rootNode, other_id);
            if(isCollision(node, other_node)){
                cout<<" collision :" << node->m_name << " with : " << other_node->m_name<<endl;
                //should trigger movement stop
                return true;

            }
        }
    }
    return false;
}

SceneNode * Character::findNodeById(SceneNode& rootNode, unsigned int id){
	if(rootNode.m_nodeId == id){
		return &rootNode;
	}
	for(SceneNode * nextNode : rootNode.children){
		SceneNode * res = findNodeById(*nextNode, id);
		if(res!= NULL){
			return res;
		}
	}
	return NULL;
}