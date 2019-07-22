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

brown = gr.material({0.36, 0.27, 0.06}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
lightBlue = gr.material({0.43, 0.78, 0.86}, {0.1, 0.1, 0.1}, 10)
gray = gr.material({0.41, 0.41, 0.41}, {0.1, 0.1, 0.1}, 10)
darkgray = gr.material({0.25, 0.29, 0.30}, {0.1, 0.1, 0.1}, 10)
lightgray = gr.material({0.64, 0.68, 0.68}, {0.1, 0.1, 0.1}, 10)

-- add a platform

platform = gr.mesh('cube', 'platform', 2)
rootnode:add_child(platform)
platform:scale(60.0, 25.0, 2.5)
platform:translate(0.0, 0.0, 5.0)
platform:rotate('x',90)
platform:set_material(darkgray)

platform_back = gr.mesh('cube', 'platform_back',3)
rootnode:add_child(platform_back)
platform_back:scale(60.0, 25.0, 0.5)
platform_back:translate(0.0, 5.0, -12.0)
platform_back:set_material(darkgray)

platform_left = gr.mesh('cube', 'platform_left',3)
rootnode:add_child(platform_left)
platform_left:scale(5.0, 25.0, 50.0)
platform_left:translate(-30.0, 5.0, -12.0)
platform_left:set_material(darkgray)

platform_right = gr.mesh('cube', 'platform_right',3)
rootnode:add_child(platform_right)
platform_right:scale(5.0, 25.0, 50.0)
platform_right:translate(30.0, 5.0, -12.0)
platform_right:set_material(darkgray)





torso = gr.mesh('sphere', 'torso')
rootnode:add_child(torso)
torso:scale(0.9, 1.1, 0.9);
torso:translate(0.0, 0.0, 0.0)
torso:set_material(white)

--neck and head
neckJoint = gr.joint('neckJoint', {0, 0, 3.14/8}, {0, 0, 3.14/8})
torso:add_child(neckJoint)
neckJoint:translate(0.0, 0.8, 0.0)

neck = gr.mesh('sphere', 'neck')
neckJoint:add_child(neck)
neck:scale(0.25, 0.12, 0.25)
neck:translate(0.0, 1.0, 0.2)
neck:set_material(gray)

headJoint = gr.joint('headJoint', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
neck:add_child(headJoint)
headJoint:translate(0.0, 1.0, 0.2)

head = gr.mesh('sphere', 'head')
headJoint:add_child(head)
head:scale(0.4, 0.32, 0.4);
head:translate(0.0, 1.35, 0.25)
head:set_material(white)

-- add eyes

leftEye = gr.mesh('sphere', 'leftEye')
head:add_child(leftEye)
leftEye:scale(0.09, 0.09, 0.1)
leftEye:translate(-0.178, 1.38, 0.52)
leftEye:set_material(black)

rightEye = gr.mesh('sphere', 'rightEye')
head:add_child(rightEye)
rightEye:scale(0.09, 0.09, 0.1)
rightEye:translate(0.178, 1.38, 0.52)
rightEye:set_material(black)


-- add eyes one

-- add the black line
line = gr.mesh('sphere', 'line')
head:add_child(line)
line:scale(0.34, 0.03, 0.401)
line:translate(0.0, 1.38, 0.28)
line:set_material(black)

-- add black line done

--neck and head done

--abs
absJoint = gr.joint('absJoint', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
torso:add_child(absJoint)
absJoint:translate(0.0, -0.5, 0.0)

abs = gr.mesh('sphere', 'abs')
absJoint:add_child(abs)
abs:scale(1.1, 1.3, 1.1)
abs:rotate("x",30)
abs:translate(0.0, -0.6, -0.1)
abs:set_material(white)

-- finally add tail
tailJoint = gr.joint('tailJoint', {-3.14/5, 0, 3.14/5}, {-3.14/4, 0, 3.14/4})
abs:add_child(tailJoint)
tailJoint:translate(0.0, -0.9, -1.2)

tail = gr.mesh('sphere', 'tail')
tailJoint:add_child(tail)
tail:scale(0.2, 0.2, 0.2)
tail:translate(0.0, -0.9, -1.3)
tail:set_material(white)

--abs done

-- left hip

leftHipJoint = gr.joint('leftHipJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
abs:add_child(leftHipJoint)
leftHipJoint:translate(-0.6, -1.3, 0.0)

leftThigh = gr.mesh('sphere', 'leftThigh')
leftHipJoint:add_child(leftThigh)
leftThigh:scale(0.4, 1.0, 0.4)
leftThigh:translate(-0.6, -1.5, 0.0)
leftThigh:set_material(gray)

leftKneeJoint = gr.joint('leftKneeJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
leftThigh:add_child(leftKneeJoint)
leftKneeJoint:translate(-0.6, -2.2, 0.0)

leftCalf = gr.mesh('sphere', 'leftCalf')
leftKneeJoint:add_child(leftCalf)
leftCalf:scale(0.3, 1.0, 0.3)
leftCalf:translate(-0.6, -2.8, 0.0)
leftCalf:set_material(gray)

leftAnkleJoint = gr.joint('leftAnkleJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
leftCalf:add_child(leftAnkleJoint)
leftAnkleJoint:translate(-0.6, -3.6, 0.0)

leftFoot = gr.mesh('sphere', 'leftFoot')
leftAnkleJoint:add_child(leftFoot)
leftFoot:scale(0.25, 0.15, 0.25)
leftFoot:translate(-0.6, -3.9, 0.0)
leftFoot:set_material(white)


-- left hip done 

-- right hip

rightHipJoint = gr.joint('rightHipJoint', {-3.14, 0, 3.14},{-3.14, 0, 3.14})
abs:add_child(rightHipJoint)
rightHipJoint:translate(0.6, -1.3, 0.0)

rightThigh = gr.mesh('sphere', 'reftThigh')
rightHipJoint:add_child(rightThigh)
rightThigh:scale(0.35, 1.0, 0.35)
rightThigh:translate(0.6, -1.5, 0.0)
rightThigh:set_material(gray)

rightKneeJoint = gr.joint('rightKneeJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
rightThigh:add_child(rightKneeJoint)
rightKneeJoint:translate(0.6, -2.2, 0.0)

rightCalf = gr.mesh('sphere', 'rightCalf')
rightKneeJoint:add_child(rightCalf)
rightCalf:scale(0.3, 1.0, 0.3)
rightCalf:translate(0.6, -2.8, 0.0)
rightCalf:set_material(gray)

rightAnkleJoint = gr.joint('rightAnkleJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
rightCalf:add_child(rightAnkleJoint)
rightAnkleJoint:translate(0.6, -3.6, 0.0)

rightFoot = gr.mesh('sphere', 'rightFoot')
rightAnkleJoint:add_child(rightFoot)
rightFoot:scale(0.25, 0.15, 0.25)
rightFoot:translate(0.6, -3.9, 0.0)
rightFoot:set_material(white)
-- right hip done

-- left shoulder and arm

leftShoulder = gr.mesh('sphere', 'leftShoulder')
torso:add_child(leftShoulder)
leftShoulder:scale(0.1, 0.1, 0.1)
leftShoulder:translate(-0.6, 0.8, 0.3)
leftShoulder:set_material(white)

leftShoulderJoint = gr.joint('leftShoulderJoint', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
leftShoulder:add_child(leftShoulderJoint)
leftShoulderJoint:translate(-0.6, 0.8, 0.3)


leftUpArm = gr.mesh('sphere', 'leftUpArm')
leftShoulderJoint:add_child(leftUpArm)

leftUpArm:scale(0.3, 0.8, 0.3)
leftUpArm:rotate('z',-40.0)
leftUpArm:translate(-1.0, 0.3, 0.3)
leftUpArm:set_material(white)

-- add a cute hand
leftArmJoint = gr.joint('leftArmJoint', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
leftUpArm:add_child(leftArmJoint)
leftArmJoint:translate(-1.22, -0.22, 0.3)


leftLowArm = gr.mesh('sphere', 'leftLowArm')
leftArmJoint:add_child(leftLowArm)
leftLowArm:scale(0.2, 0.6, 0.2)
leftLowArm:rotate('z',-20.0)
leftLowArm:rotate('x',-20.0)
leftLowArm:translate(-1.55, -0.55, 0.4)
leftLowArm:set_material(white)


leftWristJoint = gr.joint('leftWristJoint', {-3.14/4, 0, 3.14/4}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
leftLowArm:add_child(leftWristJoint)
leftWristJoint:translate(-1.7, -1.05, 0.5)

leftHand = gr.mesh('sphere', 'leftHand')
leftWristJoint:add_child(leftHand)
leftHand:scale(0.2, 0.2, 0.2)
leftHand:translate(-1.75, -1.15, 0.6)
leftHand:set_material(white)

-- left shoulder and arm done


-- right shoulder and arm

rightShoulder = gr.mesh('sphere', 'rightShoulder')
torso:add_child(rightShoulder)
rightShoulder:scale(0.1, 0.1, 0.1)
rightShoulder:translate(0.6, 0.8, 0.3)
rightShoulder:set_material(white)

rightShoulderJoint = gr.joint('rightShoulderJoint', {-3.14, 0, 3.14/2}, {-3.14/2, 0, 3.14/2})
rightShoulder:add_child(rightShoulderJoint)
rightShoulderJoint:translate(0.6, 0.8, 0.3)


rightUpArm = gr.mesh('sphere', 'rightUpArm')
rightShoulderJoint:add_child(rightUpArm)

rightUpArm:scale(0.3, 0.8, 0.3)
rightUpArm:rotate('z',40.0)
rightUpArm:translate(1.0, 0.3, 0.3)
rightUpArm:set_material(white)


-- add a cute hand
rightArmJoint = gr.joint('rightArmJoint', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
rightUpArm:add_child(rightArmJoint)
rightArmJoint:translate(1.22, -0.22, 0.3)


rightLowArm = gr.mesh('sphere', 'rightLowArm')
rightArmJoint:add_child(rightLowArm)
rightLowArm:scale(0.2, 0.6, 0.2)
rightLowArm:rotate('z',20.0)
rightLowArm:rotate('x',-20.0)
rightLowArm:translate(1.55, -0.55, 0.4)
rightLowArm:set_material(white)


rightWristJoint = gr.joint('rightWristJoint', {-3.14/4, 0, 3.14/4}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
rightLowArm:add_child(rightWristJoint)
rightWristJoint:translate(1.7, -1.05, 0.5)

rightHand = gr.mesh('sphere', 'rightHand')
rightWristJoint:add_child(rightHand)
rightHand:scale(0.2, 0.2, 0.2)
rightHand:translate(1.75, -1.15, 0.6)
rightHand:set_material(white)
-- right shoulder and arm done


-- left wing base and wing
leftWingBaseJoint = gr.joint('leftWingBaseJoint', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
torso:add_child(leftWingBaseJoint)
leftWingBaseJoint:translate(-0.5, 0.8, -0.4)


leftWingBase = gr.mesh('sphere', 'leftWingBase')
leftWingBaseJoint:add_child(leftWingBase)
leftWingBase:scale(0.6, 0.3, 0.05)
leftWingBase:rotate('z',-40.0)
leftWingBase:translate(-0.6, 1.0, -0.6)
leftWingBase:set_material(black)

leftWingJoint = gr.joint('leftWingJoint', {-3.14/4, 0, 3.14/4}, {-3.14/2, 0, 3.14/2})
leftWingBase:add_child(leftWingJoint)
leftWingJoint:rotate('x',80.0)
leftWingJoint:rotate('y',80.0)
leftWingJoint:rotate('z',20.0)
leftWingJoint:translate(-1.0, 1.4, -0.6)


leftWing = gr.mesh('sphere', 'leftWing')
leftWingJoint:add_child(leftWing)
leftWing:scale(1.2, 0.3, 0.1)
leftWing:rotate('z',20.0)
leftWing:translate(-1.8, 1.1, -0.6)
leftWing:set_material(red)

-- left wing base and wing done

-- right wing base and wing
rightWingBaseJoint = gr.joint('rightWingBaseJoint', {-3.14/8, 0, 3.14/8},{-3.14/2, 0, 3.14/2})
torso:add_child(rightWingBaseJoint)
rightWingBaseJoint:translate(0.5, 0.8, -0.4)


rightWingBase = gr.mesh('sphere', 'rightWingBase')
rightWingBaseJoint:add_child(rightWingBase)
rightWingBase:scale(0.6, 0.3, 0.05)
rightWingBase:rotate('z',40.0)
rightWingBase:translate(0.6, 1.0, -0.6)
rightWingBase:set_material(black)

rightWingJoint = gr.joint('rightWingJoint', {-3.14/4, 0, 3.14/4}, {-3.14/2, 0, 3.14/2})
rightWingBase:add_child(rightWingJoint)
rightWingJoint:rotate('x',-80.0)
rightWingJoint:rotate('y',-80.0)
rightWingJoint:rotate('z',-20.0)
rightWingJoint:translate(1.0, 1.4, -0.6)


rightWing = gr.mesh('sphere', 'rightWing')
rightWingJoint:add_child(rightWing)
rightWing:scale(1.2, 0.3, 0.1)
rightWing:rotate('z',-20.0)
rightWing:translate(1.8, 1.1, -0.6)
rightWing:set_material(red)
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

leftHipJoint_baymax = gr.joint('leftHipJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
abs_baymax:add_child(leftHipJoint_baymax)
leftHipJoint_baymax:translate(-0.6, -1.3, 0.0)

leftThigh_baymax = gr.mesh('sphere', 'leftThigh_baymax')
leftHipJoint_baymax:add_child(leftThigh_baymax)
leftThigh_baymax:scale(0.4, 1.0, 0.4)
leftThigh_baymax:translate(-0.6, -1.5, 0.0)
leftThigh_baymax:set_material(gray)

leftKneeJoint_baymax = gr.joint('leftKneeJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
leftThigh_baymax:add_child(leftKneeJoint_baymax)
leftKneeJoint_baymax:translate(-0.6, -2.2, 0.0)

leftCalf_baymax = gr.mesh('sphere', 'leftCalf_baymax')
leftKneeJoint_baymax:add_child(leftCalf_baymax)
leftCalf_baymax:scale(0.3, 1.0, 0.3)
leftCalf_baymax:translate(-0.6, -2.8, 0.0)
leftCalf_baymax:set_material(gray)

leftAnkleJoint_baymax = gr.joint('leftAnkleJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
leftCalf_baymax:add_child(leftAnkleJoint_baymax)
leftAnkleJoint_baymax:translate(-0.6, -3.6, 0.0)

leftFoot_baymax = gr.mesh('sphere', 'leftFoot_baymax')
leftAnkleJoint_baymax:add_child(leftFoot_baymax)
leftFoot_baymax:scale(0.25, 0.15, 0.25)
leftFoot_baymax:translate(-0.6, -3.9, 0.0)
leftFoot_baymax:set_material(white)


-- left hip done 

-- right hip

rightHipJoint_baymax = gr.joint('rightHipJoint_baymax', {-3.14, 0, 3.14},{-3.14, 0, 3.14})
abs_baymax:add_child(rightHipJoint_baymax)
rightHipJoint_baymax:translate(0.6, -1.3, 0.0)

rightThigh_baymax = gr.mesh('sphere', 'reftThigh_baymax')
rightHipJoint_baymax:add_child(rightThigh_baymax)
rightThigh_baymax:scale(0.35, 1.0, 0.35)
rightThigh_baymax:translate(0.6, -1.5, 0.0)
rightThigh_baymax:set_material(gray)

rightKneeJoint_baymax = gr.joint('rightKneeJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
rightThigh_baymax:add_child(rightKneeJoint_baymax)
rightKneeJoint_baymax:translate(0.6, -2.2, 0.0)

rightCalf_baymax = gr.mesh('sphere', 'rightCalf_baymax')
rightKneeJoint_baymax:add_child(rightCalf_baymax)
rightCalf_baymax:scale(0.3, 1.0, 0.3)
rightCalf_baymax:translate(0.6, -2.8, 0.0)
rightCalf_baymax:set_material(gray)

rightAnkleJoint_baymax = gr.joint('rightAnkleJoint_baymax', {-3.14, 0, 3.14}, {-3.14, 0, 3.14})
rightCalf_baymax:add_child(rightAnkleJoint_baymax)
rightAnkleJoint_baymax:translate(0.6, -3.6, 0.0)

rightFoot_baymax = gr.mesh('sphere', 'rightFoot_baymax')
rightAnkleJoint_baymax:add_child(rightFoot_baymax)
rightFoot_baymax:scale(0.25, 0.15, 0.25)
rightFoot_baymax:translate(0.6, -3.9, 0.0)
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
leftArmJoint_baymax = gr.joint('leftArmJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
leftUpArm_baymax:add_child(leftArmJoint_baymax)
leftArmJoint_baymax:translate(-1.22, -0.22, 0.3)


leftLowArm_baymax = gr.mesh('sphere', 'leftLowArm_baymax')
leftArmJoint_baymax:add_child(leftLowArm_baymax)
leftLowArm_baymax:scale(0.2, 0.6, 0.2)
leftLowArm_baymax:rotate('z',-20.0)
leftLowArm_baymax:rotate('x',-20.0)
leftLowArm_baymax:translate(-1.55, -0.55, 0.4)
leftLowArm_baymax:set_material(white)


leftWristJoint_baymax = gr.joint('leftWristJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
leftLowArm_baymax:add_child(leftWristJoint_baymax)
leftWristJoint_baymax:translate(-1.7, -1.05, 0.5)

leftHand_baymax = gr.mesh('sphere', 'leftHand_baymax')
leftWristJoint_baymax:add_child(leftHand_baymax)
leftHand_baymax:scale(0.2, 0.2, 0.2)
leftHand_baymax:translate(-1.75, -1.15, 0.6)
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
rightArmJoint_baymax = gr.joint('rightArmJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
rightUpArm_baymax:add_child(rightArmJoint_baymax)
rightArmJoint_baymax:translate(1.22, -0.22, 0.3)


rightLowArm_baymax = gr.mesh('sphere', 'rightLowArm_baymax')
rightArmJoint_baymax:add_child(rightLowArm_baymax)
rightLowArm_baymax:scale(0.2, 0.6, 0.2)
rightLowArm_baymax:rotate('z',20.0)
rightLowArm_baymax:rotate('x',-20.0)
rightLowArm_baymax:translate(1.55, -0.55, 0.4)
rightLowArm_baymax:set_material(white)


rightWristJoint_baymax = gr.joint('rightWristJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14, 0, 3.14},{-3.14/4, 0, 3.14/4})
rightLowArm_baymax:add_child(rightWristJoint_baymax)
rightWristJoint_baymax:translate(1.7, -1.05, 0.5)

rightHand_baymax = gr.mesh('sphere', 'rightHand_baymax')
rightWristJoint_baymax:add_child(rightHand_baymax)
rightHand_baymax:scale(0.2, 0.2, 0.2)
rightHand_baymax:translate(1.75, -1.15, 0.6)
rightHand_baymax:set_material(white)
-- right shoulder and arm done


-- left wing base and wing
leftWingBaseJoint_baymax = gr.joint('leftWingBaseJoint_baymax', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
torso_baymax:add_child(leftWingBaseJoint_baymax)
leftWingBaseJoint_baymax:translate(-0.5, 0.8, -0.4)


leftWingBase_baymax = gr.mesh('sphere', 'leftWingBase_baymax')
leftWingBaseJoint_baymax:add_child(leftWingBase_baymax)
leftWingBase_baymax:scale(0.6, 0.3, 0.05)
leftWingBase_baymax:rotate('z',-40.0)
leftWingBase_baymax:translate(-0.6, 1.0, -0.6)
leftWingBase_baymax:set_material(black)

leftWingJoint_baymax = gr.joint('leftWingJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14/2, 0, 3.14/2})
leftWingBase_baymax:add_child(leftWingJoint_baymax)
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
rightWingBaseJoint_baymax = gr.joint('rightWingBaseJoint_baymax', {-3.14/8, 0, 3.14/8},{-3.14/2, 0, 3.14/2})
torso_baymax:add_child(rightWingBaseJoint_baymax)
rightWingBaseJoint_baymax:translate(0.5, 0.8, -0.4)


rightWingBase_baymax = gr.mesh('sphere', 'rightWingBase_baymax')
rightWingBaseJoint_baymax:add_child(rightWingBase_baymax)
rightWingBase_baymax:scale(0.6, 0.3, 0.05)
rightWingBase_baymax:rotate('z',40.0)
rightWingBase_baymax:translate(0.6, 1.0, -0.6)
rightWingBase_baymax:set_material(black)

rightWingJoint_baymax = gr.joint('rightWingJoint_baymax', {-3.14/4, 0, 3.14/4}, {-3.14/2, 0, 3.14/2})
rightWingBase_baymax:add_child(rightWingJoint_baymax)
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







rootnode:translate(0.0, -8.0, -18.0)
torso:translate(-5.0,2.25, 0.0)
torso_baymax:translate(5.0,2.25, 0.0)
return rootnode
