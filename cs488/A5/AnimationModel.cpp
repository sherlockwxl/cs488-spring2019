#include "AnimationModel.hpp"
#include "KeyFrame.hpp"

// TODO: add a movement function buffer
AnimationModel::AnimationModel(){
    
}

void AnimationModel::update(){
   for(int i = 0 ; i < JointPointers_v_c1.size(); i++){
       SceneNode* curTargetNode_s = JointPointers_v_c1.at(i);
       JointNode * curTargetNode = static_cast<JointNode*>(curTargetNode_s);
       if(i < keyFrame_v_ani_c1.size()){
           vector<KeyFrame> currentKeyFrame_v_ani = keyFrame_v_ani_c1.at(i);
           if(currentKeyFrame_v_ani.size() > 1){
               // when there a re key frames to do
               KeyFrame currentKeyFrame_ani = currentKeyFrame_v_ani.at(1);
               
               // check if should move to next keyframe
               if(currentKeyFrame_ani.totalTime > durationCont_v_ani_c1.at(i)){
                    // calcualte time left
                    double timeLeft = double(currentKeyFrame_ani.totalTime - durationCont_v_ani_c1.at(i));
                    GLfloat remainRotation_X_perframe = (currentKeyFrame_ani.rotationTarget.x - curTargetNode->m_joint_x.init)/timeLeft;
                    GLfloat remainRotation_Y_perframe = (currentKeyFrame_ani.rotationTarget.y - curTargetNode->m_joint_y.init)/timeLeft;
                    GLfloat remainRotation_Z_perframe = (currentKeyFrame_ani.rotationTarget.z - curTargetNode->m_joint_z.init)/timeLeft;
                    if(currentKeyFrame_ani.totalTime - durationCont_v_ani_c1.at(i) == 1 && currentKeyFrame_ani.rotationTarget.x == ori_joint_angle_c1.at(i).x
                    && currentKeyFrame_ani.rotationTarget.y == ori_joint_angle_c1.at(i).y && currentKeyFrame_ani.rotationTarget.z == ori_joint_angle_c1.at(i).z){
                        currentKeyFrame_ani.order = 2;
                        //cout<<"joint : "<<curTargetNode_s->m_name <<" will reset"<<endl;
                    }
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                    if(curTargetNode_s->m_name == "leftAnkle"){
                       // cout<<"prev angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;
                    }
                    

                    
                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, remainRotation_Z_perframe, *curTargetNode_s, currentKeyFrame_ani.type, currentKeyFrame_ani.order, i, 1);
                    if(curTargetNode_s->m_name == "leftAnkle"){
                       // cout<<"target angle : "<<currentKeyFrame_ani.rotationTarget<<endl;
                       // cout<<"after angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;
                    }
                    
                    durationCont_v_ani_c1[i]++;
                }else{
                    keyFrame_v_ani_c1[i].erase(keyFrame_v_ani_c1[i].begin() + 1);
                    durationCont_v_ani_c1[i] = 0;
                }
           }
           
       }

       if(i < keyFrame_v_move_c1.size()){
           vector<KeyFrame> currentKeyFrame_v_move = keyFrame_v_move_c1.at(i);
           if(currentKeyFrame_v_move.size() > 1){
               // when there a re key frames to do
               KeyFrame currentKeyFrame_move = currentKeyFrame_v_move.at(1);

               // check if should move to next keyframe
               if(currentKeyFrame_move.totalTime > durationCont_v_move_c1.at(i)){
                    // calcualte time left
                    double timeLeft = double(currentKeyFrame_move.totalTime - durationCont_v_move_c1.at(i));
                    GLfloat remainRotation_X_perframe = (currentKeyFrame_move.rotationTarget.x - curTargetNode->m_joint_x.init)/timeLeft;
                    GLfloat remainRotation_Y_perframe = (currentKeyFrame_move.rotationTarget.y - curTargetNode->m_joint_y.init)/timeLeft;
                    GLfloat remainRotation_Z_perframe = (currentKeyFrame_move.rotationTarget.z - curTargetNode->m_joint_z.init)/timeLeft;
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                    if(currentKeyFrame_move.totalTime - durationCont_v_move_c1.at(i) == 1 && currentKeyFrame_move.rotationTarget.x == ori_joint_angle_c1.at(i).x
                    && currentKeyFrame_move.rotationTarget.y == ori_joint_angle_c1.at(i).y && currentKeyFrame_move.rotationTarget.z == ori_joint_angle_c1.at(i).z){
                        currentKeyFrame_move.order = 2;
                       // cout<<"joint : "<<curTargetNode_s->m_name <<" will reset"<<endl;
                    }
                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, remainRotation_Z_perframe, *curTargetNode_s, currentKeyFrame_move.type, currentKeyFrame_move.order, i, 1);

                    durationCont_v_move_c1[i]++;
                }else{
                    keyFrame_v_move_c1[i].erase(keyFrame_v_move_c1[i].begin() + 1);
                    durationCont_v_move_c1[i] = 0;
                }
           }
           
       }
   }

   for(int i = 0 ; i < JointPointers_v_c2.size(); i++){
       //cout<<"run 1"<<endl;
       SceneNode* curTargetNode_s = JointPointers_v_c2.at(i);
       JointNode * curTargetNode = static_cast<JointNode*>(curTargetNode_s);
       if(i < keyFrame_v_ani_c2.size()){
           //cout<<"run 2"<<endl;
           vector<KeyFrame> currentKeyFrame_v_ani = keyFrame_v_ani_c2.at(i);
           if(currentKeyFrame_v_ani.size() > 1){
               // when there a re key frames to do
               KeyFrame currentKeyFrame_ani = currentKeyFrame_v_ani.at(1);
               //cout<<"current size: "<<currentKeyFrame_v_ani.size()<<endl;
                //cout<<"name :" + currentKeyFrame_ani.KeyFrameName<<endl;
               
               // check if should move to next keyframe
               if(currentKeyFrame_ani.totalTime > durationCont_v_ani_c2.at(i)){
                    // calcualte time left
                    double timeLeft = double(currentKeyFrame_ani.totalTime - durationCont_v_ani_c2.at(i));
                    GLfloat remainRotation_X_perframe = (currentKeyFrame_ani.rotationTarget.x - curTargetNode->m_joint_x.init)/timeLeft;
                    GLfloat remainRotation_Y_perframe = (currentKeyFrame_ani.rotationTarget.y - curTargetNode->m_joint_y.init)/timeLeft;
                    GLfloat remainRotation_Z_perframe = (currentKeyFrame_ani.rotationTarget.z - curTargetNode->m_joint_z.init)/timeLeft;
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                    if(currentKeyFrame_ani.totalTime - durationCont_v_ani_c2.at(i) == 1 && currentKeyFrame_ani.rotationTarget.x == ori_joint_angle_c2.at(i).x
                    && currentKeyFrame_ani.rotationTarget.y == ori_joint_angle_c2.at(i).y && currentKeyFrame_ani.rotationTarget.z == ori_joint_angle_c2.at(i).z){
                        currentKeyFrame_ani.order = 2;
                        //cout<<"joint : "<<curTargetNode_s->m_name <<" will reset"<<endl;
                    }
                   // cout<<"prev angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;

                    if(currentKeyFrame_ani.rotationTarget.x != 0.001f){
                        rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, remainRotation_Z_perframe, *curTargetNode_s, currentKeyFrame_ani.type, currentKeyFrame_ani.order, i, 2);
                    }
                    //cout<<"after angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;
                    durationCont_v_ani_c2[i]++;
                }else{
                    keyFrame_v_ani_c2[i].erase(keyFrame_v_ani_c2[i].begin() + 1);
                    durationCont_v_ani_c2[i] = 0;
                }
           }
           
       }

       if(i < keyFrame_v_move_c2.size()){
           vector<KeyFrame> currentKeyFrame_v_move = keyFrame_v_move_c2.at(i);
           if(currentKeyFrame_v_move.size() > 1){
               // when there a re key frames to do
               KeyFrame currentKeyFrame_move = currentKeyFrame_v_move.at(1);

               // check if should move to next keyframe
               if(currentKeyFrame_move.totalTime > durationCont_v_move_c2.at(i)){
                    // calcualte time left
                    double timeLeft = double(currentKeyFrame_move.totalTime - durationCont_v_move_c2.at(i));
                    GLfloat remainRotation_X_perframe = (currentKeyFrame_move.rotationTarget.x - curTargetNode->m_joint_x.init)/timeLeft;
                    GLfloat remainRotation_Y_perframe = (currentKeyFrame_move.rotationTarget.y - curTargetNode->m_joint_y.init)/timeLeft;
                    GLfloat remainRotation_Z_perframe = (currentKeyFrame_move.rotationTarget.z - curTargetNode->m_joint_z.init)/timeLeft;
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                    if(currentKeyFrame_move.totalTime - durationCont_v_move_c2.at(i) == 1 && currentKeyFrame_move.rotationTarget.x == ori_joint_angle_c2.at(i).x
                    && currentKeyFrame_move.rotationTarget.y == ori_joint_angle_c2.at(i).y && currentKeyFrame_move.rotationTarget.z == ori_joint_angle_c2.at(i).z){
                        currentKeyFrame_move.order = 2;
                       // cout<<"joint : "<<curTargetNode_s->m_name <<" will reset"<<endl;
                    }
                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, remainRotation_Z_perframe, *curTargetNode_s, currentKeyFrame_move.type, currentKeyFrame_move.order, i, 2);

                    durationCont_v_move_c2[i]++;
                }else{
                    keyFrame_v_move_c2[i].erase(keyFrame_v_move_c2[i].begin() + 1);
                    durationCont_v_move_c2[i] = 0;
                }
           }
           
       }
   }




}

void AnimationModel::rotateJointHelper(GLfloat anglex, GLfloat angley,GLfloat anglez,SceneNode & node, int type, int order, int id, int characterId){
	
    if(node.m_nodeType == NodeType::JointNode){
        //cout<<"should not "<<endl;
        JointNode * jointNode = static_cast<JointNode*>(&node);
        if(node.m_name == "leftAnkle"){
            //cout<<"will ortate " << node.m_name << " ini : "<<jointNode->m_joint_x.init << " and "<< jointNode->m_joint_y.init<<jointNode->m_joint_z.init<<endl;
            //cout<<" current trans:"<<node.trans<<endl;
        }
        
        GLfloat newAngle_x = jointNode->m_joint_x.init + anglex;
        GLfloat newAngle_y = jointNode->m_joint_y.init + angley;
        GLfloat newAngle_z = jointNode->m_joint_z.init + anglez;
        /* cout<< " newAngle_x :   " << newAngle_x <<" newAngle_y: " << newAngle_y<<" newAngle_z: " << newAngle_z<<endl;
        cout<< " newAngle_x  limit :   " << jointNode->m_joint_x.max << " and " << jointNode->m_joint_x.min
            <<" newAngle_y: limit" << jointNode->m_joint_y.max<< " and : " <<jointNode->m_joint_y.min
            <<" newAngle_z: limit" << jointNode->m_joint_z.max<< " and : " <<jointNode->m_joint_z.min <<endl; */

        //exit(0);

        if((newAngle_x <= jointNode->m_joint_x.max) && (newAngle_x >= jointNode->m_joint_x.min)
            && 
            (newAngle_y <= jointNode->m_joint_y.max) && (newAngle_y >= jointNode->m_joint_y.min)
            && (newAngle_z <= jointNode->m_joint_z.max) && (newAngle_z >= jointNode->m_joint_z.min)){

            jointNode->m_joint_x.init = newAngle_x;
            jointNode->m_joint_y.init = newAngle_y;
            jointNode->m_joint_z.init = newAngle_z;
            glm::mat4 rotateMatrix;
            if(order == 1){
                rotateMatrix = glm::rotate(mat4(), anglex, vec3(1.0f, 0.0f, 0.0f));
                rotateMatrix = glm::rotate(rotateMatrix, angley, vec3(0.0f, 1.0f, 0.0f));
                rotateMatrix = glm::rotate(rotateMatrix, anglez, vec3(0.0f, 0.0f, 1.0f));
            }else if(order == -1){
                rotateMatrix = glm::rotate(mat4(), angley, vec3(0.0f, 1.0f, 0.0f));
                rotateMatrix = glm::rotate(rotateMatrix, anglex, vec3(1.0f, 0.0f, 0.0f));
                rotateMatrix = glm::rotate(rotateMatrix, anglez, vec3(0.0f, 0.0f, 1.0f));
            }else{
                if(characterId == 1){
                    //cout<<" target name is :"<<node.m_name<<" ori trans is : "<<ori_joint_trans_c1.at(id)<<endl;
                    //cout<<" cur trans is : "<<node.trans<<endl;
                    rotateMatrix = glm::inverse(node.trans) * ori_joint_trans_c1.at(id);
                    rotateMatrix[3][0] = 0.0f;
                    rotateMatrix[3][1] = 0.0f;
                    rotateMatrix[3][2] = 0.0f;
                    //cout<<" matrix is :"<<rotateMatrix<<endl;
                }else{
                    rotateMatrix = glm::inverse(node.trans) * ori_joint_trans_c2.at(id);
                    rotateMatrix[3][0] = 0.0f;
                    rotateMatrix[3][1] = 0.0f;
                    rotateMatrix[3][2] = 0.0f;
                }
                
            }
            
            recursiveRotate(node.trans, node, rotateMatrix);
            if(node.m_name == "leftAnkle"){
                //cout<<"after ortate " << node.m_name << " ini : "<<jointNode->m_joint_x.init << " and "<< jointNode->m_joint_y.init<<endl;
                //cout<<" after trans:"<<node.trans<<endl;
            }
        }else{
           /*  cout<<"node name : "<<node.m_name<<endl;
              cout<< " newAngle_x :   " << newAngle_x <<" newAngle_y: " << newAngle_y<<" newAngle_z: " << newAngle_z<<endl;
            cout<< " newAngle_x  limit :   " << jointNode->m_joint_x.max << " and " << jointNode->m_joint_x.min
            <<" newAngle_y: limit" << jointNode->m_joint_y.max<< " and : " <<jointNode->m_joint_y.min
            <<" newAngle_z: limit" << jointNode->m_joint_z.max<< " and : " <<jointNode->m_joint_z.min <<endl; 
 */
        }
    }

    
	for( SceneNode * nextnode : node.children){
		rotateJointHelper(anglex, angley, anglez, *nextnode, type, order, id, characterId);
	}
	
}

void AnimationModel::recursiveRotate(glm::mat4 revserseTargetMatrix, SceneNode& root, glm::mat4 rotatematrix) {
    //cout<<"rotation actually called"<<endl;
    //exit(0);
	glm::mat4 revserseMatrix = glm::inverse(revserseTargetMatrix);
	root.trans = revserseTargetMatrix*rotatematrix*revserseMatrix*root.trans;
	for(SceneNode* node: root.children) {
		recursiveRotate(revserseTargetMatrix, *node, rotatematrix);
	}
}


int AnimationModel::getCurrentStatus(int character_id){
    if(character_id == 1){
         for(int i = 0 ; i < JointPointers_v_c1.size(); i++){
            SceneNode* curTargetNode_s = JointPointers_v_c1.at(i);
            JointNode * curTargetNode = static_cast<JointNode*>(curTargetNode_s);
            if(i < keyFrame_v_ani_c1.size()){
                vector<KeyFrame> currentKeyFrame_v_ani = keyFrame_v_ani_c1.at(i);
                if(currentKeyFrame_v_ani.size() > 1){
                    // when there a re key frames to do
                    KeyFrame currentKeyFrame_ani = currentKeyFrame_v_ani.at(1);
                    
                   if(currentKeyFrame_ani.KeyFrameName == "leftArmHit" || currentKeyFrame_ani.KeyFrameName == "leftLegHit"){
                       return -1;
                   }else if(currentKeyFrame_ani.KeyFrameName=="Defend"){
                       return 1;
                   }
                }
           
            }

        }

        return 0;
    }else{
         for(int i = 0 ; i < JointPointers_v_c2.size(); i++){
            SceneNode* curTargetNode_s = JointPointers_v_c2.at(i);
            JointNode * curTargetNode = static_cast<JointNode*>(curTargetNode_s);
            if(i < keyFrame_v_ani_c2.size()){
                vector<KeyFrame> currentKeyFrame_v_ani = keyFrame_v_ani_c2.at(i);
                if(currentKeyFrame_v_ani.size() > 1){
                    // when there a re key frames to do
                    KeyFrame currentKeyFrame_ani = currentKeyFrame_v_ani.at(1);
                    
                   if(currentKeyFrame_ani.KeyFrameName == "leftArmHit"||currentKeyFrame_ani.KeyFrameName == "leftLegHit"){
                       return -1;
                   }else if(currentKeyFrame_ani.KeyFrameName=="Defend"){
                       return 1;
                   }
                }
           
            }

        }

        return 0;
    }
}