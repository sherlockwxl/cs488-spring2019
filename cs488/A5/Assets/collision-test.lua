-- puppet.lua
-- A simplified puppet without posable joints, but that
-- looks roughly humanoid.

rootnode = gr.node('root')

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 10)
green = gr.material({0.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)

torso = gr.mesh('cube', 'torso')
rootnode:add_child(torso)
torso:scale(0.5, 0.8, 0.5);
torso:translate(0.0, 0.0, 0.0)
torso:set_material(blue)



-- add second puppet





brown = gr.material({0.36, 0.27, 0.06}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
lightBlue = gr.material({0.43, 0.78, 0.86}, {0.1, 0.1, 0.1}, 10)
gray = gr.material({0.41, 0.41, 0.41}, {0.1, 0.1, 0.1}, 10)
darkgray = gr.material({0.25, 0.29, 0.30}, {0.1, 0.1, 0.1}, 10)
lightgray = gr.material({0.64, 0.68, 0.68}, {0.1, 0.1, 0.1}, 10)



torso_baymax = gr.mesh('cube', 'torso_baymax')
rootnode:add_child(torso_baymax)
torso_baymax:scale(0.9, 1.1, 0.9);
torso_baymax:translate(0.0, 0.0, 0.0)
torso_baymax:set_material(white)



-- right wing base and wing done







rootnode:translate(0.0, 0.0, -10.0)
torso:translate(-5.0,0.0,0.0)
torso_baymax:translate(5.0,0.0,0.0)
return rootnode
