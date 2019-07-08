#include "AnimationModel.hpp"
#include "KeyFrame.hpp"
AnimationModel::AnimationModel(){
    
}

void AnimationModel::update(){
   for(int i = 0 ; i < JointPointers_v.size(); i++){
       SceneNode* curTargetNode_s = JointPointers_v.at(i);
       JointNode * curTargetNode = static_cast<JointNode*>(curTargetNode_s);
       if(i < keyFrame_v.size()){
           vector<KeyFrame> currentKeyFrame_v = keyFrame_v.at(i);
           if(currentKeyFrame_v.size() > 1){
               // when there a re key frames to do
               KeyFrame currentKeyFrame = currentKeyFrame_v.at(1);
              // cout<<"current size: "<<currentKeyFrame_v.size()<<endl;
               // cout<<"name :" + currentKeyFrame.KetFrameName<<endl;
               
               // check if should move to next keyframe
               if(currentKeyFrame.totalTime > durationCont_v.at(i)){
                    // calcualte time left
                    double timeLeft = double(currentKeyFrame.totalTime - durationCont_v.at(i));
                    GLfloat remainRotation_X_perframe = (currentKeyFrame.rotationTarget.x - curTargetNode->m_joint_x.init)/timeLeft;
                    GLfloat remainRotation_Y_perframe = (currentKeyFrame.rotationTarget.y - curTargetNode->m_joint_y.init)/timeLeft;
                    JointNode * jointNode = static_cast<JointNode*>(curTargetNode_s);
                   // cout<<"prev angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;


                    rotateJointHelper(remainRotation_X_perframe, remainRotation_Y_perframe, *curTargetNode_s, currentKeyFrame.type, currentKeyFrame.order);
                    //cout<<"after angle"<<jointNode->m_joint_x.init << " and " << jointNode->m_joint_y.init<<endl;
                    durationCont_v[i]++;
                }else{
                    keyFrame_v[i].erase(keyFrame_v[i].begin() + 1);
                    durationCont_v[i] = 0;
                }
           }
           
       }
   }

}

void AnimationModel::rotateJointHelper(GLfloat anglex, GLfloat angley, SceneNode & node, int type, int order){
	
    if(node.m_nodeType == NodeType::JointNode){
        //cout<<"should not "<<endl;
        JointNode * jointNode = static_cast<JointNode*>(&node);
        cout<<"will ortate " << node.m_name << " ini : "<<jointNode->m_joint_x.init << " and "<< jointNode->m_joint_y.init<<endl;
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
            cout<<"after ortate " << node.m_name << " ini : "<<jointNode->m_joint_x.init << " and "<< jointNode->m_joint_y.init<<endl;
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