
#include "KeyFrameHandler.hpp"
KeyFrameHandler::KeyFrameHandler(){
    
}

void  KeyFrameHandler::addKeyFrameforLeftHit(AnimationModel &animationModel){
    cout<<"left hit called"<<endl;
    string s1 = "leftShoulderJoint";
    string s2 = "leftElbow";
    glm::vec2 s1_rotation1 = glm::vec2(1.0f, 0.0f);
    glm::vec2 s1_rotation2 = glm::vec2(0.0f, 0.0f);
    glm::vec2 s1_rotation3 = glm::vec2(-1.4f, 0.0f);
    glm::vec2 s1_rotation4 = glm::vec2(0.0f, 0.0f);

    KeyFrame s1_kf1 = KeyFrame(s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5 up arm retive first
    KeyFrame s1_kf3 = KeyFrame(s1, 5, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // retive up arm
    KeyFrame s1_kf4 = KeyFrame(s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));

    // wait
    KeyFrame s1_kf5 = KeyFrame(s1, 5, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf6 = KeyFrame(s1, 5, 1, -1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));

    glm::vec2 s2_rotation1 = glm::vec2(-1.4f, 0.0f);
    glm::vec2 s2_rotation2 = glm::vec2(-1.4f, 0.0f);
    glm::vec2 s2_rotation3 = glm::vec2( 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(s2, 10, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // wait 5
    KeyFrame s2_kf3 = KeyFrame(s2,  5, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    // keep post 5 
    KeyFrame s2_kf4 = KeyFrame(s2,  15, 1, -1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));

    // retrive
    KeyFrame s2_kf5 = KeyFrame(s2,  5, 1, -1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));

    for(int i = 0 ; i < animationModel.JointPointers_v.size(); i ++){
        SceneNode * node = animationModel.JointPointers_v.at(i);
        if(node->m_name == s1){
            animationModel.keyFrame_v.at(i).push_back(s1_kf1);
            animationModel.keyFrame_v.at(i).push_back(s1_kf2);
            animationModel.keyFrame_v.at(i).push_back(s1_kf3);
            animationModel.keyFrame_v.at(i).push_back(s1_kf4);
            animationModel.keyFrame_v.at(i).push_back(s1_kf5);
            animationModel.keyFrame_v.at(i).push_back(s1_kf6);
        }
        if(node->m_name == s2){ // push for leftElbow
            animationModel.keyFrame_v.at(i).push_back(s2_kf1);
            animationModel.keyFrame_v.at(i).push_back(s2_kf2);
            animationModel.keyFrame_v.at(i).push_back(s2_kf3);
            animationModel.keyFrame_v.at(i).push_back(s2_kf4);
            animationModel.keyFrame_v.at(i).push_back(s1_kf5);
        }
    }
}


void KeyFrameHandler::addKeyFrameforRunForward(AnimationModel &animationModel){

    // target nodes
    string s1 = "leftHipJoint";
    string s2 = "leftKnee";
    string s3 = "rightHipJoint";
    string s4 = "rightKnee";


    glm::vec2 s1_rotation1 = glm::vec2(-0.85f, 0.0f);
    glm::vec2 s1_rotation2 = glm::vec2(0.0f, 0.0f);
    glm::vec2 s1_rotation3 = glm::vec2(0.5f, 0.0f);
    glm::vec2 s1_rotation4 = glm::vec2(0.0f, 0.0f);

    KeyFrame s1_kf1 = KeyFrame(s1, 10, 1, 1, s1_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf2 = KeyFrame(s1, 10, 1, 1, s1_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf3 = KeyFrame(s1, 10, 1, 1, s1_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s1_kf4 = KeyFrame(s1, 10, 1, 1, s1_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    glm::vec2 s2_rotation1 = glm::vec2(0.55f, 0.0f);
    glm::vec2 s2_rotation2 = glm::vec2( 0.0f, 0.0f);
    glm::vec2 s2_rotation3 = glm::vec2(0.2f, 0.0f);
    glm::vec2 s2_rotation4 = glm::vec2( 0.0f, 0.0f);


    KeyFrame s2_kf1 = KeyFrame(s2, 10, 1, 1, s2_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf2 = KeyFrame(s2, 10, 1, 1, s2_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf3 = KeyFrame(s2,  5, 1, 1, s2_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s2_kf4 = KeyFrame(s2,  15, 1, 1, s2_rotation4, glm::vec3(0.0f, 0.0f,0.0f));




    glm::vec2 s3_rotation1 = glm::vec2(0.5f, 0.0f);
    glm::vec2 s3_rotation2 = glm::vec2(0.0f, 0.0f);
    glm::vec2 s3_rotation3 = glm::vec2(-0.85f, 0.0f);
    glm::vec2 s3_rotation4 = glm::vec2(0.0f, 0.0f);

    KeyFrame s3_kf1 = KeyFrame(s3, 10, 1, 1, s3_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf2 = KeyFrame(s3, 10, 1, 1, s3_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf3 = KeyFrame(s3, 10, 1, 1, s3_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s3_kf4 = KeyFrame(s3, 10, 1, 1, s3_rotation4, glm::vec3(0.0f, 0.0f,0.0f));



    glm::vec2 s4_rotation1 = glm::vec2(0.2f, 0.0f);
    glm::vec2 s4_rotation2 = glm::vec2( 0.0f, 0.0f);
    glm::vec2 s4_rotation3 = glm::vec2(0.55f, 0.0f);
    glm::vec2 s4_rotation4 = glm::vec2( 0.0f, 0.0f);


    KeyFrame s4_kf1 = KeyFrame(s4, 10, 1, 1, s4_rotation1, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf2 = KeyFrame(s4, 10, 1, 1, s4_rotation2, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf3 = KeyFrame(s4, 10, 1, 1, s4_rotation3, glm::vec3(0.0f, 0.0f,0.0f));
    KeyFrame s4_kf4 = KeyFrame(s4, 10, 1, 1, s4_rotation4, glm::vec3(0.0f, 0.0f,0.0f));





    for(int i = 0 ; i < animationModel.JointPointers_v.size(); i ++){
        SceneNode * node = animationModel.JointPointers_v.at(i);
        if(node->m_name == s1){
            animationModel.keyFrame_v.at(i).push_back(s1_kf1);
            animationModel.keyFrame_v.at(i).push_back(s1_kf2);
            animationModel.keyFrame_v.at(i).push_back(s1_kf3);
            animationModel.keyFrame_v.at(i).push_back(s1_kf4);

        }
        if(node->m_name == s2){ // push for leftElbow
            animationModel.keyFrame_v.at(i).push_back(s2_kf1);
            animationModel.keyFrame_v.at(i).push_back(s2_kf2);
            animationModel.keyFrame_v.at(i).push_back(s2_kf3);
            animationModel.keyFrame_v.at(i).push_back(s2_kf4);
        }
        if(node->m_name == s3){ // push for leftElbow
            animationModel.keyFrame_v.at(i).push_back(s3_kf1);
            animationModel.keyFrame_v.at(i).push_back(s3_kf2);
            animationModel.keyFrame_v.at(i).push_back(s3_kf3);
            animationModel.keyFrame_v.at(i).push_back(s3_kf4);
        }
        if(node->m_name == s4){ // push for leftElbow
            animationModel.keyFrame_v.at(i).push_back(s4_kf1);
            animationModel.keyFrame_v.at(i).push_back(s4_kf2);
            animationModel.keyFrame_v.at(i).push_back(s4_kf3);
            animationModel.keyFrame_v.at(i).push_back(s4_kf4);
        }
    }
}