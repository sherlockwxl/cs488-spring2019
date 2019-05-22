// Spring 2019

#include "A1.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

static const size_t DIM = 16;

// const for cube vertex and indices
// central is 0,0,0
static const GLfloat cube_vertex[][3] = {
	-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	
	-0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f
};

static const GLint face_indice[][3] = {
		// front
		0, 1, 4,
		1, 5, 4,

		//right
		1, 2, 5,
		2, 6, 5,

		//back
		2, 3, 7,
		7, 6, 2,

		//left
		3, 0, 4,
		4, 7, 3,

		//bot
		0, 1, 2,
		2, 3, 0,

		//top
		4, 5, 6,
		6, 7, 4
};


static const GLfloat floor_vertex[][3] = {
	0.0f, 0.0f, 0.0f,
	16.0f, 0.0f, 0.0f,
	16.0f, 0.0f, 16.0f,

	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 16.0f,
	16.0f, 0.0f, 16.0f
};
//----------------------------------------------------------------------------------------
// Constructor
A1::A1()
	: current_col( 0 )
{
	resetAttributes();
	rotation = 0;
	scale = 1;
	persistence =0;
	prev_movement = 0;
	minfo = nullptr;
}

//----------------------------------------------------------------------------------------
// Destructor
A1::~A1()
{}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A1::init()
{
	// Initialize random number generator
	int rseed=getpid();
	srandom(rseed);
	// Print random number seed in case we want to rerun with
	// same random numbers
	cout << "Random number seed = " << rseed << endl;
	
	
	// Set the background colour.
	glClearColor( 0.3, 0.5, 0.7, 1.0 );

	// Build the shader
	m_shader.generateProgramObject();
	m_shader.attachVertexShader(
		getAssetFilePath( "VertexShader.vs" ).c_str() );
	m_shader.attachFragmentShader(
		getAssetFilePath( "FragmentShader.fs" ).c_str() );
	m_shader.link();

	// Set up the uniforms
	P_uni = m_shader.getUniformLocation( "P" );
	V_uni = m_shader.getUniformLocation( "V" );
	M_uni = m_shader.getUniformLocation( "M" );
	col_uni = m_shader.getUniformLocation( "colour" );

	initGrid();

	initAvator();

	// Set up initial view and projection matrices (need to do this here,
	// since it depends on the GLFW window being set up correctly).
	view = glm::lookAt( 
		glm::vec3( 0.0f, 2.*float(DIM)*2.0*M_SQRT1_2, float(DIM)*2.0*M_SQRT1_2 ),
		glm::vec3( 0.0f, 0.0f, 0.0f ),
		glm::vec3( 0.0f, 1.0f, 0.0f ) );

	proj = glm::perspective( 
		glm::radians( 30.0f ),
		float( m_framebufferWidth ) / float( m_framebufferHeight ),
		1.0f, 1000.0f );


}

void A1::reset(){

	// 1. reset attributes
	resetAttributes();

	// if no maze was generated
	if(minfo == nullptr) return;

	// otherwise
	// 2. reset avatar
	initAvator();


	// 2. reset maze
	delete minfo;
	minfo = nullptr;

}

void A1::resetAttributes(){
	//reset all color
	color_cube = {0.23f,0.1f,0.13f};
	color_floor = {1.0f,0.614f,0.738f};
	color_avatar = {0.3f,0.9f,0.25f};
	colour[0] = 0.23f;
	colour[1] = 0.1f;
	colour[2] = 0.13f;

	// reset radio button selection
	current_col = 0;
	// reset rotation
	rotation = 0;
	// stop rotation
	persistence = 0;
	// reset shift
	shiftheld = false;
	// reset scale
	scale = 1;
	// reset mouse
	m_mouseButtonActive = false;
	// reset previous location
	prev_m_x = 0;
	// reset previous movement
	prev_movement = 0;
}

void A1::initGrid()
{
	size_t sz = 3 * 2 * 2 * (DIM+3);

	float *verts = new float[ sz ];
	size_t ct = 0;
	for( int idx = 0; idx < DIM+3; ++idx ) {
		verts[ ct ] = -1;
		verts[ ct+1 ] = 0;
		verts[ ct+2 ] = idx-1;
		verts[ ct+3 ] = DIM+1;
		verts[ ct+4 ] = 0;
		verts[ ct+5 ] = idx-1;
		ct += 6;

		verts[ ct ] = idx-1;
		verts[ ct+1 ] = 0;
		verts[ ct+2 ] = -1;
		verts[ ct+3 ] = idx-1;
		verts[ ct+4 ] = 0;
		verts[ ct+5 ] = DIM+1;
		ct += 6;
	}

	// Create the vertex array to record buffer assignments.
	glGenVertexArrays( 1, &m_grid_vao );
	glBindVertexArray( m_grid_vao );

	// Create the cube vertex buffer
	glGenBuffers( 1, &m_grid_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, m_grid_vbo );
	glBufferData( GL_ARRAY_BUFFER, sz*sizeof(float),
		verts, GL_STATIC_DRAW );

	// Specify the means of extracting the position values properly.
	GLint posAttrib = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	// Reset state to prevent rogue code from messing with *my* 
	// stuff!
	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	// OpenGL has the buffer now, there's no need for us to keep a copy.
	delete [] verts;

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A1::appLogic()
{
	// Place per frame, application logic here ...
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A1::guiLogic()
{
	// We already know there's only going to be one window, so for 
	// simplicity we'll store button states in static local variables.
	// If there was ever a possibility of having multiple instances of
	// A1 running simultaneously, this would break; you'd want to make
	// this into instance fields of A1.
	static bool showTestWindow(false);
	static bool showDebugWindow(true);

	ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
	float opacity(0.5f);

	ImGui::Begin("Debug Window", &showDebugWindow, ImVec2(100,100), opacity, windowFlags);
		if( ImGui::Button( "Quit Application" ) ) {
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}

		// Eventually you'll create multiple colour widgets with
		// radio buttons.  If you use PushID/PopID to give them all
		// unique IDs, then ImGui will be able to keep them separate.
		// This is unnecessary with a single colour selector and
		// radio button, but I'm leaving it in as an example.

		// Prefixing a widget name with "##" keeps it from being
		// displayed.

		ImGui::PushID( 0 );

		
		if( ImGui::RadioButton( "Cube color", &current_col, 0 ) ) {
			colour[0] = color_cube.r;
			colour[1] = color_cube.g;
			colour[2] = color_cube.b;
		}
		if( ImGui::RadioButton( "Floor color", &current_col, 1 ) ) {
			colour[0] = color_floor.r;
			colour[1] = color_floor.g;
			colour[2] = color_floor.b;
		}
		if( ImGui::RadioButton( "Avatar color", &current_col, 2 ) ) {
			colour[0] = color_avatar.r;
			colour[1] = color_avatar.g;
			colour[2] = color_avatar.b;
		}

		ImGui::SliderFloat("Red Channel", &colour[0], 0.0f, 1.0f);
		ImGui::SliderFloat("Green Channel", &colour[1], 0.0f, 1.0f);
		ImGui::SliderFloat("Blue Channel", &colour[2], 0.0f, 1.0f);


		switch(current_col){
			case 0:
				color_cube.r = colour[0];
				color_cube.g = colour[1];
				color_cube.b = colour[2];
				break;
			case 1:
				color_floor.r = colour[0];
				color_floor.g = colour[1];
				color_floor.b = colour[2];
				break;
			case 2:
				color_avatar.r = colour[0];
				color_avatar.g = colour[1];
				color_avatar.b = colour[2];
		}
		ImGui::PopID();

/*
		// For convenience, you can uncomment this to show ImGui's massive
		// demonstration window right in your application.  Very handy for
		// browsing around to get the widget you want.  Then look in 
		// shared/imgui/imgui_demo.cpp to see how it's done.
		if( ImGui::Button( "Test Window" ) ) {
			showTestWindow = !showTestWindow;
		}
*/
		if( ImGui::Button( "Dig" ) ) {
			updateCubes();
		}

		if( ImGui::Button( "Reset" ) ) {
			reset();
		}

		ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );

	ImGui::End();

	if( showTestWindow ) {
		ImGui::ShowTestWindow( &showTestWindow );
	}
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A1::draw()
{
	// Create a global transformation for the model (centre it).
	mat4 W;
	if(persistence){
			rotation += prev_movement;
			
	}else{
			prev_movement = 0;
	}
	W = glm::rotate(W, rotation, glm::vec3(0, 1.0f, 0));
	
	W = glm::translate( W, vec3( -float(DIM)/2.0f, 0, -float(DIM)/2.0f ) );
	
	W = glm::scale(W, glm::vec3(scale,scale,scale));

	m_shader.enable();
		glEnable( GL_DEPTH_TEST );

		glUniformMatrix4fv( P_uni, 1, GL_FALSE, value_ptr( proj ) );
		glUniformMatrix4fv( V_uni, 1, GL_FALSE, value_ptr( view ) );
		glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( W ) );

		// Just draw the grid for now.
		glBindVertexArray( m_grid_vao );
		glUniform3f( col_uni, 1, 1, 1 );
		glDrawArrays( GL_LINES, 0, (3+DIM)*4 );

		// Draw the cubes
		drawFloor();


		if(minfo != nullptr){
			drawCubes(W);
		}
		
		drawAvatar(W);

	m_shader.disable();

	// Restore defaults
	glBindVertexArray( 0 );

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A1::cleanup()
{}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A1::cursorEnterWindowEvent (
		int entered
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse cursor movement events.
 */
bool A1::mouseMoveEvent(double xPos, double yPos) 
{
	bool eventHandled(false);

	if (!ImGui::IsMouseHoveringAnyWindow()) {
		// Put some code here to handle rotations.  Probably need to
		// check whether we're *dragging*, not just moving the mouse.
		// Probably need some instance variables to track the current
		// rotation amount, and maybe the previous X position (so 
		// that you can rotate relative to the *change* in X.
		if(m_mouseButtonActive){
			rotation += (xPos - prev_m_x) * 0.01;
			prev_movement = (xPos - prev_m_x) * 0.01;
			prev_m_x = xPos;
			
		}else{
			persistence = 1;
			prev_m_x = xPos;
		}

	}

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A1::mouseButtonInputEvent(int button, int actions, int mods) {
	bool eventHandled(false);

	if (!ImGui::IsMouseHoveringAnyWindow()) {
		// The user clicked in the window.  If it's the left
		// mouse button, initiate a rotation.
		if (actions == GLFW_PRESS) {
			m_mouseButtonActive = true;
			if(persistence){
				persistence = 0;
			}
		}
	

		if (actions == GLFW_RELEASE) {
			m_mouseButtonActive = false;
			persistence = 0;
		}

	}

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A1::mouseScrollEvent(double xOffSet, double yOffSet) {
	bool eventHandled(false);

	// Zoom in or out.

	scale += yOffSet*0.1;
	if(scale < 0.5f){
		scale = 0.5f;
	}

	if(scale > 1.5f){
		scale = 1.5f;
	}
	eventHandled = true;

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool A1::windowResizeEvent(int width, int height) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A1::keyInputEvent(int key, int action, int mods) {
	bool eventHandled(false);

	// Fill in with event handling code...
	if( action == GLFW_PRESS ) {
		// Respond to some key events.

		// increate/decrease height
		if (key == GLFW_KEY_SPACE){

			eventHandled = true;

			cube_height += 1.0f;
		} 

		if (key == GLFW_KEY_BACKSPACE){

			eventHandled = true;

			if ( cube_height > 1.0f){
				cube_height -= 1.0f;
			}
		} 

		//exit program
		if (key == GLFW_KEY_Q){

			eventHandled = true;

			glfwSetWindowShouldClose(m_window, GL_TRUE);
		} 

		// Avator movement

		if(key == GLFW_KEY_LEFT){
			eventHandled = true;
			moveAvator(0);
		}

		if(key == GLFW_KEY_RIGHT){
			eventHandled = true;
			moveAvator(1);
		}

		if(key == GLFW_KEY_UP){
			eventHandled = true;
			moveAvator(2);
		}

		if(key == GLFW_KEY_DOWN){
			eventHandled = true;
			moveAvator(3);
		}

		if(key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT){
			eventHandled = true;
			shiftheld = true;
		}

		// reset 
		if (key == GLFW_KEY_R){
			eventHandled = true;
			reset();
		}

		// reset 
		if (key == GLFW_KEY_D){
			eventHandled = true;
			updateCubes();
		}
		
	}

	if(action == GLFW_RELEASE){
		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT){
			eventHandled = true;
			shiftheld = false;
		}
	}

	return eventHandled;
}


//----------------------------------------------------------------------------------------
/*
 * Helper function. Delete previous maze info(if not null). And dig new maze
 */

void A1::updateCubes(){
	// delete maze if exits
	if(minfo==nullptr){
		minfo = new Maze(DIM);
		minfo->digMaze();
		initCubes();
	}
	else{
		delete minfo;
		minfo = new Maze(DIM);
		minfo->digMaze();
	}

	
	avatar_X = 0;
	avatar_Y = minfo->getStartY();
}

//----------------------------------------------------------------------------------------
/*
 * function to initilize cubes.
 */

void A1::initCubes(){

	cube_height = 1.0f;


	// Create the vertex array to record buffer assignments.
	glGenVertexArrays( 1, &m_cube_vao );
	glBindVertexArray( m_cube_vao );

	// Create the cube vertex buffer
	glGenBuffers( 1, &m_cube_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, m_cube_vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(cube_vertex),
		cube_vertex, GL_STATIC_DRAW );

	glGenBuffers(1, &m_cube_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cube_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( face_indice ), face_indice, GL_STATIC_DRAW);

	// Specify the means of extracting the position values properly.
	GLint posAttrib = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	// Reset state to prevent rogue code from messing with *my* 
	// stuff!
	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );


	CHECK_GL_ERRORS;
}
//----------------------------------------------------------------------------------------
/*
 * function to draw cubes.
 */
void A1::drawCubes(glm::mat4 W){
	
	for(int i = 0 ; i < DIM; i++){
		for(int j = 0 ; j < DIM; j++){
			if(!minfo->getValue(i, j)) continue;
			// add height
			for(float k = 0.0f; k < cube_height ; k++){
				glUniform3f(col_uni, color_cube.r, color_cube.g, color_cube.b);
				W = glm::translate( W, vec3( i + 0.5f, k, j + 0.5f) );
				glUniformMatrix4fv( M_uni, 1, GL_FALSE, value_ptr( W ) );
				glBindVertexArray(m_cube_vao);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
				W = glm::translate( W, vec3( -(i + 0.5f), -k, -(j + 0.5f)) );

				glBindVertexArray(0);
			}
			
		}
	}
}


//----------------------------------------------------------------------------------------
/*
 * function to ini Avator.
 */
void A1::initAvator(){
	avatar_X = 0.0f;
	avatar_Y = 0.0f;
}


//----------------------------------------------------------------------------------------
/*
 * function to draw Avator.
 */
void A1::drawAvatar(glm::mat4 W){

	// Create the vertex array to record buffer assignments.
	glGenVertexArrays( 1, &m_avator_vao );
	glBindVertexArray( m_avator_vao );

	// Create the cube vertex buffer
	glGenBuffers( 1, &m_avator_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, m_avator_vbo );

	// Specify the means of extracting the position values properly.
	GLint posAttrib = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray( posAttrib );

	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr );


	glUniform3f(col_uni, color_avatar.r, color_avatar.g, color_avatar.b);
	W = glm::translate(W, vec3(avatar_X + 0.5f, 0.5f, avatar_Y + 0.5f));
	CHECK_GL_ERRORS;

	float R = 0.3f;
	int stack_amt = 20;
	float stack_angle = (float) (M_PI / stack_amt);
	int slice_amt = 50;
	float slice_angle = (float) ( 2 *M_PI / slice_amt);

	float x0, x1, x2, x3, y1, y2, y3, y0, z1, z2, z3, z0; 
	float alpha_x = 0.0f;
	float alpha_z = 0.0f;

	for( int i = 0;i < stack_amt;i++ ){

		alpha_z = (float) (i * stack_angle);

		float rsinz = R*sin(alpha_z);
		float rsinznext = R * sin(alpha_z + stack_angle);
		float z0 = R * cos(alpha_z);

		for( int j = 0;j < slice_amt; j++ ){
			alpha_x = j * slice_angle;

			x0 = rsinz * cos(alpha_x);
			x1 = rsinznext * cos(alpha_x);
			x2 = rsinznext * cos(alpha_x + slice_angle);
			x3 = rsinz * cos(alpha_x + slice_angle);


			y0 = rsinz * sin(alpha_x);
			y1 = rsinznext * sin(alpha_x);
			y2 = rsinznext * sin(alpha_x + slice_angle);
			y3 = rsinz * sin(alpha_x + slice_angle);

			z0 = z0;
			z1 = R * cos(alpha_z + stack_angle);
			z2 = z1;
			z3 = z0;

			GLfloat coordsList[] = {
				x0, y0, z0,
				x1, y1, z1,
				x2, y2, z2,
				x2, y2, z2,
				x3, y3, z3,
				x1, y1, z1,
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(coordsList), coordsList, GL_STATIC_DRAW);

			glBindVertexArray(m_avator_vao);

			glUniformMatrix4fv(M_uni, 1, GL_FALSE, value_ptr(W));
			CHECK_GL_ERRORS;
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			glBindVertexArray(0);

		}	
		
	}

	W = glm::translate(W, vec3(-avatar_X - 0.5f, - 0.5f, - avatar_Y - 0.5f));
	glBindVertexArray(0);
	CHECK_GL_ERRORS;

}

//----------------------------------------------------------------------------------------
/*
 * function to move Avator.
 */
void A1::moveAvator(int direction){
	// 0 for left; 1 for right; 2 for down; 3 for up
	int avatar_X_int = (int)avatar_X;
	int avatar_Y_int = (int)avatar_Y;

	if(minfo == nullptr){
		switch(direction){
			case 0: // move left

				if(avatar_X_int > 0 ){

					avatar_X -= 1;
				}
				break;
			case 1: // move right

				if(avatar_X_int < (DIM - 1)){

					avatar_X += 1;
				}
				break;
			case 2: // move down

				if(avatar_Y_int > 0 ){

					avatar_Y -= 1;
				}
				break;
			case 3: // move up

				if(avatar_Y_int < (DIM - 1) ){

					avatar_Y += 1;
				}
				break;
		}
	}else{
		switch(direction){
			case 0: // move left

				if(avatar_X_int > 0 && (!minfo->getValue(avatar_X_int - 1, avatar_Y_int) || shiftheld == 1)){

					avatar_X -= 1;
					if(minfo->getValue(avatar_X_int - 1, avatar_Y_int)){
						minfo->setValue(avatar_X_int - 1, avatar_Y_int, 0);
					}
				}
				break;
			case 1: // move right

				if(avatar_X_int < (DIM - 1) && (!minfo->getValue(avatar_X_int + 1, avatar_Y_int) || shiftheld == 1)){

					avatar_X += 1;
					if(minfo->getValue(avatar_X_int + 1, avatar_Y_int)){
						minfo->setValue(avatar_X_int + 1, avatar_Y_int, 0);
					}
				}
				break;
			case 2: // move down

				if(avatar_Y_int > 0 && (!minfo->getValue(avatar_X_int, avatar_Y_int - 1) || shiftheld == 1)){

					avatar_Y -= 1;
					if(minfo->getValue(avatar_X_int, avatar_Y_int - 1)){
						minfo->setValue(avatar_X_int, avatar_Y_int - 1, 0);
					}
				}
				break;
			case 3: // move up

				if(avatar_Y_int < (DIM - 1) && (!minfo->getValue(avatar_X_int, avatar_Y_int + 1) || shiftheld == 1)){

					avatar_Y += 1;
					if(minfo->getValue(avatar_X_int, avatar_Y_int + 1)){
						minfo->setValue(avatar_X_int, avatar_Y_int + 1, 0);
					}
				}
				break;
		}
	}
	
}


void A1::drawFloor(){

	glUniform3f(col_uni, color_floor.r, color_floor.g, color_floor.b);
	glGenVertexArrays( 1, &m_floor_vao );
	glBindVertexArray( m_floor_vao );

	// Create the cube vertex buffer
	glGenBuffers( 1, &m_floor_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, m_floor_vbo );
	glBufferData( GL_ARRAY_BUFFER, 18*sizeof(float),
		floor_vertex, GL_STATIC_DRAW );

	// Specify the means of extracting the position values properly.
	GLint posAttrib = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr );

	glDrawArrays( GL_TRIANGLES, 0, 6 );


	// Reset state to prevent rogue code from messing with *my* 
	// stuff!
	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	
}