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
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                   // cout<<"prev angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;


                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, *curTargetNode_s, currentKeyFrame_ani.type, currentKeyFrame_ani.order);
                    //cout<<"after angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;
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
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);

                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, *curTargetNode_s, currentKeyFrame_move.type, currentKeyFrame_move.order);

                    durationCont_v_move_c1[i]++;
                }else{
                    keyFrame_v_move_c1[i].erase(keyFrame_v_move_c1[i].begin() + 1);
                    durationCont_v_move_c1[i] = 0;
                }
           }
           
       }
   }

   for(int i = 0 ; i < JointPointers_v_c2.size(); i++){
       SceneNode* curTargetNode_s = JointPointers_v_c2.at(i);
       JointNode * curTargetNode = static_cast<JointNode*>(curTargetNode_s);
       if(i < keyFrame_v_ani_c2.size()){
           vector<KeyFrame> currentKeyFrame_v_ani = keyFrame_v_ani_c2.at(i);
           if(currentKeyFrame_v_ani.size() > 1){
               // when there a re key frames to do
               KeyFrame currentKeyFrame_ani = currentKeyFrame_v_ani.at(1);
              // cout<<"current size: "<<currentKeyFrame_v.size()<<endl;
               // cout<<"name :" + currentKeyFrame.KetFrameName<<endl;
               
               // check if should move to next keyframe
               if(currentKeyFrame_ani.totalTime > durationCont_v_ani_c2.at(i)){
                    // calcualte time left
                    double timeLeft = double(currentKeyFrame_ani.totalTime - durationCont_v_ani_c2.at(i));
                    GLfloat remainRotation_X_perframe = (currentKeyFrame_ani.rotationTarget.x - curTargetNode->m_joint_x.init)/timeLeft;
                    GLfloat remainRotation_Y_perframe = (currentKeyFrame_ani.rotationTarget.y - curTargetNode->m_joint_y.init)/timeLeft;
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                   // cout<<"prev angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;


                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, *curTargetNode_s, currentKeyFrame_ani.type, currentKeyFrame_ani.order);
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
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);

                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, *curTargetNode_s, currentKeyFrame_move.type, currentKeyFrame_move.order);

                    durationCont_v_move_c2[i]++;
                }else{
                    keyFrame_v_move_c2[i].erase(keyFrame_v_move_c2[i].begin() + 1);
                    durationCont_v_move_c2[i] = 0;
                }
           }
           
       }
   }




}

void AnimationModel::rotateJointHelper(GLfloat anglex, GLfloat angley, SceneNode & node, int type, int order){
	
    if(node.m_nodeType == NodeType::JointNode){
        //cout<<"should not "<<endl;
        JointNode * jointNode = static_cast<JointNode*>(&node);
        //cout<<"will ortate " << node.m_name << " ini : "<<jointNode->m_joint_x.init << " and "<< jointNode->m_joint_y.init<<endl;
        GLfloat newAngle_x = jointNode->m_joint_x.init + anglex;
        GLfloat newAngle_y = jointNode->m_joint_y.init + angley;
        //cout<< " newAngle_x :   " << newAngle_x <<" newAngle_y: " << newAngle_y<<endl;
        //cout<< " newAngle_x  limit :   " << jointNode->m_joint_x.max << " and " << jointNode->m_joint_x.min
           // <<" newAngle_y: limit" << jointNode->m_joint_y.max<< " and : " <<jointNode->m_joint_y.min <<endl;



        if((newAngle_x < jointNode->m_joint_x.max) && (newAngle_x > jointNode->m_joint_x.min)
            && 
            (newAngle_y < jointNode->m_joint_y.max) && (newAngle_y > jointNode->m_joint_y.min)){

            //cout<<" will perced"<<endl;
            jointNode->m_joint_x.init = newAngle_x;
            jointNode->m_joint_y.init = newAngle_y;
            glm::mat4 rotateMatrix;
            if(order == 1){
                rotateMatrix = glm::rotate(mat4(), anglex, vec3(1.0f, 0.0f, 0.0f));
                rotateMatrix = glm::rotate(rotateMatrix, angley, vec3(0.0f, 1.0f, 0.0f));
            }else{
                rotateMatrix = glm::rotate(mat4(), angley, vec3(0.0f, 1.0f, 0.0f));
                rotateMatrix = glm::rotate(rotateMatrix, anglex, vec3(1.0f, 0.0f, 0.0f));
            }
            //cout<<"after ortate " << node.m_name << " ini : "<<jointNode->m_joint_x.init << " and "<< jointNode->m_joint_y.init<<endl;
            recursiveRotate(node.trans, node, rotateMatrix);
        }else{

        }
    }

    
	for( SceneNode * nextnode : node.children){
		rotateJointHelper(anglex, angley, *nextnode, type, order);
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