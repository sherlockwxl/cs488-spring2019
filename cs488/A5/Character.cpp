#include "Character.hpp"
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