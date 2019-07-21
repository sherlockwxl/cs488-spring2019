
#include "KeyFrameHandler.hpp"
KeyFrameHandler::KeyFrameHandler(){
    
}

int  KeyFrameHandler::addKeyFrameforLeftHit(AnimationModel &animationModel,int character){
    string keyFrameName = "leftArmHit";


    string s1 = "leftShoulderJoint";
    string s2 = "leftElbow";
    if(character == 2){
        s1.append("_baymax");
        s2.append("_baymax");
    }
    glm::vec3 s1_rotation1 = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 s1_rotation2 = glm::vec3(0.01f, 0.01f, 0.01f);
    glm::vec3 s1_rotation3 = glm::vec3(-1.4f, 0.0f, 0.0f);
    glm::vec3 s1_rotation4 = glm::vec3(0.0f, 0.0f, 0.0f);

    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5 up arm retive first
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 5, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // retive up arm
    KeyFrame s1_kf4 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    // wait
    KeyFrame s1_kf5 = KeyFrame(keyFrameName, s1, 5, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf6 = KeyFrame(keyFrameName, s1, 5, 1, -1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));

    glm::vec3 s2_rotation1 = glm::vec3(-1.4f, 0.0f, 0.0f);
    glm::vec3 s2_rotation2 = glm::vec3(-1.4f, 0.0f, 0.0f);
    glm::vec3 s2_rotation3 = glm::vec3( 0.01f, 0.01f, 0.01f);
    glm::vec3 s2_rotation4 = glm::vec3(0.0f, 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(keyFrameName, s2, 10, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5
    KeyFrame s2_kf3 = KeyFrame(keyFrameName, s2,  5, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // keep post 5 
    KeyFrame s2_kf4 = KeyFrame(keyFrameName, s2,  15, 1, -1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));

    // retrive
    KeyFrame s2_kf5 = KeyFrame(keyFrameName, s2,  5, 1, -1, s2_rotation4, glm::vec3(0.0f, 0.0f,0.0f));

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
            keyFrame_v->at(i).push_back(s2_kf5);
        }
    }

    return 45;
    //cout<<"after add size is "<<animationModel.keyFrame_v_ani_c1.size()<<endl;
}


int KeyFrameHandler::addKeyFrameforRunForward(AnimationModel &animationModel,int character){

    string keyFrameName = "run";
    // target nodes
    string s1 = "leftHipJoint";
    string s2 = "leftKnee";
    string s3 = "rightHipJoint";
    string s4 = "rightKnee";
    if(character == 2){
        s1.append("_baymax");
        s2.append("_baymax");
        s3.append("_baymax");
        s4.append("_baymax");
    }

    glm::vec3 s1_rotation1 = glm::vec3(-0.85f, 0.0f, 0.0f);
    glm::vec3 s1_rotation2 = glm::vec3(0.01f, 0.01f, 0.01f);
    glm::vec3 s1_rotation3 = glm::vec3(0.5f, 0.0f, 0.0f);
    glm::vec3 s1_rotation4 = glm::vec3(0.0f, 0.0f, 0.0f);

    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf4 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    glm::vec3 s2_rotation1 = glm::vec3(0.55f, 0.0f, 0.0f);
    glm::vec3 s2_rotation2 = glm::vec3( 0.01f, 0.01f, 0.01f);
    glm::vec3 s2_rotation3 = glm::vec3(0.2f, 0.0f, 0.0f);
    glm::vec3 s2_rotation4 = glm::vec3( 0.0f, 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf3 = KeyFrame(keyFrameName, s2,  5, 1, 1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf4 = KeyFrame(keyFrameName, s2,  15, 1, 1, s2_rotation4, glm::vec3(0.0f, 0.0f,0.0f));




    glm::vec3 s3_rotation1 = glm::vec3(0.5f, 0.0f, 0.0f);
    glm::vec3 s3_rotation2 = glm::vec3(0.01f, 0.01f, 0.01f);
    glm::vec3 s3_rotation3 = glm::vec3(-0.85f, 0.0f, 0.0f);
    glm::vec3 s3_rotation4 = glm::vec3(0.0f, 0.0f, 0.0f);

    KeyFrame s3_kf1 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf2 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf3 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf4 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    glm::vec3 s4_rotation1 = glm::vec3(0.2f, 0.0f, 0.0f);
    glm::vec3 s4_rotation2 = glm::vec3( 0.01f, 0.01f, 0.01f);
    glm::vec3 s4_rotation3 = glm::vec3(0.55f, 0.0f, 0.0f);
    glm::vec3 s4_rotation4 = glm::vec3( 0.0f, 0.0f, 0.0f);


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

    return 40;
}


int  KeyFrameHandler::addKeyFrameforLeftLegHit(AnimationModel &animationModel,int character){
    string keyFrameName = "leftLegHit";


    string s1 = "leftHipJoint";
    string s2 = "leftKnee";
    string s3 = "leftAnkle";

    if(character == 2){
        s1.append("_baymax");
        s2.append("_baymax");
        s3.append("_baymax");
    }


    glm::vec3 s1_rotation1 = glm::vec3(0.1f,  0.2f, -0.5f);

    // testing 


    //testing done
    
    glm::vec3 s1_rotation2 = glm::vec3(-0.7f, 0.2f, -0.3f);
    glm::vec3 s1_rotation3 = glm::vec3(-1.35f, 0.1f, -0.8f);
    glm::vec3 s1_rotation4 = glm::vec3(-1.35f, 0.5f, -0.8f);
    glm::vec3 s1_rotation5 = glm::vec3(-0.7f, 0.5f, -0.8f);
    glm::vec3 s1_rotation6 = glm::vec3(0.0f, 0.5f, -0.7f);
    glm::vec3 s1_rotation7 = glm::vec3(0.0f, 0.0f, 0.0f);


    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5 up arm retive first
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // retive up arm
    KeyFrame s1_kf4 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));

    // wait
    KeyFrame s1_kf5 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation5, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf6 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation6, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf7 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation7, glm::vec3(0.0f, 0.0f,0.0f));
    
    
    glm::vec3 s2_rotation1 = glm::vec3(0.6f, 0.0f, 0.0f);
    glm::vec3 s2_rotation2 = glm::vec3(0.15f, 0.3f, 0.0f);
    glm::vec3 s2_rotation3 = glm::vec3(0.15f, 0.3f, 0.2f);
    glm::vec3 s2_rotation4 = glm::vec3(0.0f, 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(keyFrameName, s2, 40, 1, 1, s2_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5
    KeyFrame s2_kf3 = KeyFrame(keyFrameName, s2,  10, 1, 1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    // keep post 5 
    KeyFrame s2_kf4 = KeyFrame(keyFrameName, s2,  13, 1, 1, s2_rotation4, glm::vec3(0.0f, 0.0f,0.0f));


    glm::vec3 s3_rotation1 = glm::vec3(0.001f, 0.001f, 0.001f);
    glm::vec3 s3_rotation2 = glm::vec3(0.0f, -0.7f, 0.0f);
    glm::vec3 s3_rotation3 = glm::vec3(0.15f, -1.0f, 0.1f);
    glm::vec3 s3_rotation4 = glm::vec3(0.0f, 0.0f, 0.0f);


    KeyFrame s3_kf1 = KeyFrame(keyFrameName, s3, 40, 1, 1, s3_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf2 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5
    KeyFrame s3_kf3 = KeyFrame(keyFrameName, s3,  10, 1, 1, s3_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    // keep post 5 
    KeyFrame s3_kf4 = KeyFrame(keyFrameName, s3,  15, 1, 1, s3_rotation4, glm::vec3(0.0f, 0.0f,0.0f));

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
            keyFrame_v->at(i).push_back(s1_kf7);
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
    }

    return 75;
    //cout<<"after add size is "<<animationModel.keyFrame_v_ani_c1.size()<<endl;
}


int KeyFrameHandler::addKeyFrameforDefend(AnimationModel &animationModel, int character){
    string keyFrameName = "Defend";


    string s1 = "leftShoulderJoint";
    string s2 = "leftElbow";
    string s3 = "rightShoulderJoint";
    string s4 = "rightElbow";
    if(character == 2){
        s1.append("_baymax");
        s2.append("_baymax");
        s3.append("_baymax");
        s4.append("_baymax");
    }

    glm::vec3 s1_rotation1 = glm::vec3(-0.55f, 0.5f, -0.7f);
    glm::vec3 s1_rotation2 = glm::vec3(0.0f, 0.0f, 0.0f);
    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 30, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 60, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    glm::vec3 s2_rotation1 = glm::vec3(-1.8f, 0.1f, 0.2f);
    glm::vec3 s2_rotation2 = glm::vec3(0.0f, 0.0f, 0.0f);
    KeyFrame s2_kf1 = KeyFrame(keyFrameName, s2, 32, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(keyFrameName, s2, 60, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf3 = KeyFrame(keyFrameName, s2, 10, 1, 1, s2_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    glm::vec3 s3_rotation1 = glm::vec3(-0.8f, 0.5f, -0.7f);
    glm::vec3 s3_rotation2 = glm::vec3(0.0f, 0.0f, 0.0f);
    KeyFrame s3_kf1 = KeyFrame(keyFrameName, s3, 30, 1, 1, s3_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf2 = KeyFrame(keyFrameName, s3, 60, 1, 1, s3_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf3 = KeyFrame(keyFrameName, s3, 10, 1, 1, s3_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    glm::vec3 s4_rotation1 = glm::vec3(1.55f, -0.1f, -0.2f);
    glm::vec3 s4_rotation2 = glm::vec3(0.0f, 0.0f, 0.0f);
    KeyFrame s4_kf1 = KeyFrame(keyFrameName, s4, 32, 1, 1, s4_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf2 = KeyFrame(keyFrameName, s4, 60, 1, 1, s4_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf3 = KeyFrame(keyFrameName, s4, 10, 1, 1, s4_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

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
        }
        if(node->m_name == s2){ // push for leftElbow
            keyFrame_v->at(i).push_back(s2_kf1);
            keyFrame_v->at(i).push_back(s2_kf2);
            keyFrame_v->at(i).push_back(s2_kf3);
        }

        if(node->m_name == s3){
            keyFrame_v->at(i).push_back(s3_kf1);
            keyFrame_v->at(i).push_back(s3_kf2);
            keyFrame_v->at(i).push_back(s3_kf3);
        }
        if(node->m_name == s4){ // push for leftElbow
            keyFrame_v->at(i).push_back(s4_kf1);
            keyFrame_v->at(i).push_back(s4_kf2);
            keyFrame_v->at(i).push_back(s4_kf3);
        }
    }

    return 70;
}

int addKeyFrameforFail(AnimationModel &animationModel, int character){
    string keyFrameName = "Fail";


    string s1 = "torso";
    if(character == 2){
        s1.append("_baymax");

    }

    glm::vec3 s1_rotation1 = glm::vec3(-0.55f, 0.5f, -0.7f);
    glm::vec3 s1_rotation2 = glm::vec3(0.0f, 0.0f, 0.0f);
    KeyFrame s1_kf1 = KeyFrame(keyFrameName, s1, 30, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(keyFrameName, s1, 60, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf3 = KeyFrame(keyFrameName, s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

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
        }

    }

    return 70;
}
void KeyFrameHandler::stopMovement(AnimationModel &animationModel, int character){
    // target nodes
    string s1 = "leftHipJoint";
    string s2 = "leftKnee";
    string s3 = "rightHipJoint";
    string s4 = "rightKnee";
    
    if(character == 2){
        s1.append("_baymax");
        s2.append("_baymax");
        s3.append("_baymax");
        s4.append("_baymax");
    }
    

    int size;
    std::vector<SceneNode *> *JointPointers_v;
    std::vector<std::vector<KeyFrame>> *keyFrame_v;
    std::vector<glm::vec3>ori_joint_angle;

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
        glm::vec3 ori_angel = ori_joint_angle.at(i);

        glm::vec3 s_rotation = glm::vec3(ori_angel.x, ori_angel.y, ori_angel.z);

        string s = "dummy";
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
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


void KeyFrameHandler::stopAnimation(AnimationModel &animationModel, int character){
    // target nodes
    string s1 = "leftShoulderJoint";
    string s2 = "leftElbow";

    string s3 = "leftHipJoint";
    string s4 = "leftKnee";
    string s5 = "leftAnkle";


    if(character == 2){
        s1.append("_baymax");
        s2.append("_baymax");
        s3.append("_baymax");
        s4.append("_baymax");
        s5.append("_baymax");
    }
    

    int size;
    std::vector<SceneNode *> *JointPointers_v;
    std::vector<std::vector<KeyFrame>> *keyFrame_v;
    std::vector<glm::vec3>ori_joint_angle;

    if(character == 1){
        size = animationModel.JointPointers_v_c1.size();
        JointPointers_v = &animationModel.JointPointers_v_c1;
        keyFrame_v = &animationModel.keyFrame_v_ani_c1;
        ori_joint_angle = animationModel.ori_joint_angle_c1;
    }else{
        size = animationModel.JointPointers_v_c2.size();
        JointPointers_v = &animationModel.JointPointers_v_c2;
        keyFrame_v = &animationModel.keyFrame_v_ani_c2;
        ori_joint_angle = animationModel.ori_joint_angle_c2;
    }

    for(int i = 0 ; i < size; i ++){
        SceneNode * node = JointPointers_v->at(i);
        glm::vec3 ori_angel = ori_joint_angle.at(i);

        glm::vec3 s_rotation = glm::vec3(ori_angel.x, ori_angel.y, ori_angel.z);

        string s = "dummy";
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
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
        if(node->m_name == s5){ // push for leftElbow
            KeyFrame s_kf_reset = KeyFrame("stopMovement", s5, 10, 1, 1, s_rotation, glm::vec3(0.0f, 0.0f,0.0f));
            keyFrame_v->at(i).clear();
            keyFrame_v->at(i).push_back(kf_dummy);
            keyFrame_v->at(i).push_back(s_kf_reset);
        }

    }
}


