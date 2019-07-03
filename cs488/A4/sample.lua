stone = gr.material({0.8, 0.7, 0.7}, {0.0, 0.0, 0.0}, 0)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
hide = gr.material({0.84, 0.6, 0.53}, {0.3, 0.3, 0.3}, 20)
stone_2 = gr.material({0.4, 0.7, 0.7}, {0.0, 0.0, 0.0}, 10)
stone_red = gr.material({0.9, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0)

-- ##############################################
-- the arch
-- ##############################################

inst = gr.node('inst')

arc = gr.node('arc')
inst:add_child(arc)
arc:translate(0, 0, -10)

p1 = gr.nh_box('p1', {0, 0, 0}, 1)
arc:add_child(p1)
p1:set_material(stone_red)
p1:scale(0.8, 4, 0.8)
p1:translate(-2.4, 0, -0.4)

p2 = gr.nh_box('p2', {0, 0, 0}, 1)
arc:add_child(p2)
p2:set_material(stone_red)
p2:scale(0.8, 4, 0.8)
p2:translate(1.6, 0, -0.4)

s = gr.nh_sphere('s', {0, 0, 0}, 1)
arc:add_child(s)
s:set_material(stone_red)
s:scale(4, 0.6, 0.6)
s:translate(0, 4, 0)


-- #############################################
-- Read in the cow model from a separate file.
-- #############################################

cow_poly = gr.mesh('cow', './Assets/cow.obj')
factor = 2.0/(2.76+3.637)

cow_poly:set_material(hide)

cow_poly:translate(0.0, 3.637, 0.0)
cow_poly:scale(factor, factor, factor)
cow_poly:translate(0.0, -1.0, 0.0)

-- ##############################################
-- the scene
-- ##############################################

scene = gr.node('scene')
scene:rotate('X', 23)

-- the floor

plane = gr.mesh('plane', './Assets/plane.obj' )
scene:add_child(plane)
plane:set_material(grass)
plane:scale(30, 30, 30)

-- Construct a central altar in the shape of a buckyball.  The
-- buckyball at the centre of the real Stonehenge was destroyed
-- in the great fire of 733 AD.

buckyball = gr.mesh( 'buckyball', './Assets/buckyball.obj' )
scene:add_child(buckyball)
buckyball:set_material(stone)
buckyball:scale(0.9, 3.9, 0.9)
buckyball:translate(20, 5, 4)

buckyball_sup = gr.nh_box('buckyball_sup', {0, 0, 0}, 1)
scene:add_child(buckyball_sup)
buckyball_sup:set_material(stone_2)
buckyball_sup:scale(5, 2.9, 4.9)
buckyball_sup:translate(17.5, 0, 2.1)

mickey = gr.mesh( 'mickey', './Assets/mickey.obj' )
scene:add_child(mickey)
mickey:set_material(stone)
mickey:scale(5.9, 5.9, 5.9)
mickey:translate(10, 1.2, 15)


-- Use the instanced cow model to place some actual cows in the scene.
-- For convenience, do this in a loop.

cow_number = 1

for _, pt in pairs({
              {{-20,1.2,-13}, 20},
		      {{-25,1.2,-8}, 20},
		      {{-16,1.2,-6}, 20},
              {{-19,1.2,-10}, 20},
              {{-20,1.2,-5}, 20},
              {{-12,1.2,4}, 20},}) do
   cow_instance = gr.node('cow' .. tostring(cow_number))
   scene:add_child(cow_instance)
   cow_instance:add_child(cow_poly)
   cow_instance:scale(1.4, 1.4, 1.4)
   --cow_instance:rotate('Y', pt[2])
   cow_instance:translate(table.unpack(pt[1]))
   
   cow_number = cow_number + 1
end

-- Place a ring of arches.

arc_number = 1
for _, pt2 in pairs({
    {{-5,1.2,-13}, 20},
    {{-2,1.2,-2}, 70},
    {{4,1.2,7}, 40},
    {{-10,1.2,-10}, 10},
    {{-7,1.2,18}, 60},
    {{-5,1.2,27}, 30},
    {{5,1.2,20}, 40},
    {{7,1.2,15}, 50},
    {{9,1.2,5}, 70}}) do
   an_arc = gr.node('arc' .. tostring(arc_number))
   an_arc:rotate('Y',  pt2[2])
   scene:add_child(an_arc)
   an_arc:add_child(arc)
   an_arc:translate(table.unpack(pt2[1]))

   arc_number = arc_number + 1
end

gr.render(scene,
	  'sample.png', 1000, 1000,
	  {0, 2, 70}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.4, 0.4, 0.4}, {gr.light({200, 202, 430}, {0.8, 0.8, 0.8}, {1, 0, 0})})