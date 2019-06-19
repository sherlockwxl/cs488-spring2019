rootnode = gr.node('root')

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
brown = gr.material({0.36, 0.27, 0.06}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
lightBlue = gr.material({0.43, 0.78, 0.86}, {0.1, 0.1, 0.1}, 10)
gray = gr.material({0.41, 0.41, 0.41}, {0.1, 0.1, 0.1}, 10)
darkgray = gr.material({0.25, 0.29, 0.30}, {0.1, 0.1, 0.1}, 10)
lightgray = gr.material({0.64, 0.68, 0.68}, {0.1, 0.1, 0.1}, 10)



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
absJoint = gr.joint('absJoint', {-3.14/8, 0, 3.14/8}, {0, 0, 0})
torso:add_child(absJoint)
absJoint:translate(0.0, -0.5, 0.0)

abs = gr.mesh('sphere', 'abs')
absJoint:add_child(abs)
abs:rotate("x",30)
abs:scale(1.1, 1.3, 1.1)
abs:translate(0.0, -0.6, -0.1)
abs:set_material(white)

-- finally add tail
tailJoint = gr.joint('tailJoint', {-3.14/5, 0, 3.14/5}, {0, 0, 0})
abs:add_child(tailJoint)
tailJoint:translate(0.0, -0.9, -1.2)

tail = gr.mesh('sphere', 'tail')
tailJoint:add_child(tail)
tail:scale(0.2, 0.2, 0.2)
tail:translate(0.0, -0.9, -1.3)
tail:set_material(white)

--abs done

-- left hip

leftHipJoint = gr.joint('leftHipJoint', {-3.14/8, 0, 3.14/8}, {0 , 0, 0})
abs:add_child(leftHipJoint)
leftHipJoint:translate(-0.6, -1.3, 0.0)

leftThigh = gr.mesh('sphere', 'leftThigh')
leftHipJoint:add_child(leftThigh)
leftThigh:scale(0.4, 1.0, 0.4)
leftThigh:translate(-0.6, -1.5, 0.0)
leftThigh:set_material(gray)

leftThighJoint = gr.joint('leftThighJoint', {-3.14/8, 0, 3.14/8}, {0 , 0, 0})
leftThigh:add_child(leftThighJoint)
leftThighJoint:translate(-0.6, -2.2, 0.0)

leftFoot = gr.mesh('sphere', 'leftFoot')
leftThighJoint:add_child(leftFoot)
leftFoot:scale(0.2, 0.15, 0.2)
leftFoot:translate(-0.6, -2.5, 0.0)
leftFoot:set_material(white)


-- left hip done 

-- right hip

rightHipJoint = gr.joint('rightHipJoint', {-3.14/8, 0, 3.14/8}, {0 , 0, 0})
abs:add_child(rightHipJoint)
rightHipJoint:translate(0.6, -1.3, 0.0)

rightThigh = gr.mesh('sphere', 'leftThigh')
rightHipJoint:add_child(rightThigh)
rightThigh:scale(0.35, 1.0, 0.35)
rightThigh:translate(0.6, -1.5, 0.0)
rightThigh:set_material(gray)

rightThighJoint = gr.joint('rightThighJoint', {-3.14/8, 0, 3.14/8}, {0 , 0, 0})
rightThigh:add_child(rightThighJoint)
rightThighJoint:translate(0.6, -2.2, 0.0)

rightFoot = gr.mesh('sphere', 'rightFoot')
rightThighJoint:add_child(rightFoot)
rightFoot:scale(0.2, 0.15, 0.2)
rightFoot:translate(0.6, -2.5, 0.0)
rightFoot:set_material(white)

-- right hip done

-- left shoulder and arm

leftShoulder = gr.mesh('sphere', 'leftShoulder')
torso:add_child(leftShoulder)
leftShoulder:scale(0.1, 0.1, 0.1)
leftShoulder:translate(-0.6, 0.8, 0.3)
leftShoulder:set_material(white)

leftShoulderJoint = gr.joint('leftShoulderJoint', {-3.14, 0, 3.14/2}, {-3.14/2, 0, 3.14/2})
leftShoulder:add_child(leftShoulderJoint)
leftShoulderJoint:translate(-0.6, 0.8, 0.3)


leftUpArm = gr.mesh('sphere', 'leftUpArm')
leftShoulderJoint:add_child(leftUpArm)

leftUpArm:scale(0.3, 0.8, 0.3)
leftUpArm:rotate('z',-40.0)
leftUpArm:translate(-1.0, 0.3, 0.3)
leftUpArm:set_material(white)

-- add a cute hand
leftArmJoint = gr.joint('leftArmJoint', {-3.14/(1.2), 0, 3.14/2}, {0 , 0, 0})
leftUpArm:add_child(leftArmJoint)
leftArmJoint:translate(-1.4, -0.3, 0.4)

leftHand = gr.mesh('sphere', 'leftHand')
leftArmJoint:add_child(leftHand)
leftHand:scale(0.2, 0.2, 0.2)
leftHand:translate(-1.5, -0.4, 0.4)
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
rightArmJoint = gr.joint('rightArmJoint', {-3.14/(1.2), 0, 3.14/2}, {0 , 0, 0})
rightUpArm:add_child(rightArmJoint)
rightArmJoint:translate(1.4, -0.3, 0.4)

rightHand = gr.mesh('sphere', 'rightHand')
rightArmJoint:add_child(rightHand)
rightHand:scale(0.2, 0.2, 0.2)
rightHand:translate(1.5, -0.4, 0.4)
rightHand:set_material(white)
-- right shoulder and arm done


-- left wing base and wing
leftWingBaseJoint = gr.joint('leftWingBaseJoint', {-3.14/8, 0, 3.14/8}, {0, 0, 0})
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
rightWingBaseJoint = gr.joint('rightWingBaseJoint', {-3.14/8, 0, 3.14/8}, {0, 0, 0})
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

-- right wing base and wing done




rootnode:translate(0.0, 0.0, -8.0)

return rootnode