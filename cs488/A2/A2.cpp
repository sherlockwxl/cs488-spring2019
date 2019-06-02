// Spring 2019

#include "A2.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include <iostream>
#include <utility> 
#include <math.h>
using namespace std;

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
using namespace glm;

pair<int, int> cubeIndexPair[12] = {
	{0, 1},
	{0, 3},
	{0, 4},
	{1, 2},
	{1, 5},
	{2, 3},
	{2, 6},
	{3, 7},
	{4, 5},
	{4, 7},
	{5, 6},
	{6, 7},
}; 

pair<int, int> axisIndexPair[3] = {
	{0, 1},
	{0, 2},
	{0, 3},
}; 
static const glm::vec3 cube_vertex[8]=
{
	//bot x z y(-1)
	glm::vec3(-1.0f,  -1.0f, -1.0f), //0
	glm::vec3(-1.0f,  -1.0f,  1.0f), //1
	glm::vec3( 1.0f,  -1.0f,  1.0f), //2
	glm::vec3( 1.0f,  -1.0f, -1.0f), //3
	//top
	glm::vec3(-1.0f,  1.0f,  -1.0f), //4
	glm::vec3(-1.0f,  1.0f,   1.0f), //5
	glm::vec3( 1.0f,  1.0f,   1.0f), //6
	glm::vec3( 1.0f,  1.0f,  -1.0f), //7
	//bot x z y(-1)
	/*glm::vec3(-1.0f,  -1.0f, -1.0f),
	glm::vec3(-1.0f,   1.0f, -1.0f),
	glm::vec3(1.0f,   1.0f, -1.0f),
	glm::vec3(1.0f,  -1.0f, -1.0f),
	//top
	glm::vec3(-1.0f,  -1.0f,  1.0f),
	glm::vec3(-1.0f,   1.0f,  1.0f),
	glm::vec3(1.0f,   1.0f,  1.0f),
	glm::vec3(1.0f,  -1.0f,  1.0f),*/
};


//----------------------------------------------------------------------------------------
// Constructor
VertexData::VertexData()
	: numVertices(0),
	  index(0)
{
	positions.resize(kMaxVertices);
	colours.resize(kMaxVertices);
}


//----------------------------------------------------------------------------------------
// Constructor
A2::A2()
	: m_currentLineColour(vec3(0.0f))
{
	

}

//----------------------------------------------------------------------------------------
// Destructor
A2::~A2()
{

}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A2::init()
{
	// Set the background colour.
	glClearColor(0.3, 0.5, 0.7, 1.0);

	createShaderProgram();

	glGenVertexArrays(1, &m_vao);

	enableVertexAttribIndices();

	generateVertexBuffers();

	mapVboDataToVertexAttributeLocation();

	reset();

}

//----------------------------------------------------------------------------------------
void A2::createShaderProgram()
{
	m_shader.generateProgramObject();
	m_shader.attachVertexShader( getAssetFilePath("VertexShader.vs").c_str() );
	m_shader.attachFragmentShader( getAssetFilePath("FragmentShader.fs").c_str() );
	m_shader.link();
}

//---------------------------------------------------------------------------------------- Winter 2019
void A2::enableVertexAttribIndices()
{
	glBindVertexArray(m_vao);

	// Enable the attribute index location for "position" when rendering.
	GLint positionAttribLocation = m_shader.getAttribLocation( "position" );
	glEnableVertexAttribArray(positionAttribLocation);

	// Enable the attribute index location for "colour" when rendering.
	GLint colourAttribLocation = m_shader.getAttribLocation( "colour" );
	glEnableVertexAttribArray(colourAttribLocation);

	// Restore defaults
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
void A2::generateVertexBuffers()
{
	// Generate a vertex buffer to store line vertex positions
	{
		glGenBuffers(1, &m_vbo_positions);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);

		// Set to GL_DYNAMIC_DRAW because the data store will be modified frequently.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * kMaxVertices, nullptr,
				GL_DYNAMIC_DRAW);


		// Unbind the target GL_ARRAY_BUFFER, now that we are finished using it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}

	// Generate a vertex buffer to store line colors
	{
		glGenBuffers(1, &m_vbo_colours);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colours);

		// Set to GL_DYNAMIC_DRAW because the data store will be modified frequently.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * kMaxVertices, nullptr,
				GL_DYNAMIC_DRAW);


		// Unbind the target GL_ARRAY_BUFFER, now that we are finished using it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}
}

//----------------------------------------------------------------------------------------
void A2::mapVboDataToVertexAttributeLocation()
{
	// Bind VAO in order to record the data mapping.
	glBindVertexArray(m_vao);

	// Tell GL how to map data from the vertex buffer "m_vbo_positions" into the
	// "position" vertex attribute index for any bound shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
	GLint positionAttribLocation = m_shader.getAttribLocation( "position" );
	glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Tell GL how to map data from the vertex buffer "m_vbo_colours" into the
	// "colour" vertex attribute index for any bound shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colours);
	GLint colorAttribLocation = m_shader.getAttribLocation( "colour" );
	glVertexAttribPointer(colorAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//---------------------------------------------------------------------------------------
void A2::initLineData()
{
	m_vertexData.numVertices = 0;
	m_vertexData.index = 0;
}

//---------------------------------------------------------------------------------------
void A2::setLineColour (
		const glm::vec3 & colour
) {
	m_currentLineColour = colour;
}

//---------------------------------------------------------------------------------------
void A2::drawLine(
		const glm::vec2 & V0,   // Line Start (NDC coordinate)
		const glm::vec2 & V1    // Line End (NDC coordinate)
) {

	m_vertexData.positions[m_vertexData.index] = V0;
	m_vertexData.colours[m_vertexData.index] = m_currentLineColour;
	++m_vertexData.index;
	m_vertexData.positions[m_vertexData.index] = V1;
	m_vertexData.colours[m_vertexData.index] = m_currentLineColour;
	++m_vertexData.index;

	m_vertexData.numVertices += 2;
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A2::appLogic()
{
	// Place per frame, application logic here ...

	// Call at the beginning of frame, before drawing lines:
	initLineData();


	// execute pipeline handler draw the cube
	pieplineHandler();

	// draw the viewpoint

	setLineColour(vec3(0.2f, 1.0f, 1.0f));
	drawLine(vp1, vec2(vp1.x, vp2.y));//top
	drawLine(vp1, vec2(vp2.x, vp1.y));//left
	drawLine(vp2, vec2(vp1.x, vp2.y));//right
	drawLine(vp2, vec2(vp2.x, vp1.y));//bot

	// draw the model frames
	// Step 1 process model transfter base vec into model then view
	// transfer base, x, y, z
	setLineColour(vec3(0.5f, 1.0f, 0.8f));
	glm::vec4 model_base_0 = viewTransfer * modelTransfer * base_0;
	glm::vec4 model_base_x = viewTransfer * modelTransfer * base_x;
	glm::vec4 model_base_y = viewTransfer * modelTransfer * base_y;
	glm::vec4 model_base_z = viewTransfer * modelTransfer * base_z;
	//FrameHandler(model_base_0, model_base_x, model_base_y, model_base_z);

	// draw the whole model
	setLineColour(vec3(0.9f, 0.5f, 0.1f));
	glm::vec4 world_base_0 = viewTransfer *  base_0;
	glm::vec4 world_base_x = viewTransfer *  base_x;
	glm::vec4 world_base_y = viewTransfer *  base_y;
	glm::vec4 world_base_z = viewTransfer *  base_z;
	//FrameHandler(world_base_0, world_base_x, world_base_y, world_base_z);


}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A2::guiLogic()
{
	static bool firstRun(true);
	if (firstRun) {
		ImGui::SetNextWindowPos(ImVec2(50, 50));
		firstRun = false;
	}

	static bool showDebugWindow(true);
	ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
	float opacity(0.5f);

	ImGui::Begin("Properties", &showDebugWindow, ImVec2(100,100), opacity,
			windowFlags);


		// Add more gui elements here here ...


		// Create Button, and check if it was clicked:
		if( ImGui::Button( "Quit Application" ) ) {
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}

		ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );

	ImGui::End();
}

//----------------------------------------------------------------------------------------
void A2::uploadVertexDataToVbos() {

	//-- Copy vertex position data into VBO, m_vbo_positions:
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec2) * m_vertexData.numVertices,
				m_vertexData.positions.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}

	//-- Copy vertex colour data into VBO, m_vbo_colours:
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_colours);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * m_vertexData.numVertices,
				m_vertexData.colours.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		CHECK_GL_ERRORS;
	}
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A2::draw()
{
	uploadVertexDataToVbos();

	glBindVertexArray(m_vao);

	m_shader.enable();
		glDrawArrays(GL_LINES, 0, m_vertexData.numVertices);
	m_shader.disable();

	// Restore defaults
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A2::cleanup()
{

}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A2::cursorEnterWindowEvent (
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
bool A2::mouseMoveEvent (
		double xPos,
		double yPos
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A2::mouseButtonInputEvent (
		int button,
		int actions,
		int mods
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A2::mouseScrollEvent (
		double xOffSet,
		double yOffSet
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool A2::windowResizeEvent (
		int width,
		int height
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A2::keyInputEvent (
		int key,
		int action,
		int mods
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}


//----------------------------------------------------------------------------------------
/*
 * Pipeline handler, process the cube info and return vertexs ready for draw.
 */

void A2::pieplineHandler(){

	//cout<<" pipe line handler called"<<endl;


	// Step 1. Convert to vec4
	glm::vec4 cube_vec4_temp[8];
	for( int i = 0 ; i < 8 ; i++){
		cube_vec4_temp[i] = vec4(cube_vertex[i], 1.0f);
	}

	// Step 2. Modelling Transformations
	glm::vec4 cube_vec4_WCS[8];
	for( int i = 0 ; i < 8 ; i++){
		cube_vec4_WCS[i] = modelTransfer * cube_vec4_temp[i];
	};

	// Step 3. View Transformations

	glm::vec4 cube_vec4_VCS[8];
	for( int i = 0 ; i < 8 ; i++){
		cube_vec4_VCS[i] = viewTransfer * cube_vec4_WCS[i];
	};

	// Step 4. Projection and clipping

	// Step 4.1 Clipping

	// Step 4.1.1 trivial condition (both < near > far and reverse order for first z < second z)
	int easyClipFlag[12] = {0};  // 1 for pass; -1 for neg pass; 0 for fail
	for(int i = 0 ; i < 12; i++){
		easyClipFlag[i] = easyClipping(cube_vec4_VCS, cubeIndexPair, i);
	}

	// step 4.1.2 clip to two planes
	for (int i = 0;  i < 12 ; i++){
		
		if(easyClipFlag[i] == 0){
			continue;
		}

		pair<glm::vec4, glm::vec4 > currentPair;
		int firstIndex = cubeIndexPair[i].first;
		int secondIndex = cubeIndexPair[i].second;
		cout << "ori i : " << i << " " << cube_vertex[firstIndex] << " " <<  cube_vertex[secondIndex]<<endl;
		if(easyClipFlag[i] == 1){
			currentPair.first = cube_vec4_VCS[firstIndex];
			currentPair.second = cube_vec4_VCS[secondIndex];
		}else{// when second z > first z
			currentPair.first = cube_vec4_VCS[secondIndex];
			currentPair.second = cube_vec4_VCS[firstIndex];
		}
		
		cout << " start " << currentPair.first << " " << currentPair.second<< endl;
		// ini done
		// clip to two planes
		// clip to near plane, check second only since first.z > second.z
		if(currentPair.second.z < nearPlane){ // clip required
			currentPair.second = currentPair.second + 
				(currentPair.first - currentPair.second) * 
					(nearPlane - currentPair.second.z) / (
						currentPair.first.z - currentPair.second.z);
		}

		// clip to far plane, check first only since first.z > second.z
		if(currentPair.first.z > farPlane){ // clip required
			currentPair.first = currentPair.second + 
				(currentPair.first - currentPair.second) * 
					(farPlane - currentPair.second.z) / (
						currentPair.first.z - currentPair.second.z);
		}

		// first clip done

		// step 4.2 Projection
		// use easy approach x -> x/z y -> y/z for now
		pair<glm::vec2, glm::vec2 > displayPair;
		displayPair.first.x = (currentPair.first.x/currentPair.first.z)/(tan(fov/2.0f/180.0f*M_PI));
		displayPair.second.x = (currentPair.second.x/currentPair.second.z)/(tan(fov/2.0f/180.0f*M_PI));
		displayPair.first.y = (currentPair.first.y/currentPair.first.z)/(tan(fov/2.0f/180.0f*M_PI));
		displayPair.second.y = (currentPair.second.y/currentPair.second.z)/(tan(fov/2.0f/180.0f*M_PI));

		cout << " display " << displayPair.first << " " << displayPair.second<<endl;
		// projection done
		// step 4.3 clip to viewing volume
		// add helper function here
		bool needDraw = clipAndTtoViewPoint(displayPair);

		cout << " result " << needDraw<<endl;
		// draw line
		if(needDraw){
			setLineColour(vec3(0.2f, 1.0f, 1.0f));
			drawLine(displayPair.first, displayPair.second);
			cout<<"draw line "<< displayPair.first << " " <<displayPair.second<<endl;
		}
	}


}

void A2::FrameHandler(glm::vec4 new_base_0, glm::vec4 new_base_x, glm::vec4 new_base_y, glm::vec4 new_base_z){


	// Step 2 clipping (same as cube line clipping)
	// Step 2.1 easy clipping

	// Step 2.1.1 trivial condition (both < near > far and reverse order for first z < second z)
	glm::vec4 mode_frame_vec4_VCS[4];
	mode_frame_vec4_VCS[0] = new_base_0;
	mode_frame_vec4_VCS[1] = new_base_x;
	mode_frame_vec4_VCS[2] = new_base_y;
	mode_frame_vec4_VCS[3] = new_base_z;

	int easyClipFlag[3] = {0};  // 1 for pass; -1 for neg pass; 0 for fail
	
	for(int i = 0 ; i < 3; i++){
		easyClipFlag[i] = easyClipping(mode_frame_vec4_VCS, axisIndexPair, i);
	}

	// step 4.1.2 clip to two planes
	for (int i = 0;  i < 3 ; i++){
		if(easyClipFlag[i] == 0){
			continue;
		}

		pair<glm::vec4, glm::vec4 > currentPair;
		int firstIndex = axisIndexPair[i].first;
		int secondIndex = axisIndexPair[i].second;
		if(easyClipFlag[i] == 1){
			currentPair.first = mode_frame_vec4_VCS[firstIndex];
			currentPair.second = mode_frame_vec4_VCS[secondIndex];
		}else{// when second z > first z
			currentPair.first = mode_frame_vec4_VCS[secondIndex];
			currentPair.second = mode_frame_vec4_VCS[firstIndex];
		}
		// ini done
		// clip to two planes
		// clip to near plane, check second only since first.z > second.z
		if(currentPair.second.z < nearPlane){ // clip required
			currentPair.second = currentPair.second + 
				(currentPair.first - currentPair.second) * 
					(nearPlane - currentPair.second.z) / (
						currentPair.first.z - currentPair.second.z);
		}

		// clip to far plane, check first only since first.z > second.z
		if(currentPair.first.z > farPlane){ // clip required
			currentPair.first = currentPair.second + 
				(currentPair.first - currentPair.second) * 
					(farPlane - currentPair.second.z) / (
						currentPair.first.z - currentPair.second.z);
		}

		// first clip done

		// step 4.2 Projection
		// use easy approach x -> x/z y -> y/z for now
		pair<glm::vec2, glm::vec2 > displayPair;
		displayPair.first.x = (currentPair.first.x/currentPair.first.z)/(tan(fov/2.0f/180.0f*M_PI));
		displayPair.second.x = (currentPair.second.x/currentPair.second.z)/(tan(fov/2.0f/180.0f*M_PI));
		displayPair.first.y = (currentPair.first.y/currentPair.first.z)/(tan(fov/2.0f/180.0f*M_PI));
		displayPair.second.y = (currentPair.second.y/currentPair.second.z)/(tan(fov/2.0f/180.0f*M_PI));


		// projection done
		// step 4.3 clip to viewing volume
		// add helper function here
		bool needDraw = clipAndTtoViewPoint(displayPair);


		// draw line
		if(needDraw)
		drawLine(displayPair.first, displayPair.second);
	}


}


void A2::reset(){
	eye_origin = glm::vec3(5.0f, 2.0f, 10.0f);
	world_origin = glm::vec3(0.0f, 0.0f, 0.0f);
	cube_origin = glm::vec3(0.0f, 0.0f, 0.0f);

	modelTransfer = glm::mat4(
					glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), // x
					glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), // y 
					glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), // z
					glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); // w

	viewTransfer = calculateView();
	
	resetFOV();
	resetVP();
}

void A2::resetFOV(){
	nearPlane = 1.0f;
	farPlane = 20.0f;
	fov = 30.0f;
}

void A2::resetVP(){
	vp1 = glm::vec2(-0.9f, 0.9f);
	vp2 = glm::vec2( 0.9f, -0.9f);
}

int A2::easyClipping(glm::vec4 *cube_vec4_VCS, std::pair<int, int> *indexPair, int index){
	int res = 1;
	int firstIndex = indexPair[index].first;
	int secondIndex = indexPair[index].second;
	// trivial test
	if((cube_vec4_VCS[firstIndex].z < nearPlane && cube_vec4_VCS[secondIndex].z < nearPlane) ||
		(cube_vec4_VCS[firstIndex].z > farPlane && cube_vec4_VCS[secondIndex].z > farPlane))
		{
			// both points not within range should return 0;
			res = 0;
			return res;
		}

	// make sure first index has larger z value
	if(cube_vec4_VCS[firstIndex].z < cube_vec4_VCS[secondIndex].z){
		res = -1;
	}
	return res;
}

//----------------------------------------------------------------------------------------
/*
 *  view volume clipping and transfer to view point helper function.
 *  input pair 
 */
bool A2::clipAndTtoViewPoint(pair<glm::vec2, glm::vec2 > &input2DPair){

	vec2 P1 = input2DPair.first;
	vec2 P2 = input2DPair.second;

	GLfloat vp_tl_x, vp_tl_y, vp_br_x, vp_br_y;

	/*vp_tl_x = -1;
	vp_tl_y = 1;
	vp_br_x = 1;
	vp_br_y = -1;*/
	vp_tl_x = std::min(vp1.x, vp2.x);
	vp_tl_y = std::max(vp1.y, vp2.y);
	vp_br_x = std::max(vp1.x, vp2.x);
	vp_br_y = std::min(vp1.y, vp2.y);
	
	cout << " now clip " << P1 << " " << P2<<endl;

	// first clip to -1 , 1
	// first easy check 
	if((P1.x < vp_tl_x && P2.x < vp_tl_x) || // all left
		(P1.x > vp_br_x && P2.x > vp_br_x) || // all right
		(P1.y > vp_tl_y && P2.y > vp_tl_y) || // all top
		(P1.y < vp_br_y && P2.y < vp_br_y)) // all bot
		{
			cout << "fail test 1"<<endl;
			return false;
		}

	// Step 1. clip on x = vp_tl_x and vp_br_x
	sortTwoPoints(P1, P2, 0); // sort points base on x first

	// clip to vp_tl_x, check second only since P1.x > P2.x
	if(P2.x < vp_tl_x){ // clip required
			P2 = P2 + 
				(P1 - P2) * 
					(vp_tl_x - P2.x) / (
						P1.x - P2.x);
	}

	// clip to vp_br_x, check first only since P1.x > P2.x
	if(P1.x > vp_br_x){ // clip required
		P1 = P2 + 
			(P1 - P2) * 
				(vp_br_x - P2.x) / (
					P1.x - P2.x);
	}


	cout << " after clip x " << P1 << " " << P2<<endl;
	if((P1.x < vp_tl_x && P2.x < vp_tl_x) || // all left
		(P1.x > vp_br_x && P2.x > vp_br_x) || // all right
		(P1.y > vp_tl_y && P2.y > vp_tl_y) || // all top
		(P1.y < vp_br_y && P2.y < vp_br_y)) // all bot
		{
			cout << "fail test 2"<<endl;
			return false;
		}


	// Step 2. clip on y =  vp_tl_y and vp_br_y
	sortTwoPoints(P1, P2, 1); // sort points base on y 

	// clip to vp_br_y, check second only since P1.y > P2.y
	if(P2.y < vp_br_y){ // clip required
			P2 = P2 + 
				(P1 - P2) * 
					(vp_br_y - P2.y) / (
						P1.y - P2.y);
	}

	// clip to vp_tl_y, check first only since P1.y > P2.y
	if(P1.y > vp_tl_y){ // clip required
		P1 = P2 + 
			(P1 - P2) * 
				(vp_tl_y - P2.y) / (
					P1.y - P2.y);
	}


	cout << " after clip y " << P1 << " " << P2<<endl;

	if((P1.x < vp_tl_x && P2.x < vp_tl_x) || // all left
		(P1.x > vp_br_x && P2.x > vp_br_x) || // all right
		(P1.y > vp_tl_y && P2.y > vp_tl_y) || // all top
		(P1.y < vp_br_y && P2.y < vp_br_y)) // all bot
		{
			cout << "fail test 3"<<endl;
			return false;
		}


	// map to view port
	vp_tl_x = std::min(vp1.x, vp2.x);
	vp_tl_y = std::min(vp1.y, vp2.y);
	vp_br_x = std::max(vp1.x, vp2.x);
	vp_br_y = std::max(vp1.y, vp2.y);



	// clip done ready to draw
	/*input2DPair.first.x = (P1.x * (vp_br_x - vp_tl_x) + (vp_br_x + vp_tl_x) )/ 2.0f;
	input2DPair.first.y = (P1.y * (vp_tl_y - vp_br_y) + (vp_tl_y + vp_br_y) )/ 2.0f;
	input2DPair.second.x = (P2.x * (vp_br_x - vp_tl_x) + (vp_br_x + vp_tl_x) )/ 2.0f;
	input2DPair.second.y = (P2.y * (vp_tl_y - vp_br_y) + (vp_tl_y + vp_br_y) )/ 2.0f;*/

	input2DPair.first.x = P1.x;
	input2DPair.first.y = P1.y;
	input2DPair.second.x = P2.x;
	input2DPair.second.y = P2.y;
	
	return true;


}
/*
 *  helper function to sort two points base on x(base = 0) or y (base = 1); 
 */
void A2::sortTwoPoints(glm::vec2 &P1, glm::vec2 &P2, int base){
	if(base == 0){
		// sort on x let P1.x > P2.x
		if(P1.x > P2.x){
			return;
		}else{
			vec2 temp;
			temp.x = P1.x;
			temp.y = P1.y;
			P1.x = P2.x;
			P1.y = P2.y;
			P2.x = temp.x;
			P2.y = temp.y;
			return;
		}
	}else{
		// sort on y let P1.y > P2.y
		if(P1.y > P2.y){
			return;
		}else{
			vec2 temp;
			temp.x = P1.x;
			temp.y = P1.y;
			P1.x = P2.x;
			P1.y = P2.y;
			P2.x = temp.x;
			P2.y = temp.y;
			return;
		}
	}
}

// calculate worldtoview matrix follow uvn base
glm::mat4 A2::calculateView(){

	
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 new_z = glm::normalize(world_origin - eye_origin);
	glm::vec3 new_x = glm::normalize(glm::cross(up,new_z));
	glm::vec3 new_y = glm::normalize(glm::cross(new_z, new_x));

	glm::mat4 view = glm::mat4(
		glm::vec4(new_x.x, new_y.x, new_z.x, 0.0f),
		glm::vec4(new_x.y, new_y.y, new_z.y, 0.0f),
		glm::vec4(new_x.z, new_y.z, new_z.z, 0.0f),
		glm::vec4(-glm::dot(eye_origin,new_x), -glm::dot(eye_origin,new_y), -glm::dot(eye_origin,new_z), 1)
	);

	
	cout<<view<<endl;
	return view;
}