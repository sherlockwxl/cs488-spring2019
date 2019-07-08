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
        case 2: // move up

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
        case 3: // move down

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
}

// check if two geometry node has collision
// meshid 0 cube; meshid 1 sephere
void Character::isCollision(SceneNode LeftNode, SceneNode RightNode){
    GeometryNode * LeftGeoNode = static_cast<GeometryNode *>(LeftNode);
    GeometryNode * RightGeoNode = static_cast<GeometryNode *>(RightNode);
    //build box for each node
    glm::vec3 left_trans = glm::vec3(LeftNode.trans[0][3], LeftNode.trans[1][3], LeftNode.trans[2][3]);
    glm::vec3 right_trans = glm::vec3(RightNode.trans[0][3], RightNode.trans[1][3], RightNode.trans[2][3]);
    box leftBox = { left_trans.x - LeftNode.trans[0][0],
                    left_trans.x + LeftNode.trans[0][0],
                    left_trans.y - LeftNode.trans[1][1],
                    left_trans.y + LeftNode.trans[1][1],
                    left_trans.z - LeftNode.trans[2][2],
                    left_trans.z + LeftNode.trans[2][2]};
    box rightBox = { right_trans.x - RightNode.trans[0][0],
                    right_trans.x + RightNode.trans[0][0],
                    right_trans.y - RightNode.trans[1][1],
                    right_trans.y + RightNode.trans[1][1],
                    right_trans.z - RightNode.trans[2][2],
                    right_trans.z + RightNode.trans[2][2]};


    return (leftBox.min_x <= rightBox.max_x && leftBox.max_x >= rightBox.min_x) &&
         (leftBox.min_y <= rightBox.max_y && leftBox.max_y >= rightBox.min_y) &&
         (leftBox.min_z <= rightBox.max_z && leftBox.max_z >= rightBox.min_z);
}