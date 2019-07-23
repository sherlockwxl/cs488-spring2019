//TODO: fix AABB issue may need to implement new check approach
#include "Character.hpp"
#include "GeometryNode.hpp"
#include <glm/gtx/io.hpp>

using namespace irrklang;
Character::Character(){
    moveLeftOrRight = 0;
    moveUpOrDown = 0;
    moveUpFrameCounter = 0;
    moveLeftFrameCounter = 0;
    SoundEngine = createIrrKlangDevice();
    animationDuration = 0;
    movementDuration = 0;
    irrklang::vec3df position(0,3,3);        // position of the listener
    irrklang::vec3df lookDirection(0,0,-2); // the direction the listener looks into
    irrklang::vec3df velPerSecond(0,0,0);    // only relevant for doppler effects
    irrklang::vec3df upVector(0,1,0);        // where 'up' is in your 3D scene

    SoundEngine->setListenerPosition(position, lookDirection, velPerSecond, upVector);
    chracterWalkSound = SoundEngine->play3D("Assets/walk_sound.wav",position, GL_TRUE,  GL_TRUE, GL_TRUE);
    chracterWalkSound->setPlaybackSpeed(0.8f);
    chracterWalkSound->setMinDistance(5.0f); // a loud sound

    moveRecord = glm::vec3(0.0f);
    isOntheGround = false;
    isOntheGroundStrict = false;
    hitByBallTimeCount = 0;
    status = 0;
    
}
Character::Character(SceneNode m_rootNode){
    m_rootNode = m_rootNode;
    moveLeftOrRight = 0;
    moveUpOrDown = 0;
    moveUpFrameCounter = 0;
    moveLeftFrameCounter = 0;
    moveRecord = glm::vec3(0.0f);
    isOntheGround = false;
    isOntheGroundStrict = false;
    hitByBallTimeCount = 0;
    status = 0;
}
Character::~Character()
{
}
void Character::move(int direction, int type){

    switch (direction){
        case 0:  // move left

            if(moveLeftOrRight == -1 && type == 1){// to end
                moveLeftFrameCounter = persistence;
            }else{
                if((moveLeftOrRight == 1 || moveLeftOrRight == 0) && type == 1){
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
                if((moveLeftOrRight == -1 || moveLeftOrRight == 0)&& type == 1){
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
                if((moveUpOrDown == -1  || moveUpOrDown == 0) && type == 1){
                    return;
                }
                moveUpOrDown = 1;
                moveUpFrameCounter = -1;
            }

            break;
        case 2: // move down
            //cout<<" current " << moveUpOrDown << " type : "<< type<< " counter :"<<moveUpFrameCounter<<endl;
            if(moveUpOrDown == -1 && type == 1){// to end
                moveUpFrameCounter = persistence;
            }else{
                if((moveUpOrDown == 1 || moveUpOrDown == 0) && type == 1){
                    return;
                }
                moveUpOrDown = -1;
                moveUpFrameCounter = -1;
            }

            break;
        case 4: // jump
            //cout<<"jump called on :"<<jump<<endl;
            if(jump == 0){
                jump = 1;
            }
            break;
             
    }
}



void Character::update(){
    if(hitByBallTimeCount != 0){
        hitByBallTimeCount = std::max(hitByBallTimeCount - 1, 0);
    }
    updatecurrentStatus();
    animationDuration = std::max(animationDuration - 1,0);
    checkOntheGround();
    GLfloat v_up; 
    if(jump == 1){ // jump triggered
        //if(isOntheGround){
            v_upOrDown = jumpstartSpeed;
            jump = 2;
       // }
    }else if (jump == 2){// during jump
        v_upOrDown -= g;
       // cout << " v " << v_upOrDown<<endl;
        box leftFootBox = getBoundingBox(leftFoot_Node.get());
        box rightFootBox = getBoundingBox(rightFoot_Node.get());
        box baseBox = getBoundingBox(ground_Node.get());
        if(v_upOrDown < 0.0f){// going down
            if(v_upOrDown < (baseBox.max_y - std::min(leftFootBox.min_y, rightFootBox.min_y))){
                v_upOrDown = (baseBox.max_y - std::min(leftFootBox.min_y, rightFootBox.min_y));
                //cout<<baseBox.max_y<< " min : "<<baseBox.min_y<<endl;
                //cout<<  std::min(leftFootBox.min_y, rightFootBox.min_y)<<endl;
                //cout<<"gap : " << (baseBox.max_y - std::min(leftFootBox.min_y, rightFootBox.min_y))<<endl;
                
            }
        }    
        if(isOntheGround){
            jumpSound = SoundEngine->play2D("Assets/walk_sound.wav",GL_FALSE);
            v_upOrDown = 0.0f;
            jump = 0;
        }
    }
    
    
    v_up = v_upOrDown;
    GLfloat v_for; 
    if(moveUpFrameCounter == -1){// keep moving
        v_forOrBack = startSpeed;
    }else{
        v_forOrBack = std::max(v_forOrBack - g*u, 0.0f);
    }
    v_for = v_forOrBack;

    GLfloat v_left;
    if(moveLeftFrameCounter == -1){// keep moving
        v_leftOrRight = startSpeed;
    }else{
        v_leftOrRight = std::max(v_leftOrRight - g*u, 0.0f);
    }
    v_left = v_leftOrRight;


    glm::vec4 temp = glm::vec4(v_left * moveLeftOrRight, v_up , v_for * moveUpOrDown, 0.0f);
	temp = trackBallRotationMatrix * temp;
    moveRecord = moveRecord-vec3(temp);
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
    checkOntheGroundStrict();
    if( isOntheGroundStrict){// touch the ground after last move
        box leftFootBox = getBoundingBox(leftFoot_Node.get());
        box rightFootBox = getBoundingBox(rightFoot_Node.get());
        box baseBox = getBoundingBox(ground_Node.get());
        GLfloat gap = (baseBox.max_y - std::min(leftFootBox.min_y, rightFootBox.min_y));
        //cout<<"current gap: "<< gap<<endl;
        if(gap > 0){// need to move back
            //cout<<"need to move back: "<< gap<<endl;
            m_rootNode->translate(glm::vec3(0.0f, gap, 0.0f));
            jump = 0;
        }

    }


    if(checkCollisions()){
        m_rootNode->translate(glm::vec3(temp * -1.0f));
        moveRecord = moveRecord+vec3(temp);
        stopMovement();
        if(animationDuration > 0){
            if(status != 1){
                stopAnimation();
            }
            
        }
    }else{
        irrklang::vec3df newPosition = getPosition();
        chracterWalkSound->setPosition(newPosition);
        //cout<<glm::length2(v_left)<<" "<<glm::length2(v_for)<<endl;
        if(glm::length2(v_left) > 0 || glm::length2(v_for) > 0){
            chracterWalkSound->setIsPaused(false);
            keyFrameHandler->addKeyFrameforRunForward(*animationModel, id);
        }else{
            if(moveLeftOrRight !=0 || moveUpOrDown != 0){
                stopMovement();
            }
            chracterWalkSound->setIsPaused(true);
        }
    }
    weaponBall->update();
    if(enemy->weaponBall->status == 1 && weaponBall->status == 1){
        if(isCollision(weaponBall->m_rootNode.get(), enemy->weaponBall->m_rootNode.get())){
            weaponBall->hit();
            enemy->weaponBall->hit();
        }
    }
    if(checkBallCollisions()){
        weaponBall->hit();
    }

    updateAllNodeStatus();
}

// check if two geometry node has collision
// meshid 0 cube; meshid 1 sephere
bool Character::isCollision(SceneNode * LeftNode, SceneNode * RightNode){


    box leftBox = getBoundingBox(LeftNode);
    box rightBox = getBoundingBox(RightNode);
    if( (leftBox.min_x <= rightBox.max_x && leftBox.max_x >= rightBox.min_x) &&
         (leftBox.min_y <= rightBox.max_y && leftBox.max_y >= rightBox.min_y) &&
         (leftBox.min_z <= rightBox.max_z && leftBox.max_z >= rightBox.min_z))
         {
             /* if(LeftNode->m_name == "leftFoot"){
                  cout<<LeftNode->trans<<endl;
               cout<<RightNode->trans<<endl;
               cout<<"left y : " << leftBox.min_y << " max y : " << leftBox.max_y<<endl;
               cout<<"right y : " << rightBox.min_y << " max  y : " << rightBox.max_y<<endl;
               cout<<"left x : " << leftBox.min_x << " max x : " << leftBox.max_x<<endl;
               cout<<"right x : " << rightBox.min_x << " max  x : " << rightBox.max_x<<endl;
               cout<<"left z : " << leftBox.min_z << " max z: " << leftBox.max_z<<endl;
               cout<<"right z : " << rightBox.min_z << " max z : " << rightBox.max_z<<endl;  
               //exit(0);
             } */
              
         }
    return ((leftBox.min_x <= rightBox.max_x && leftBox.max_x >= rightBox.min_x) &&
         (leftBox.min_y <= rightBox.max_y && leftBox.max_y >= rightBox.min_y) &&
         (leftBox.min_z <= rightBox.max_z && leftBox.max_z >= rightBox.min_z));
}

bool Character::checkCollisions(){

    for(auto const& id: geoIndexVector) {
        SceneNode * node = findNodeById(*m_rootNode, id);
        for(auto const& other_id: other_geoIndexVector){
            SceneNode * other_node = findNodeById(*other_rootNode, other_id);
            if(isCollision(node, other_node)){
                //cout<<" collision :" << node->m_name << " with : " << other_node->m_name<<endl;
                if(status == -1){
                    enemy->gotHit(other_id);
                }
                //should trigger movement stop
                return true;

            }
        }
    }

    for(auto const& id: geoIndexVector) {
        SceneNode * node = findNodeById(*m_rootNode, id);
        if(isCollision(node, back_Node.get())||
           isCollision(node, left_Node.get())||
           isCollision(node, right_Node.get())||
           isCollision(node, front_Node.get())){
            //cout<<"collision"<<endl;
            return true;

        }
    }
    return false;
}

bool Character::checkBallCollisions(){
    SceneNode * node = weaponBall->m_rootNode.get();
    if(weaponBall->status == 1){
        for(auto const& other_id: other_geoIndexVector){
            SceneNode * other_node = findNodeById(*other_rootNode, other_id);
            if(isCollision(node, other_node)){
                //cout<<" collision :" << node->m_name << " with : " << other_node->m_name<<endl;

                enemy->gotHitByBall(other_id);

                //should trigger movement stop
                return true;

            }
        }


        if(isCollision(node, back_Node.get())||
            isCollision(node, left_Node.get())||
            isCollision(node, right_Node.get())||
            isCollision(node, front_Node.get())){
            //cout<<"collision"<<endl;
            return true;

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


void Character::checkOntheGround(){
    if(isCollision(leftFoot_Node.get(), ground_Node.get()) || isCollision(rightFoot_Node.get(), ground_Node.get())){
        isOntheGround = true;
       // exit(0);
    }else{
        isOntheGround = false;
    }
}

box Character::getBoundingBox(SceneNode* node){
    GeometryNode * GeoNode = static_cast<GeometryNode *>(node);

    //build box for each node
    //cout<<LeftNode->trans<<endl;
    // test
    glm::vec3 trans = glm::vec3(GeoNode->trans[3][0], GeoNode->trans[3][1], GeoNode->trans[3][2]);
    trans = glm::vec3( glm::vec4(trans,0.0f) * glm::inverse(trackBallRotationMatrix) );
    GLfloat Mult;
    if(GeoNode->meshId == "cube"){
        Mult = 0.5f;
    }else{
        Mult = 0.65f;
    }
    glm::vec3 Box_base[] = {glm::vec3(-1.0f*Mult, -1.0f*Mult, -1.0f*Mult),
                           glm::vec3(-1.0f*Mult, -1.0f*Mult, 1.0f*Mult),
                           glm::vec3(-1.0f*Mult, 1.0f*Mult, -1.0f*Mult),
                           glm::vec3(1.0f*Mult, -1.0f*Mult, -1.0f*Mult),
                           glm::vec3(-1.0f*Mult, 1.0f*Mult, 1.0f*Mult),
                           glm::vec3(1.0f*Mult, -1.0f*Mult, 1.0f*Mult),
                           glm::vec3(1.0f*Mult, 1.0f*Mult, -1.0f*Mult),
                           glm::vec3(1.0f*Mult, 1.0f*Mult, 1.0f*Mult), };

    glm::vec3 max = glm::vec3(-1000.0f, -1000.0f, -1000.0f);
    glm::vec3 min = glm::vec3(1000.0f, 1000.0f, 1000.0f);
    for(int i = 0; i < 8; i++){
        glm::vec3 transformed = glm::vec3(GeoNode->trans * glm::vec4(Box_base[i], 1.0f));
        //cout<<"ori : " << LeftNode->trans <<endl;
        //cout<<"after : " << left_transformed<<endl;
        min.x = std::min(min.x, transformed.x);
        min.y = std::min(min.y, transformed.y);
        min.z = std::min(min.z, transformed.z);
        max.x = std::max(max.x, transformed.x);
        max.y = std::max(max.y, transformed.y);
        max.z = std::max(max.z, transformed.z);

    }
    box Box = {
        min.x,
        max.x,
        min.y,
        max.y,
        min.z,
        max.z
    };
    return Box;
}

void Character::gotHit(int NodeId){
    SceneNode * node = findNodeById(*m_rootNode, NodeId);
    GeometryNode * GeoNode = static_cast<GeometryNode *>(node);
    //cout<<" got hit on : " << node->m_name<<endl;
    if(status != 1){
        if(GeoNode->hitTimeCount == 0){
            GeoNode->isHit = true;
            GeoNode->hitTimeCount = 60;
            lifeValue -= 10;
            gotHitSound = SoundEngine->play2D("Assets/gothit.wav", GL_FALSE);
        }
    }
    
    
    //TODO: reduce life value after
}

void Character::gotHitByBall(int NodeId){
    SceneNode * node = findNodeById(*m_rootNode, NodeId);
    GeometryNode * GeoNode = static_cast<GeometryNode *>(node);
    //cout<<" got hit by ball on : " << node->m_name<<endl;
    //cout<<" current stautus" << status<< " time : "<< hitByBallTimeCount<<endl;
    if(status != 1){
        if(hitByBallTimeCount == 0){
            GeoNode->isHit = true;
            hitByBallTimeCount = 30;
            lifeValue = std::max(lifeValue-50, 0);
            gotHitSound = SoundEngine->play2D("Assets/gothit.wav", GL_FALSE);
        }
    }
    
    
    //TODO: reduce life value after
}


irrklang::vec3df Character::getPosition(){
    irrklang::vec3df position;
    
    GeometryNode * GeoNode = static_cast<GeometryNode *>(m_rootNode.get());

    //build box for each node
    //cout<<LeftNode->trans<<endl;
    // test
    glm::vec3 trans = glm::vec3(GeoNode->trans[3][0], GeoNode->trans[3][1], GeoNode->trans[3][2]);
    trans = glm::vec3( glm::vec4(trans,0.0f) * glm::inverse(trackBallRotationMatrix) );
    //std::cout<<"run covert"<<trans<<std::endl;
    position.X = -1 *(double)trans.x;
    position.Y = 1 * (double)trans.y;
    position.Z = 1 * (double)trans.z;
    return position;
}



void Character::hitwithLeftHand(){// 45
    if(animationDuration<30){
         animationDuration += keyFrameHandler->addKeyFrameforLeftHit(*animationModel, id);
    }else{
         //cout <<" left hit dropped"<<endl;
    }
}

void Character::hitwithLeftLeg(){ // 55
    if(animationDuration<30){
         animationDuration += keyFrameHandler->addKeyFrameforLeftLegHit(*animationModel, id);
    }else{
        //cout <<" left leg dropped"<<endl;
    }
}

void Character::defend(){
    if(animationDuration<70){
         animationDuration += keyFrameHandler->addKeyFrameforDefend(*animationModel, id);
    }
}

void Character::stopMovement(){
    //cout<<"stop movement called"<<endl;
    moveUpOrDown = 0;
    moveLeftOrRight = 0;
    moveLeftFrameCounter = 0;
    moveUpFrameCounter = 0;
    v_forOrBack = 0.0f;
    v_leftOrRight = 0.0f;
    keyFrameHandler->stopMovement(*animationModel, id);
}

void Character::stopAnimation(){
    //cout<<"stop animation called"<<endl;
    animationDuration = 0;
    keyFrameHandler->stopAnimation(*animationModel, id);
}

void Character::updateAllNodeStatus(){
    for(auto const& id: geoIndexVector) {
        SceneNode * node = findNodeById(*m_rootNode, id);
        if(node->m_nodeType == NodeType::GeometryNode){
            GeometryNode * GeoNode = static_cast<GeometryNode *>(node);
            if(GeoNode->isHit){
                if(GeoNode->particleTriggered == true){
                    GeoNode->hitTimeCount = std::max(GeoNode->hitTimeCount - 1, 0);
                    if(GeoNode->hitTimeCount == 0){
                        GeoNode->isHit = false;
                        GeoNode->particleTriggered =false;
                    }
                }
            }
        }
    }
}


void Character::updatecurrentStatus(){
    status = animationModel->getCurrentStatus(id);
}

void Character::resetCharacter(){
    stopAnimation();
    stopAnimation();
    m_rootNode->translate(glm::vec3(moveRecord));
    moveRecord = glm::vec3(0.0f);
    lifeValue = 100;
    jump = 2;

    animationDuration = 0;
    movementDuration = 0;
    isOntheGround = false;
    isOntheGroundStrict = false;
    hitByBallTimeCount = 0;
    status = 0;

    startSpeed = 0.1f;
    jumpstartSpeed = 0.6f;


}

bool Character::isCollisionStrict(SceneNode * LeftNode, SceneNode * RightNode){

    
    box leftBox = getBoundingBox(LeftNode);
    box rightBox = getBoundingBox(RightNode);
    if( (leftBox.min_x <= rightBox.max_x && leftBox.max_x >= rightBox.min_x) &&
         (leftBox.min_y <= rightBox.max_y && leftBox.max_y >= rightBox.min_y) &&
         (leftBox.min_z <= rightBox.max_z && leftBox.max_z >= rightBox.min_z))
         {
/*                cout<<LeftNode->trans<<endl;
               cout<<RightNode->trans<<endl;
               cout<<"left y : " << leftBox.min_y << " max y : " << leftBox.max_y<<endl;
               cout<<"right y : " << rightBox.min_y << " max  y : " << rightBox.max_y<<endl;
               cout<<"left x : " << leftBox.min_x << " max x : " << leftBox.max_x<<endl;
               cout<<"right x : " << rightBox.min_x << " max  x : " << rightBox.max_x<<endl;
               cout<<"left z : " << leftBox.min_z << " max z: " << leftBox.max_z<<endl;
               cout<<"right z : " << rightBox.min_z << " max z : " << rightBox.max_z<<endl; */
               //exit(0);
         }
    return (leftBox.min_x < rightBox.max_x && leftBox.max_x > rightBox.min_x) &&
         (leftBox.min_y < rightBox.max_y && leftBox.max_y > rightBox.min_y) &&
         (leftBox.min_z < rightBox.max_z && leftBox.max_z > rightBox.min_z);
}

void Character::checkOntheGroundStrict(){
    if(isCollisionStrict(leftFoot_Node.get(), ground_Node.get()) || isCollisionStrict(rightFoot_Node.get(), ground_Node.get())){
        isOntheGroundStrict = true;
        //cout<<"on the ground strict"<<endl;
       // exit(0);
    }else{
        isOntheGroundStrict = false;
    }
}


void Character::releaseBall(){
    weaponBall->release(m_rootNode->trans);
}
// backup box generation code
/* GeometryNode * LeftGeoNode = static_cast<GeometryNode *>(LeftNode);
    GeometryNode * RightGeoNode = static_cast<GeometryNode *>(RightNode);
    //build box for each node
    //cout<<LeftNode->trans<<endl;
    // test
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
    glm::vec3 leftBox_base[] = {glm::vec3(-1.0f*leftMult, -1.0f*leftMult, -1.0f*leftMult),
                           glm::vec3(-1.0f*leftMult, -1.0f*leftMult, 1.0f*leftMult),
                           glm::vec3(-1.0f*leftMult, 1.0f*leftMult, -1.0f*leftMult),
                           glm::vec3(1.0f*leftMult, -1.0f*leftMult, -1.0f*leftMult),
                           glm::vec3(-1.0f*leftMult, 1.0f*leftMult, 1.0f*leftMult),
                           glm::vec3(1.0f*leftMult, -1.0f*leftMult, 1.0f*leftMult),
                           glm::vec3(1.0f*leftMult, 1.0f*leftMult, -1.0f*leftMult),
                           glm::vec3(1.0f*leftMult, 1.0f*leftMult, 1.0f*leftMult), };

    glm::vec3 rightBox_base[] = {glm::vec3(-1.0f*rightMult, -1.0f*rightMult, -1.0f*rightMult),
                           glm::vec3(-1.0f*rightMult, -1.0f*rightMult, 1.0f*rightMult),
                           glm::vec3(-1.0f*rightMult, 1.0f*rightMult, -1.0f*rightMult),
                           glm::vec3(1.0f*rightMult, -1.0f*rightMult, -1.0f*rightMult),
                           glm::vec3(-1.0f*rightMult, 1.0f*rightMult, 1.0f*rightMult),
                           glm::vec3(1.0f*rightMult, -1.0f*rightMult, 1.0f*rightMult),
                           glm::vec3(1.0f*rightMult, 1.0f*rightMult, -1.0f*rightMult),
                           glm::vec3(1.0f*rightMult, 1.0f*rightMult, 1.0f*rightMult), };

    glm::vec3 left_max = glm::vec3(-1000.0f, -1000.0f, -1000.0f);
    glm::vec3 left_min = glm::vec3(1000.0f, 1000.0f, 1000.0f);
    glm::vec3 right_max = glm::vec3(-1000.0f, -1000.0f, -1000.0f);
    glm::vec3 right_min = glm::vec3(1000.0f, 1000.0f, 1000.0f);
    for(int i = 0; i < 8; i++){
        glm::vec3 left_transformed = glm::vec3(LeftNode->trans * glm::vec4(leftBox_base[i], 1.0f));
        //cout<<"ori : " << LeftNode->trans <<endl;
        //cout<<"after : " << left_transformed<<endl;
        left_min.x = std::min(left_min.x, left_transformed.x);
        left_min.y = std::min(left_min.y, left_transformed.y);
        left_min.z = std::min(left_min.z, left_transformed.z);
        left_max.x = std::max(left_max.x, left_transformed.x);
        left_max.y = std::max(left_max.y, left_transformed.y);
        left_max.z = std::max(left_max.z, left_transformed.z);

        glm::vec3 right_transformed = glm::vec3(RightNode->trans * glm::vec4(rightBox_base[i], 1.0f));
        right_min.x = std::min(right_min.x, right_transformed.x);
        right_min.y = std::min(right_min.y, right_transformed.y);
        right_min.z = std::min(right_min.z, right_transformed.z);
        right_max.x = std::max(right_max.x, right_transformed.x);
        right_max.y = std::max(right_max.y, right_transformed.y);
        right_max.z = std::max(right_max.z, right_transformed.z);
    }
    box leftBox = {
        left_min.x,
        left_max.x,
        left_min.y,
        left_max.y,
        left_min.z,
        left_max.z
    };
    box rightBox = {
        right_min.x,
        right_max.x,
        right_min.y,
        right_max.y,
        right_min.z,
        right_max.z,
    }; */
    // box leftBox = { std::min(left_trans.x - LeftNode->trans[0][0]*leftMult,  left_trans.x + LeftNode->trans[0][0]*leftMult),
    //                 std::max(left_trans.x - LeftNode->trans[0][0]*leftMult,  left_trans.x + LeftNode->trans[0][0]*leftMult),
    //                 std::min(left_trans.y - LeftNode->trans[1][1]*leftMult,  left_trans.y + LeftNode->trans[1][1]*leftMult),
    //                 std::max(left_trans.y - LeftNode->trans[1][1]*leftMult,  left_trans.y + LeftNode->trans[1][1]*leftMult),
    //                 std::min(left_trans.z - LeftNode->trans[2][2]*leftMult,  left_trans.z + LeftNode->trans[2][2]*leftMult),
    //                 std::max(left_trans.z - LeftNode->trans[2][2]*leftMult,  left_trans.z + LeftNode->trans[2][2]*leftMult)};
    // box rightBox = { std::min(right_trans.x - RightNode->trans[0][0]*leftMult,  right_trans.x + RightNode->trans[0][0]*leftMult),
    //                 std::max(right_trans.x - RightNode->trans[0][0]*leftMult,  right_trans.x + RightNode->trans[0][0]*leftMult),
    //                 std::min(right_trans.y - RightNode->trans[1][1]*leftMult,  right_trans.y + RightNode->trans[1][1]*leftMult),
    //                 std::max(right_trans.y - RightNode->trans[1][1]*leftMult,  right_trans.y + RightNode->trans[1][1]*leftMult),
    //                 std::min(right_trans.z - RightNode->trans[2][2]*leftMult,  right_trans.z + RightNode->trans[2][2]*leftMult),
    //                 std::max(right_trans.z - RightNode->trans[2][2]*leftMult,  right_trans.z + RightNode->trans[2][2]*leftMult)};