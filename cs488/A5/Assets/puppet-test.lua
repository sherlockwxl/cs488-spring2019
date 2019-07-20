-- puppet.lua
-- A simplified puppet without posable joints, but that
-- looks roughly humanoid.

rootnode = gr.node('root')

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 10)
green = gr.material({0.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
darkgray = gr.material({0.25, 0.29, 0.30}, {0.1, 0.1, 0.1}, 10)

-- add a platform

platform = gr.mesh('cube', 'platform', 2)
rootnode:add_child(platform)
platform:scale(25.0, 25.0, 0.5)
platform:translate(0.0, 0.0, 5.0)
platform:rotate('x',90)
platform:set_material(darkgray)

platform_back = gr.mesh('cube', 'platform_back')
rootnode:add_child(platform_back)
platform_back:scale(25.0, 25.0, 0.1)
platform_back:translate(0.0, 0.0, -12.0)
platform_back:set_material(darkgray)

torso = gr.mesh('sphere', 'torso')
rootnode:add_child(torso)
torso:scale(0.5, 0.8, 0.5)
torso:translate(0.0, 0.0, 0.0)
torso:set_material(blue)

neckJoint = gr.joint('neckJoint', {0, 0, 3.14/8}, {-3.14/8, 0, 3.14/8},{-3.14/4, 0, 3.14/4})
torso:add_child(neckJoint)
neckJoint:translate(0.0, 0.7, 0.0)

neck = gr.mesh('sphere', 'neck')
neckJoint:add_child(neck)
neck:scale(0.15, 0.4, 0.15)
neck:translate(0.0, 1.1, 0.0)
neck:set_material(white)

headJoint = gr.joint('headJoint', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4},{-3.14/4, 0, 3.14/4})
neck:add_child(headJoint)
headJoint:translate(0.0, 1.2, 0.0)

head = gr.mesh('sphere', 'head')
headJoint:add_child(head)
head:scale(0.4, 0.4, 0.4)
head:translate(0.0, 1.4, 0.0)
head:set_material(white)

leftEye = gr.mesh('sphere', 'leftEye')
head:add_child(leftEye)
leftEye:scale(0.1, 0.1, 0.1)
leftEye:translate(-0.2, 1.4, 0.35)
leftEye:set_material(black)

rightEye = gr.mesh('sphere', 'rightEye')
head:add_child(rightEye)
rightEye:scale(0.1, 0.1, 0.1)
rightEye:translate(0.2, 1.4, 0.35)
rightEye:set_material(black)

leftShoulder = gr.mesh('sphere', 'leftShoulder')
torso:add_child(leftShoulder)
leftShoulder:scale(0.4, 0.2, 0.4)
leftShoulder:translate(-0.4, 0.8, 0.0)
leftShoulder:set_material(blue)

leftShoulderJoint = gr.joint('leftShoulderJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
leftShoulder:add_child(leftShoulderJoint)
leftShoulderJoint:translate(-0.65, 0.8, 0.0)

leftUpArm = gr.mesh('sphere', 'leftUpArm')
leftShoulderJoint:add_child(leftUpArm)
leftUpArm:scale(0.2, 0.4, 0.2)
leftUpArm:translate(-0.65, 0.5, 0.0)
leftUpArm:set_material(green)

leftElbow = gr.joint('leftElbow', {-3.14, 0, 3.14}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
leftUpArm:add_child(leftElbow)
leftElbow:translate(-0.65, 0.15, 0.0)

leftDownArm = gr.mesh('sphere', 'leftDownArm')
leftElbow:add_child(leftDownArm)
leftDownArm:scale(0.15, 0.3, 0.15)
leftDownArm:translate(-0.65, -0.1, 0.0)
leftDownArm:set_material(green)

leftWrist = gr.joint('leftWrist', {-3.14/4, 0, 3.14/4}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
leftDownArm:add_child(leftWrist)
leftWrist:translate(-0.65, -0.35, 0.0)

leftHand = gr.mesh('sphere', 'leftHand')
leftWrist:add_child(leftHand)
leftHand:scale(0.1, 0.1, 0.1)
leftHand:translate(-0.65, -0.45, 0.0)
leftHand:set_material(green)

rightShoulder = gr.mesh('sphere', 'rightShoulder')
torso:add_child(rightShoulder)
rightShoulder:scale(0.4, 0.2, 0.4)
rightShoulder:translate(0.4, 0.8, 0.0)
rightShoulder:set_material(blue)

rightShoulderJoint = gr.joint('rightShoulderJoint', {-3.14, 0, 3.14/2}, {-3.14/2, 0, 3.14/2},{-3.14/4, 0, 3.14/4})
rightShoulder:add_child(rightShoulderJoint)
rightShoulderJoint:translate(0.65, 0.8, 0.0)

rightUpArm = gr.mesh('sphere', 'rightUpArm')
rightShoulderJoint:add_child(rightUpArm)
rightUpArm:scale(0.2, 0.4, 0.2)
rightUpArm:translate(0.65, 0.5, 0.0)
rightUpArm:set_material(green)

rightElbow = gr.joint('rightElbow', {-3.14/2, 0, 0}, {-3.14/2, 0, 3.14/2},{-3.14/4, 0, 3.14/4})
rightUpArm:add_child(rightElbow)
rightElbow:translate(0.65, 0.15, 0.0)

rightDownArm = gr.mesh('sphere', 'rightDownArm')
rightElbow:add_child(rightDownArm)
rightDownArm:scale(0.15, 0.3, 0.15)
rightDownArm:translate(0.65, -0.1, 0.0)
rightDownArm:set_material(green)

rightWrist = gr.joint('rightWrist', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4},{-3.14/4, 0, 3.14/4})
rightDownArm:add_child(rightWrist)
rightWrist:translate(0.65, -0.35, 0.0)

rightHand = gr.mesh('sphere', 'rightHand')
rightWrist:add_child(rightHand)
rightHand:scale(0.1, 0.1, 0.1)
rightHand:translate(0.65, -0.45, 0.0)
rightHand:set_material(green)

leftHip = gr.mesh('sphere', 'leftHip')
torso:add_child(leftHip)
leftHip:scale(0.25, 0.25, 0.25)
leftHip:translate(-0.3, -0.7, 0.0)
leftHip:set_material(red)

leftHipJoint = gr.joint('leftHipJoint', {-3.14/2, 0, 3.14/4}, {-3.14/4, 0, 3.14/4},{-3.14/4, 0, 3.14/4})
leftHip:add_child(leftHipJoint)
leftHipJoint:translate(-0.3, -0.9, 0.0)

leftUpLeg = gr.mesh('sphere', 'leftUpLeg')
leftHipJoint:add_child(leftUpLeg)
leftUpLeg:scale(0.2, 0.5, 0.2)
leftUpLeg:translate(-0.3, -1.2, 0.0)
leftUpLeg:set_material(red)

leftKnee = gr.joint('leftKnee', {0, 0, 3.14/2}, {-3.14, 0, 3.14},{-3.14, 0, 3.14})
leftUpLeg:add_child(leftKnee)
leftKnee:translate(-0.3, -1.65, 0.0)

leftDownLeg = gr.mesh('sphere', 'leftDownLeg')
leftKnee:add_child(leftDownLeg)
leftDownLeg:scale(0.2, 0.4, 0.2)
leftDownLeg:translate(-0.3, -2.0, 0.0)
leftDownLeg:set_material(red)

leftAnkle = gr.joint('leftAnkle', {-3.14/2, 0, 3.14/2}, {-3.14/2, 0, 3.14/2},{-3.14/4, 0, 3.14/4})
leftDownLeg:add_child(leftAnkle)
leftAnkle:translate(-0.3, -2.3, 0.0)

leftFoot = gr.mesh('cube', 'leftFoot')
leftAnkle:add_child(leftFoot)
leftFoot:scale(0.3, 0.2, 0.5)
leftFoot:translate(-0.3, -2.4, 0.2)
leftFoot:set_material(red)

rightHip = gr.mesh('sphere', 'rightHip')
torso:add_child(rightHip)
rightHip:scale(0.25, 0.25, 0.25)
rightHip:translate(0.3, -0.7, 0.0)
rightHip:set_material(red)

rightHipJoint = gr.joint('rightHipJoint', {-3.14/2, 0, 3.14/4}, {-3.14/4, 0, 3.14/4},{-3.14/4, 0, 3.14/4})
rightHip:add_child(rightHipJoint)
rightHipJoint:translate(0.3, -0.9, 0.0)

rightUpLeg = gr.mesh('sphere', 'rightUpLeg')
rightHipJoint:add_child(rightUpLeg)
rightUpLeg:scale(0.2, 0.5, 0.2)
rightUpLeg:translate(0.3, -1.2, 0.0)
rightUpLeg:set_material(red)

rightKnee = gr.joint('rightKnee', {0, 0, 3.14/2}, {-3.14/4, 0, 3.14/4},{-3.14/4, 0, 3.14/4})
rightUpLeg:add_child(rightKnee)
rightKnee:translate(0.3, -1.65, 0.0)

rightDownLeg = gr.mesh('sphere', 'rightDownLeg')
rightKnee:add_child(rightDownLeg)
rightDownLeg:scale(0.2, 0.4, 0.2)
rightDownLeg:translate(0.3, -2.0, 0.0)
rightDownLeg:set_material(red)

rightAnkle = gr.joint('rightAnkle', {-3.14/8, 0, 3.14/8}, {-3.14/8, 0, 3.14/8},{-3.14/4, 0, 3.14/4})
rightDownLeg:add_child(rightAnkle)
rightAnkle:translate(0.3, -2.3, 0.0)

rightFoot = gr.mesh('cube', 'rightFoot')
rightAnkle:add_child(rightFoot)
rightFoot:scale(0.3, 0.2, 0.5)
rightFoot:translate(0.3, -2.4, 0.2)
rightFoot:set_material(red)

-- add second puppet





brown = gr.material({0.36, 0.27, 0.06}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
lightBlue = gr.material({0.43, 0.78, 0.86}, {0.1, 0.1, 0.1}, 10)
gray = gr.material({0.41, 0.41, 0.41}, {0.1, 0.1, 0.1}, 10)
darkgray = gr.material({0.25, 0.29, 0.30}, {0.1, 0.1, 0.1}, 10)
lightgray = gr.material({0.64, 0.68, 0.68}, {0.1, 0.1, 0.1}, 10)



torso_baymax = gr.mesh('sphere', 'torso_baymax')
rootnode:add_child(torso_baymax)
torso_baymax:scale(0.9, 1.1, 0.9);
torso_baymax:translate(0.0, 0.0, 0.0)
torso_baymax:set_material(white)

--neck_baymax and head_baymax
neckJoint_baymax = gr.joint('neckJoint_baymax', {0, 0, 3.14/8}, {0, 0, 3.14/8})
torso_baymax:add_child(neckJoint_baymax)
neckJoint_baymax:translate(0.0, 0.8, 0.0)

neck_baymax = gr.mesh('sphere', 'neck_baymax')
neckJoint_baymax:add_child(neck_baymax)
neck_baymax:scale(0.25, 0.12, 0.25)
neck_baymax:translate(0.0, 1.0, 0.2)
neck_baymax:set_material(gray)

headJoint_baymax = gr.joint('headJoint_baymax', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
neck_baymax:add_child(headJoint_baymax)
headJoint_baymax:translate(0.0, 1.0, 0.2)

head_baymax = gr.mesh('sphere', 'head_baymax')
headJoint_baymax:add_child(head_baymax)
head_baymax:scale(0.4, 0.32, 0.4);
head_baymax:translate(0.0, 1.35, 0.25)
head_baymax:set_material(white)

-- add eyes

leftEye_baymax = gr.mesh('sphere', 'leftEye_baymax')
head_baymax:add_child(leftEye_baymax)
leftEye_baymax:scale(0.09, 0.09, 0.1)
leftEye_baymax:translate(-0.178, 1.38, 0.52)
leftEye_baymax:set_material(black)

rightEye_baymax = gr.mesh('sphere', 'rightEye_baymax')
head_baymax:add_child(rightEye_baymax)
rightEye_baymax:scale(0.09, 0.09, 0.1)
rightEye_baymax:translate(0.178, 1.38, 0.52)
rightEye_baymax:set_material(black)


-- add eyes one

-- add the black line_baymax
line_baymax = gr.mesh('sphere', 'line_baymax')
head_baymax:add_child(line_baymax)
line_baymax:scale(0.34, 0.03, 0.401)
line_baymax:translate(0.0, 1.38, 0.28)
line_baymax:set_material(black)

-- add black line_baymax done

--neck_baymax and head_baymax done

--abs_baymax
absJoint_baymax = gr.joint('absJoint_baymax', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
torso_baymax:add_child(absJoint_baymax)
absJoint_baymax:translate(0.0, -0.5, 0.0)

abs_baymax = gr.mesh('sphere', 'abs_baymax')
absJoint_baymax:add_child(abs_baymax)
abs_baymax:scale(1.1, 1.3, 1.1)
abs_baymax:rotate("x",30)
abs_baymax:translate(0.0, -0.6, -0.1)
abs_baymax:set_material(white)

-- finally add tail_baymax
tailJoint_baymax = gr.joint('tailJoint_baymax', {-3.14/5, 0, 3.14/5}, {-3.14/4, 0, 3.14/4})
abs_baymax:add_child(tailJoint_baymax)
tailJoint_baymax:translate(0.0, -0.9, -1.2)

tail_baymax = gr.mesh('sphere', 'tail_baymax')
tailJoint_baymax:add_child(tail_baymax)
tail_baymax:scale(0.2, 0.2, 0.2)
tail_baymax:translate(0.0, -0.9, -1.3)
tail_baymax:set_material(white)

--abs_baymax done

-- left hip

leftHipJoint_baymax = gr.joint('leftHipJoint_baymax', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
abs_baymax:add_child(leftHipJoint_baymax)
leftHipJoint_baymax:translate(-0.6, -1.3, 0.0)

leftThigh_baymax = gr.mesh('sphere', 'leftThigh_baymax')
leftHipJoint_baymax:add_child(leftThigh_baymax)
leftThigh_baymax:scale(0.4, 1.0, 0.4)
leftThigh_baymax:translate(-0.6, -1.5, 0.0)
leftThigh_baymax:set_material(gray)

leftThighJoint_baymax = gr.joint('leftThighJoint_baymax', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
leftThigh_baymax:add_child(leftThighJoint_baymax)
leftThighJoint_baymax:translate(-0.6, -2.2, 0.0)

leftFoot_baymax = gr.mesh('sphere', 'leftFoot_baymax')
leftThighJoint_baymax:add_child(leftFoot_baymax)
leftFoot_baymax:scale(0.2, 0.15, 0.2)
leftFoot_baymax:translate(-0.6, -2.5, 0.0)
leftFoot_baymax:set_material(white)


-- left hip done 

-- right hip

rightHipJoint_baymax = gr.joint('rightHipJoint_baymax', {-3.14, 0, 3.14},{-3.14, 0, 3.14})
abs_baymax:add_child(rightHipJoint_baymax)
rightHipJoint_baymax:translate(0.6, -1.3, 0.0)

rightThigh_baymax = gr.mesh('sphere', 'leftThigh_baymax')
rightHipJoint_baymax:add_child(rightThigh_baymax)
rightThigh_baymax:scale(0.35, 1.0, 0.35)
rightThigh_baymax:translate(0.6, -1.5, 0.0)
rightThigh_baymax:set_material(gray)

rightThighJoint_baymax = gr.joint('rightThighJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
rightThigh_baymax:add_child(rightThighJoint_baymax)
rightThighJoint_baymax:translate(0.6, -2.2, 0.0)

rightFoot_baymax = gr.mesh('sphere', 'rightFoot_baymax')
rightThighJoint_baymax:add_child(rightFoot_baymax)
rightFoot_baymax:scale(0.2, 0.15, 0.2)
rightFoot_baymax:translate(0.6, -2.5, 0.0)
rightFoot_baymax:set_material(white)

-- right hip done

-- left shoulder and arm

leftShoulder_baymax = gr.mesh('sphere', 'leftShoulder_baymax')
torso_baymax:add_child(leftShoulder_baymax)
leftShoulder_baymax:scale(0.1, 0.1, 0.1)
leftShoulder_baymax:translate(-0.6, 0.8, 0.3)
leftShoulder_baymax:set_material(white)

leftShoulderJoint_baymax = gr.joint('leftShoulderJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
leftShoulder_baymax:add_child(leftShoulderJoint_baymax)
leftShoulderJoint_baymax:translate(-0.6, 0.8, 0.3)


leftUpArm_baymax = gr.mesh('sphere', 'leftUpArm_baymax')
leftShoulderJoint_baymax:add_child(leftUpArm_baymax)

leftUpArm_baymax:scale(0.3, 0.8, 0.3)
leftUpArm_baymax:rotate('z',-40.0)
leftUpArm_baymax:translate(-1.0, 0.3, 0.3)
leftUpArm_baymax:set_material(white)

-- add a cute hand
leftArmJoint_baymax = gr.joint('leftArmJoint_baymax', {-3.14/(1.2), 0, 3.14/2}, {-3.14/(1.2) , 0, 3.14/2})
leftUpArm_baymax:add_child(leftArmJoint_baymax)
leftArmJoint_baymax:translate(-1.4, -0.3, 0.4)

leftHand_baymax = gr.mesh('sphere', 'leftHand_baymax')
leftArmJoint_baymax:add_child(leftHand_baymax)
leftHand_baymax:scale(0.2, 0.2, 0.2)
leftHand_baymax:translate(-1.5, -0.4, 0.4)
leftHand_baymax:set_material(white)

-- left shoulder and arm done


-- right shoulder and arm

rightShoulder_baymax = gr.mesh('sphere', 'rightShoulder_baymax')
torso_baymax:add_child(rightShoulder_baymax)
rightShoulder_baymax:scale(0.1, 0.1, 0.1)
rightShoulder_baymax:translate(0.6, 0.8, 0.3)
rightShoulder_baymax:set_material(white)

rightShoulderJoint_baymax = gr.joint('rightShoulderJoint_baymax', {-3.14, 0, 3.14/2}, {-3.14/2, 0, 3.14/2})
rightShoulder_baymax:add_child(rightShoulderJoint_baymax)
rightShoulderJoint_baymax:translate(0.6, 0.8, 0.3)


rightUpArm_baymax = gr.mesh('sphere', 'rightUpArm_baymax')
rightShoulderJoint_baymax:add_child(rightUpArm_baymax)

rightUpArm_baymax:scale(0.3, 0.8, 0.3)
rightUpArm_baymax:rotate('z',40.0)
rightUpArm_baymax:translate(1.0, 0.3, 0.3)
rightUpArm_baymax:set_material(white)


-- add a cute hand
rightArmJoint_baymax = gr.joint('rightArmJoint_baymax', {-3.14/(1.2), 0, 3.14/2}, {-3.14/4, 0, 3.14/4})
rightUpArm_baymax:add_child(rightArmJoint_baymax)
rightArmJoint_baymax:translate(1.4, -0.3, 0.4)

rightHand_baymax = gr.mesh('sphere', 'rightHand_baymax')
rightArmJoint_baymax:add_child(rightHand_baymax)
rightHand_baymax:scale(0.2, 0.2, 0.2)
rightHand_baymax:translate(1.5, -0.4, 0.4)
rightHand_baymax:set_material(white)
-- right shoulder and arm done


-- left wing base and wing
leftWing_baymaxBaseJoint_baymax = gr.joint('leftWing_baymaxBaseJoint_baymax', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
torso_baymax:add_child(leftWing_baymaxBaseJoint_baymax)
leftWing_baymaxBaseJoint_baymax:translate(-0.5, 0.8, -0.4)


leftWing_baymaxBase_baymax = gr.mesh('sphere', 'leftWing_baymaxBase_baymax')
leftWing_baymaxBaseJoint_baymax:add_child(leftWing_baymaxBase_baymax)
leftWing_baymaxBase_baymax:scale(0.6, 0.3, 0.05)
leftWing_baymaxBase_baymax:rotate('z',-40.0)
leftWing_baymaxBase_baymax:translate(-0.6, 1.0, -0.6)
leftWing_baymaxBase_baymax:set_material(black)

leftWingJoint_baymax = gr.joint('leftWingJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14/2, 0, 3.14/2})
leftWing_baymaxBase_baymax:add_child(leftWingJoint_baymax)
leftWingJoint_baymax:rotate('x',80.0)
leftWingJoint_baymax:rotate('y',80.0)
leftWingJoint_baymax:rotate('z',20.0)
leftWingJoint_baymax:translate(-1.0, 1.4, -0.6)


leftWing_baymax = gr.mesh('sphere', 'leftWing_baymax')
leftWingJoint_baymax:add_child(leftWing_baymax)
leftWing_baymax:scale(1.2, 0.3, 0.1)
leftWing_baymax:rotate('z',20.0)
leftWing_baymax:translate(-1.8, 1.1, -0.6)
leftWing_baymax:set_material(red)

-- left wing base and wing done

-- right wing base and wing
rightWing_baymaxBaseJoint_baymax = gr.joint('rightWing_baymaxBaseJoint_baymax', {-3.14/8, 0, 3.14/8},{-3.14/2, 0, 3.14/2})
torso_baymax:add_child(rightWing_baymaxBaseJoint_baymax)
rightWing_baymaxBaseJoint_baymax:translate(0.5, 0.8, -0.4)


rightWing_baymaxBase_baymax = gr.mesh('sphere', 'rightWing_baymaxBase_baymax')
rightWing_baymaxBaseJoint_baymax:add_child(rightWing_baymaxBase_baymax)
rightWing_baymaxBase_baymax:scale(0.6, 0.3, 0.05)
rightWing_baymaxBase_baymax:rotate('z',40.0)
rightWing_baymaxBase_baymax:translate(0.6, 1.0, -0.6)
rightWing_baymaxBase_baymax:set_material(black)

rightWingJoint_baymax = gr.joint('rightWingJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14/2, 0, 3.14/2})
rightWing_baymaxBase_baymax:add_child(rightWingJoint_baymax)
rightWingJoint_baymax:rotate('x',-80.0)
rightWingJoint_baymax:rotate('y',-80.0)
rightWingJoint_baymax:rotate('z',-20.0)
rightWingJoint_baymax:translate(1.0, 1.4, -0.6)


rightWing_baymax = gr.mesh('sphere', 'rightWing_baymax')
rightWingJoint_baymax:add_child(rightWing_baymax)
rightWing_baymax:scale(1.2, 0.3, 0.1)
rightWing_baymax:rotate('z',-20.0)
rightWing_baymax:translate(1.8, 1.1, -0.6)
rightWing_baymax:set_material(red)

-- right wing base and wing done







rootnode:translate(0.0, 0.0, -10.0)
torso:translate(-5.0,-2.25,0.0)
torso_baymax:translate(5.0,0.0,0.0)
return rootnode
