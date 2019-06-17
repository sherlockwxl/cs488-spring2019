-- puppet.lua
-- A simplified puppet without posable joints, but that
-- looks roughly humanoid.

rootnode = gr.node('root')

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 10)
green = gr.material({0.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
newclolo = gr.material({0.8, 0.8, 0.8}, {0.1, 0.1, 0.1}, 10)

torso = gr.mesh('sphere', 'torso')
rootnode:add_child(torso)
torso:scale(0.5, 0.8, 0.5);
torso:translate(0.0, 0.0, 0.0)
torso:set_material(blue)

neckJoint = gr.joint('neckJoint', {0, 0, 3.14/8}, {-3.14/8, 0, 3.14/8})
torso:add_child(neckJoint)
neckJoint:translate(0.0, 0.7, 0.0)

neck = gr.mesh('sphere', 'neck')
neckJoint:add_child(neck)
neck:scale(0.15, 0.4, 0.15)
neck:translate(0.0, 1.1, 0.0)
neck:set_material(white)

headJoint = gr.joint('headJoint', {-3.14/8, 0, 3.14/8}, {-3.14/4, 0, 3.14/4})
neck:add_child(headJoint)
headJoint:translate(0.0, 1.2, 0.0)

head = gr.mesh('sphere', 'head')
headJoint:add_child(head)
head:scale(0.4, 0.4, 0.4)
head:translate(0.0, 1.4, 0.0)
head:set_material(newclolo)

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

leftShoulderJoint = gr.joint('leftShoulderJoint', {-3.14, 0, 3.14/2}, {-3.14/2, 0, 3.14/2})
leftShoulder:add_child(leftShoulderJoint)
leftShoulderJoint:translate(-0.65, 0.8, 0.0)

leftUpArm = gr.mesh('sphere', 'leftUpArm')
leftShoulderJoint:add_child(leftUpArm)
leftUpArm:scale(0.2, 0.4, 0.2)
leftUpArm:translate(-0.65, 0.5, 0.0)
leftUpArm:set_material(green)

leftElbow = gr.joint('leftElbow', {-3.14/2, 0, 0}, {-3.14/2, 0, 3.14/2})
leftUpArm:add_child(leftElbow)
leftElbow:translate(-0.65, 0.15, 0.0)

leftDownArm = gr.mesh('sphere', 'leftDownArm')
leftElbow:add_child(leftDownArm)
leftDownArm:scale(0.15, 0.3, 0.15)
leftDownArm:translate(-0.65, -0.1, 0.0)
leftDownArm:set_material(green)

leftWrist = gr.joint('leftWrist', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
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

rightShoulderJoint = gr.joint('rightShoulderJoint', {-3.14, 0, 3.14/2}, {-3.14/2, 0, 3.14/2})
rightShoulder:add_child(rightShoulderJoint)
rightShoulderJoint:translate(0.65, 0.8, 0.0)

rightUpArm = gr.mesh('sphere', 'rightUpArm')
rightShoulderJoint:add_child(rightUpArm)
rightUpArm:scale(0.2, 0.4, 0.2)
rightUpArm:translate(0.65, 0.5, 0.0)
rightUpArm:set_material(green)

rightElbow = gr.joint('rightElbow', {-3.14/2, 0, 0}, {-3.14/2, 0, 3.14/2})
rightUpArm:add_child(rightElbow)
rightElbow:translate(0.65, 0.15, 0.0)

rightDownArm = gr.mesh('sphere', 'rightDownArm')
rightElbow:add_child(rightDownArm)
rightDownArm:scale(0.15, 0.3, 0.15)
rightDownArm:translate(0.65, -0.1, 0.0)
rightDownArm:set_material(green)

rightWrist = gr.joint('rightWrist', {-3.14/4, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
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

leftHipJoint = gr.joint('leftHipJoint', {-3.14/2, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
leftHip:add_child(leftHipJoint)
leftHipJoint:translate(-0.3, -0.9, 0.0)

leftUpLeg = gr.mesh('sphere', 'leftUpLeg')
leftHipJoint:add_child(leftUpLeg)
leftUpLeg:scale(0.2, 0.5, 0.2)
leftUpLeg:translate(-0.3, -1.2, 0.0)
leftUpLeg:set_material(red)

leftKnee = gr.joint('leftKnee', {0, 0, 3.14/2}, {-3.14/4, 0, 3.14/4})
leftUpLeg:add_child(leftKnee)
leftKnee:translate(-0.3, -1.65, 0.0)

leftDownLeg = gr.mesh('sphere', 'leftDownLeg')
leftKnee:add_child(leftDownLeg)
leftDownLeg:scale(0.2, 0.4, 0.2)
leftDownLeg:translate(-0.3, -2.0, 0.0)
leftDownLeg:set_material(red)

leftAnkle = gr.joint('leftAnkle', {-3.14/8, 0, 3.14/8}, {-3.14/8, 0, 3.14/8})
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

rightHipJoint = gr.joint('rightHipJoint', {-3.14/2, 0, 3.14/4}, {-3.14/4, 0, 3.14/4})
rightHip:add_child(rightHipJoint)
rightHipJoint:translate(0.3, -0.9, 0.0)

rightUpLeg = gr.mesh('sphere', 'rightUpLeg')
rightHipJoint:add_child(rightUpLeg)
rightUpLeg:scale(0.2, 0.5, 0.2)
rightUpLeg:translate(0.3, -1.2, 0.0)
rightUpLeg:set_material(red)

rightKnee = gr.joint('rightKnee', {0, 0, 3.14/2}, {-3.14/4, 0, 3.14/4})
rightUpLeg:add_child(rightKnee)
rightKnee:translate(0.3, -1.65, 0.0)

rightDownLeg = gr.mesh('sphere', 'rightDownLeg')
rightKnee:add_child(rightDownLeg)
rightDownLeg:scale(0.2, 0.4, 0.2)
rightDownLeg:translate(0.3, -2.0, 0.0)
rightDownLeg:set_material(red)

rightAnkle = gr.joint('rightAnkle', {-3.14/8, 0, 3.14/8}, {-3.14/8, 0, 3.14/8})
rightDownLeg:add_child(rightAnkle)
rightAnkle:translate(0.3, -2.3, 0.0)

rightFoot = gr.mesh('cube', 'rightFoot')
rightAnkle:add_child(rightFoot)
rightFoot:scale(0.3, 0.2, 0.5)
rightFoot:translate(0.3, -2.4, 0.2)
rightFoot:set_material(red)

rootnode:translate(0.0, 0.0, -5.0)

return rootnode
