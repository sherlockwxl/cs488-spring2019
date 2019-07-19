
#include "KeyFrameHandler.hpp"
KeyFrameHandler::KeyFrameHandler(){
    
}

void  KeyFrameHandler::addKeyFrameforLeftHit(AnimationModel &animationModel,int character){
    string keyFrameName = "leftArmHit";


    string s1 = "leftShoulderJoint";
    string s2 = "leftElbow";
    glm::vec2 s1_rotation1 = glm::vec2(1.0f, 0.0f);
    glm::vec2 s1_rotation2 = glm::vec2(0.0f, 0.0f);
    glm::vec2 s1_rotation3 = glm::vec2(-1.4f, 0.0f);
    glm::vec2 s1_rotation4 = glm::vec2(0.0f, 0.0f);

    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5 up arm retive first
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 5, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // retive up arm
    KeyFrame s1_kf4 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    // wait
    KeyFrame s1_kf5 = KeyFrame(keyFrameName, s1, 5, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf6 = KeyFrame(keyFrameName, s1, 5, 1, -1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));

    glm::vec2 s2_rotation1 = glm::vec2(-1.4f, 0.0f);
    glm::vec2 s2_rotation2 = glm::vec2(-1.4f, 0.0f);
    glm::vec2 s2_rotation3 = glm::vec2( 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(keyFrameName, s2, 10, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5
    KeyFrame s2_kf3 = KeyFrame(keyFrameName, s2,  5, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // keep post 5 
    KeyFrame s2_kf4 = KeyFrame(keyFrameName, s2,  15, 1, -1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));

    // retrive
    KeyFrame s2_kf5 = KeyFrame(keyFrameName, s2,  5, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    int size;
    std::vector<SceneNode *> *JointPointers_v;
    std::vector<std::vector<KeyFrame>> *keyFrame_v;

    if(character == 1){
        size = animationModel.JointPointers_v_c1.size();
        JointPointers_v = &animationModel.JointPointers_v_c1;
        keyFrame_v = &animationModel.keyFrame_v_ani_c1;
    }else{
        size = animationModel.JointPointers_v_c2.size();
        JointPointers_v = &animationModel.JointPointers_v_c2;
        keyFrame_v = &animationModel.keyFrame_v_ani_c2;
    }

    for(int i = 0 ; i < size; i ++){
        SceneNode * node = JointPointers_v->at(i);
        if(node->m_name == s1){
            keyFrame_v->at(i).push_back(s1_kf1);
            keyFrame_v->at(i).push_back(s1_kf2);
            keyFrame_v->at(i).push_back(s1_kf3);
            keyFrame_v->at(i).push_back(s1_kf4);
            keyFrame_v->at(i).push_back(s1_kf5);
            keyFrame_v->at(i).push_back(s1_kf6);
        }
        if(node->m_name == s2){ // push for leftElbow
            keyFrame_v->at(i).push_back(s2_kf1);
            keyFrame_v->at(i).push_back(s2_kf2);
            keyFrame_v->at(i).push_back(s2_kf3);
            keyFrame_v->at(i).push_back(s2_kf4);
            keyFrame_v->at(i).push_back(s1_kf5);
        }
    }
    //cout<<"after add size is "<<animationModel.keyFrame_v_ani_c1.size()<<endl;
}


void KeyFrameHandler::addKeyFrameforRunForward(AnimationModel &animationModel,int character){

    string keyFrameName = "run";
    // target nodes
    string s1 = "leftHipJoint";
    string s2 = "leftKnee";
    string s3 = "rightHipJoint";
    string s4 = "rightKnee";


    glm::vec2 s1_rotation1 = glm::vec2(-0.85f, 0.0f);
    glm::vec2 s1_rotation2 = glm::vec2(0.0f, 0.0f);
    glm::vec2 s1_rotation3 = glm::vec2(0.5f, 0.0f);
    glm::vec2 s1_rotation4 = glm::vec2(0.0f, 0.0f);

    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf4 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    glm::vec2 s2_rotation1 = glm::vec2(0.55f, 0.0f);
    glm::vec2 s2_rotation2 = glm::vec2( 0.0f, 0.0f);
    glm::vec2 s2_rotation3 = glm::vec2(0.2f, 0.0f);
    glm::vec2 s2_rotation4 = glm::vec2( 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf3 = KeyFrame(keyFrameName, s2,  5, 1, 1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf4 = KeyFrame(keyFrameName, s2,  15, 1, 1, s2_rotation4, glm::vec3(0.0f, 0.0f,0.0f));




    glm::vec2 s3_rotation1 = glm::vec2(0.5f, 0.0f);
    glm::vec2 s3_rotation2 = glm::vec2(0.0f, 0.0f);
    glm::vec2 s3_rotation3 = glm::vec2(-0.85f, 0.0f);
    glm::vec2 s3_rotation4 = glm::vec2(0.0f, 0.0f);

    KeyFrame s3_kf1 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf2 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf3 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf4 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    glm::vec2 s4_rotation1 = glm::vec2(0.2f, 0.0f);
    glm::vec2 s4_rotation2 = glm::vec2( 0.0f, 0.0f);
    glm::vec2 s4_rotation3 = glm::vec2(0.55f, 0.0f);
    glm::vec2 s4_rotation4 = glm::vec2( 0.0f, 0.0f);


    KeyFrame s4_kf1 = KeyFrame(keyFrameName, s4, 10, 1, 1, s4_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf2 = KeyFrame(keyFrameName, s4, 10, 1, 1, s4_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf3 = KeyFrame(keyFrameName, s4, 10, 1, 1, s4_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf4 = KeyFrame(keyFrameName, s4, 10, 1, 1, s4_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    int size;
    std::vector<SceneNode *> *JointPointers_v;
    std::vector<std::vector<KeyFrame>> *keyFrame_v;

    if(character == 1){
        size = animationModel.JointPointers_v_c1.size();
        JointPointers_v = &animationModel.JointPointers_v_c1;
        keyFrame_v = &animationModel.keyFrame_v_move_c1;
    }else{
        size = animationModel.JointPointers_v_c2.size();
        JointPointers_v = &animationModel.JointPointers_v_c2;
        keyFrame_v = &animationModel.keyFrame_v_move_c2;
    }



    for(int i = 0 ; i < size; i ++){
        SceneNode * node = JointPointers_v->at(i);
        if(node->m_name == s1){
            keyFrame_v->at(i).push_back(s1_kf1);
            keyFrame_v->at(i).push_back(s1_kf2);
            keyFrame_v->at(i).push_back(s1_kf3);
            keyFrame_v->at(i).push_back(s1_kf4);

        }
        if(node->m_name == s2){ // push for leftElbow
            keyFrame_v->at(i).push_back(s2_kf1);
            keyFrame_v->at(i).push_back(s2_kf2);
            keyFrame_v->at(i).push_back(s2_kf3);
            keyFrame_v->at(i).push_back(s2_kf4);
        }
        if(node->m_name == s3){ // push for leftElbow
            keyFrame_v->at(i).push_back(s3_kf1);
            keyFrame_v->at(i).push_back(s3_kf2);
            keyFrame_v->at(i).push_back(s3_kf3);
            keyFrame_v->at(i).push_back(s3_kf4);
        }
        if(node->m_name == s4){ // push for leftElbow
            keyFrame_v->at(i).push_back(s4_kf1);
            keyFrame_v->at(i).push_back(s4_kf2);
            keyFrame_v->at(i).push_back(s4_kf3);
            keyFrame_v->at(i).push_back(s4_kf4);
        }
    }
}

void KeyFrameHandler::stopMovement(AnimationModel &animationModel, int character){
    // target nodes
    string s1 = "leftHipJoint";
    string s2 = "leftKnee";
    string s3 = "rightHipJoint";
    string s4 = "rightKnee";

    

    int size;
    std::vector<SceneNode *> *JointPointers_v;
    std::vector<std::vector<KeyFrame>> *keyFrame_v;
    std::vector<GLfloat>ori_joint_angle;

    if(character == 1){
        size = animationModel.JointPointers_v_c1.size();
        JointPointers_v = &animationModel.JointPointers_v_c1;
        keyFrame_v = &animationModel.keyFrame_v_move_c1;
        ori_joint_angle = animationModel.ori_joint_angle_c1;
    }else{
        size = animationModel.JointPointers_v_c2.size();
        JointPointers_v = &animationModel.JointPointers_v_c2;
        keyFrame_v = &animationModel.keyFrame_v_move_c2;
        ori_joint_angle = animationModel.ori_joint_angle_c2;
    }

    for(int i = 0 ; i < size; i ++){
        SceneNode * node = JointPointers_v->at(i);
        GLfloat ori_angel = ori_joint_angle.at(i);

        glm::vec2 s_rotation = glm::vec2(ori_angel, 0.0f);

        string s = "dummy";
		glm::vec2 rotation = glm::vec2(0.0f, 0.0f);
		KeyFrame kf_dummy = KeyFrame(s, s, 0, 1, 1, rotation, glm::vec3(0.0f, 0.0f,0.0f));

        
        if(node->m_name == s1){
            KeyFrame s_kf_reset = KeyFrame("stopMovement", s1, 10, 1, 1, s_rotation, glm::vec3(0.0f, 0.0f,0.0f));
            keyFrame_v->at(i).clear();
            keyFrame_v->at(i).push_back(kf_dummy);
            keyFrame_v->at(i).push_back(s_kf_reset);
        }
        if(node->m_name == s2){ // push for leftElbow
            KeyFrame s_kf_reset = KeyFrame("stopMovement", s2, 10, 1, 1, s_rotation, glm::vec3(0.0f, 0.0f,0.0f));
            keyFrame_v->at(i).clear();
            keyFrame_v->at(i).push_back(kf_dummy);
            keyFrame_v->at(i).push_back(s_kf_reset);
        }
        if(node->m_name == s3){ // push for leftElbow
            KeyFrame s_kf_reset = KeyFrame("stopMovement", s3, 10, 1, 1, s_rotation, glm::vec3(0.0f, 0.0f,0.0f));
            keyFrame_v->at(i).clear();
            keyFrame_v->at(i).push_back(kf_dummy);
            keyFrame_v->at(i).push_back(s_kf_reset);
        }
        if(node->m_name == s4){ // push for leftElbow
            KeyFrame s_kf_reset = KeyFrame("stopMovement", s4, 10, 1, 1, s_rotation, glm::vec3(0.0f, 0.0f,0.0f));
            keyFrame_v->at(i).clear();
            keyFrame_v->at(i).push_back(kf_dummy);
            keyFrame_v->at(i).push_back(s_kf_reset);
        }
    }


}
