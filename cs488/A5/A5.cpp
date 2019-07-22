// Spring 2019

#include "A5.hpp"
#include "scene_lua.hpp"
#include "trackball.hpp"
using namespace std;

#include "cs488-framework/GlErrorCheck.hpp"
#include "cs488-framework/MathUtils.hpp"
#include "GeometryNode.hpp"
#include "JointNode.hpp"


#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>

// image loader for texture mapping
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;
using namespace irrklang;

static bool show_gui = true;

const size_t CIRCLE_PTS = 48;
const float platform_uv[] = {

  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,

  0.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 0.0f,

  // top face bot right
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  
  

  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 0.0f,


  0.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 0.0f,


  0.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 0.0f,


  0.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 1.0f,
  
  


  0.0f, 1.0f, //2
  0.0f, 0.0f, //6
  1.0f, 1.0f, //3


  0.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 1.0f,
  
  0.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,
  
  0.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 0.0f,

  // Top face top left
  0.0f, 1.0f,
  1.0f, 1.0f,
  0.0f, 0.0f
};

static const GLfloat vertices[] = {
0.5f,  0.5f,
0.5f, -0.5f,
-0.5f, -0.5f,
-0.5f, 0.5f,
0.5f,  0.5f
};
static const GLint face_indice[][3] = {
		// front
		0, 1, 2,
		1, 2, 3
};


//----------------------------------------------------------------------------------------
// Constructor
A5::A5(const std::string & luaSceneFile)
	: m_luaSceneFile(luaSceneFile),
	  m_positionAttribLocation(0),
	  m_normalAttribLocation(0),
	  m_vao_meshData(0),
	  m_vbo_vertexPositions(0),
	  m_vbo_vertexNormals(0),
	  m_vao_arcCircle(0),
	  m_vbo_arcCircle(0),
	  m_particle_positionAttribLocation(0),
	  m_vao_particle(0),
	  m_vbo_particle(0),
	  texture_count(0),
	  m_vbo_textureUV(0),
	  m_textureCoordsAttribLocation(0),
	  m_vao_c1(0),
	  m_vbo_bar_c1(0),
	  m_bar_c1_positionAttribLocation(0),
	  m_vao_c2(0),
	  m_vbo_bar_c2(0),
	  m_bar_c2_positionAttribLocation(0)


{
	animationModel = AnimationModel();
	keyFrameHandler = KeyFrameHandler();
	character_1 = Character();
	character_2 = Character();
	character_1.id = 1;
	character_2.id = 2;
	character_1.enemy = &character_2;
	character_2.enemy = &character_1;
	character_1.animationModel = &animationModel;
	character_2.animationModel = &animationModel;
	character_1.keyFrameHandler = &keyFrameHandler;
	character_2.keyFrameHandler = &keyFrameHandler;
	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	particleModel = ParticleModel(1.0f, color);
	SoundEngine = createIrrKlangDevice();
    backGroundSound = SoundEngine->play2D("Assets/background.wav", GL_TRUE);
	gamestage = 0;
	hard_c1 = 0; // 0 for default 1 for medium 2 for hard
	hard_c2 = 0; // 0 for default 1 for medium 2 for hard
	speed_c1 = 1.0f; // 0.5 ~ 1.5
	speed_c2 = 1.0f; // 0.5 ~ 1.5
	display_shadow = true;
	display_texture = true;
	lose = 0;

}

//----------------------------------------------------------------------------------------
// Destructor
A5::~A5()
{
}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A5::init()
{	
	// Set the background colour.
	glClearColor(0.45, 0.45, 0.45, 1.0);

	createShaderProgram();

	glGenVertexArrays(1, &m_vao_arcCircle);
	glGenVertexArrays(1, &m_vao_meshData);
	glGenVertexArrays(1, &m_vao_particle);
	glGenVertexArrays(1, &m_vao_c1);
	glGenVertexArrays(1, &m_vao_c2);
	enableVertexShaderInputSlots();

	processLuaSceneFile(m_luaSceneFile);

	// process texture file
	loadTexture("Assets/asphalt.jpg");
	loadTexture("Assets/container.jpg");
	loadTexture("Assets/fighter_background_2.jpg");
	instructionId = loadTexture2("Assets/instruction.jpg");

	// Load and decode all .obj files at once here.  You may add additional .obj files to
	// this list in order to support rendering additional mesh types.  All vertex
	// positions, and normals will be extracted and stored within the MeshConsolidator
	// class.
	unique_ptr<MeshConsolidator> meshConsolidator (new MeshConsolidator{
			getAssetFilePath("cube.obj"),
			getAssetFilePath("sphere.obj"),
			getAssetFilePath("suzanne.obj")
	});


	// Acquire the BatchInfoMap from the MeshConsolidator.
	meshConsolidator->getBatchInfoMap(m_batchInfoMap);

	// Take all vertex data within the MeshConsolidator and upload it to VBOs on the GPU.
	uploadVertexDataToVbos(*meshConsolidator);

	mapVboDataToVertexShaderInputLocations();

	initPerspectiveMatrix();

	initViewMatrix();

	initLightSources();


	// Exiting the current scope calls delete automatically on meshConsolidator freeing
	// all vertex data resources.  This is fine since we already copied this data to
	// VBOs on the GPU.  We have no use for storing vertex data on the CPU side beyond
	// this point.

	// backup ini translation
	ini_translation = m_rootNode->trans;

	// reset all variables abd mouse location
	resetAll();

	// Extra ini for A5
	initAnimationModel();
	initDepthMap();
	initTexture();



}

//----------------------------------------------------------------------------------------
void A5::processLuaSceneFile(const std::string & filename) {
	// This version of the code treats the Lua file as an Asset,
	// so that you'd launch the program with just the filename
	// of a puppet in the Assets/ directory.
	// std::string assetFilePath = getAssetFilePath(filename.c_str());
	// m_rootNode = std::shared_ptr<SceneNode>(import_lua(assetFilePath));

	// This version of the code treats the main program argument
	// as a straightforward pathname.
	m_rootNode = std::shared_ptr<SceneNode>(import_lua(filename));

	

	// get the total node
	totalNode = m_rootNode->totalSceneNodes();
	root_ori = m_rootNode->trans*vec4(0.0f, 0.0f, 0.0f, 1.0f);
	root_ori_m =  m_rootNode->trans;
	// get the index of all joint node
	for(int id = 0 ; id < totalNode; id++){
		SceneNode * node = findNodeById(*m_rootNode, id);
		if(node->m_name == "head"){
			head_id = id;
		}
		if(node->m_name == "platform"){
			character_1.ground_Node = std::shared_ptr<SceneNode>(node);
			character_2.ground_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "platform_back"){
			character_1.back_Node = std::shared_ptr<SceneNode>(node);
			character_2.back_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "platform_left"){
			character_1.left_Node = std::shared_ptr<SceneNode>(node);
			character_2.left_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "platform_right"){
			character_1.right_Node = std::shared_ptr<SceneNode>(node);
			character_2.right_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "platform_front"){
			character_1.front_Node = std::shared_ptr<SceneNode>(node);
			character_2.front_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "torso"){
			GLfloat angel = 3.141592f * 0.5f;
			glm::mat4 y_rotateMatrix = glm::rotate(mat4(), angel, vec3(0.0f, 1.0f, 0.0f));
			recursiveRotate(node->trans, *node, y_rotateMatrix);
			Left_rootNode = std::shared_ptr<SceneNode>(node);
			character_1.m_rootNode = Left_rootNode;
			character_2.other_rootNode = Left_rootNode;
			character_1.ori_trans = Left_rootNode->trans;
		}
		if(node->m_name == "leftFoot"){
			character_1.leftFoot_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "rightFoot"){
			character_1.rightFoot_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "torso_baymax"){
			GLfloat angel = 3.141592f * 1.5f;
			glm::mat4 y_rotateMatrix = glm::rotate(mat4(), angel, vec3(0.0f, 1.0f, 0.0f));
			recursiveRotate(node->trans, *node, y_rotateMatrix);
			Right_rootNode = std::shared_ptr<SceneNode>(node);
			character_2.m_rootNode = Right_rootNode;
			character_1.other_rootNode = Right_rootNode;
			character_2.ori_trans = Right_rootNode->trans;
		}
		if(node->m_name == "leftFoot_baymax"){
			character_2.leftFoot_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_name == "rightFoot_baymax"){
			character_2.rightFoot_Node = std::shared_ptr<SceneNode>(node);
		}
		if(node->m_nodeType == NodeType::JointNode){
			jointIndex.push(id);
		}
	}
	for(int id = 0; id < totalNode; id++){
		SceneNode * node = findNodeById(*character_1.m_rootNode, id);
		if(node != NULL){
			if(node->m_nodeType == NodeType::GeometryNode){
				character_1.geoIndexVector.push_back(id);
				character_2.other_geoIndexVector.push_back(id);
			}
			if(node->m_nodeType == NodeType::JointNode){
				jointIndex_c1.push(id);
			}
		}
	}
	for(int id = 0; id < totalNode; id++){
		SceneNode * node = findNodeById(*character_2.m_rootNode, id);
		if(node != NULL){
			if(node->m_nodeType == NodeType::GeometryNode){
				character_2.geoIndexVector.push_back(id);
				character_1.other_geoIndexVector.push_back(id);
			}
			if(node->m_nodeType == NodeType::JointNode){
				jointIndex_c2.push(id);
			}
		}
	}
	// push all joint node index into vector for easy access
	while(!jointIndex.empty()) {
        jointIndexVector.push_back(jointIndex.top());
        jointIndex.pop();
    }

	// push joint node id for both characters
	while(!jointIndex_c1.empty()) {
        jointIndexVector_c1.push_back(jointIndex_c1.top());
        jointIndex_c1.pop();
    }
	while(!jointIndex_c2.empty()) {
        jointIndexVector_c2.push_back(jointIndex_c2.top());
        jointIndex_c2.pop();
    }

	// store all ori angle
	for(auto const& id: jointIndexVector) {
		SceneNode * node = findNodeById(*m_rootNode, id);
		JointNode * jointNode = static_cast<JointNode*>(node);
		ori_joint_angle.push_back(jointNode->m_joint_x.init);
	}
	ori_joint_angle.push_back(head_rotation);

	// back up joint angle for each character
	for(auto const& id: jointIndexVector_c1) {
		SceneNode * node = findNodeById(*m_rootNode, id);
		JointNode * jointNode = static_cast<JointNode*>(node);
		character_1.ori_joint_angle.push_back(glm::vec3(jointNode->m_joint_x.init,jointNode->m_joint_y.init,jointNode->m_joint_z.init));
	}
	for(auto const& id: jointIndexVector_c2) {
		SceneNode * node = findNodeById(*m_rootNode, id);
		JointNode * jointNode = static_cast<JointNode*>(node);
		character_2.ori_joint_angle.push_back(glm::vec3(jointNode->m_joint_x.init,jointNode->m_joint_y.init,jointNode->m_joint_z.init));
	}

	if (!m_rootNode) {
		std::cerr << "Could Not Open " << filename << std::endl;
	}
	
}

//----------------------------------------------------------------------------------------
void A5::createShaderProgram()
{
	m_shader.generateProgramObject();
	m_shader.attachVertexShader( getAssetFilePath("VertexShader.vs").c_str() );
	m_shader.attachFragmentShader( getAssetFilePath("FragmentShader.fs").c_str() );
	m_shader.link();

	m_shader_arcCircle.generateProgramObject();
	m_shader_arcCircle.attachVertexShader( getAssetFilePath("arc_VertexShader.vs").c_str() );
	m_shader_arcCircle.attachFragmentShader( getAssetFilePath("arc_FragmentShader.fs").c_str() );
	m_shader_arcCircle.link();

	// add particle shader program
	m_shader_particle.generateProgramObject();
	m_shader_particle.attachVertexShader( getAssetFilePath("VertexShader.vs").c_str() );
	m_shader_particle.attachFragmentShader( getAssetFilePath("particle_FragmentShader.fs").c_str() );
	m_shader_particle.link();

	m_shader_depthMap.generateProgramObject();
	m_shader_depthMap.attachVertexShader( getAssetFilePath("depthMap_VertexShader.vs").c_str() );
	m_shader_depthMap.attachFragmentShader( getAssetFilePath("depthMap_FragmentShader.fs").c_str() );
	m_shader_depthMap.link();

	m_shader_bar_c1.generateProgramObject();
	m_shader_bar_c1.attachVertexShader( getAssetFilePath("bar_VertexShader.vs").c_str() );
	m_shader_bar_c1.attachFragmentShader( getAssetFilePath("bar_FragmentShader.fs").c_str() );
	m_shader_bar_c1.link();

	m_shader_bar_c2.generateProgramObject();
	m_shader_bar_c2.attachVertexShader( getAssetFilePath("bar_VertexShader.vs").c_str() );
	m_shader_bar_c2.attachFragmentShader( getAssetFilePath("bar_FragmentShader.fs").c_str() );
	m_shader_bar_c2.link();

}

//----------------------------------------------------------------------------------------
void A5::enableVertexShaderInputSlots()
{
	//-- Enable input slots for m_vao_meshData:
	{
		glBindVertexArray(m_vao_meshData);

		// Enable the vertex shader attribute location for "position" when rendering.
		m_positionAttribLocation = m_shader.getAttribLocation("position");
		glEnableVertexAttribArray(m_positionAttribLocation);

		// Enable the vertex shader attribute location for "normal" when rendering.
		m_normalAttribLocation = m_shader.getAttribLocation("normal");
		glEnableVertexAttribArray(m_normalAttribLocation);

		// Enable the vertex shader attribute location for "textureUV" when rendering.
		m_textureCoordsAttribLocation = m_shader.getAttribLocation("textureUV");
		glEnableVertexAttribArray(m_textureCoordsAttribLocation);

		CHECK_GL_ERRORS;
	}


	//-- Enable input slots for m_vao_arcCircle:
	{
		glBindVertexArray(m_vao_arcCircle);

		// Enable the vertex shader attribute location for "position" when rendering.
		m_arc_positionAttribLocation = m_shader_arcCircle.getAttribLocation("position");
		glEnableVertexAttribArray(m_arc_positionAttribLocation);
		CHECK_GL_ERRORS;
	}

	//-- Enable input slots for m_vao_particle:
	{
		glBindVertexArray(m_vao_particle);

		// Enable the vertex shader attribute location for "position" when rendering.
		m_particle_positionAttribLocation = m_shader_particle.getAttribLocation("position");
		glEnableVertexAttribArray(m_particle_positionAttribLocation);
		
		CHECK_GL_ERRORS;
	}

	{
		glBindVertexArray(m_vao_c1);

		// Enable the vertex shader attribute location for "position" when rendering.
		m_bar_c1_positionAttribLocation = m_shader_bar_c1.getAttribLocation("position");
		glEnableVertexAttribArray(m_bar_c1_positionAttribLocation);
		
		CHECK_GL_ERRORS;
	}

	{
		glBindVertexArray(m_vao_c2);

		// Enable the vertex shader attribute location for "position" when rendering.
		m_bar_c2_positionAttribLocation = m_shader_bar_c2.getAttribLocation("position");
		glEnableVertexAttribArray(m_bar_c2_positionAttribLocation);
		
		CHECK_GL_ERRORS;
	}


	// Restore defaults
	glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------
void A5::uploadVertexDataToVbos (
		const MeshConsolidator & meshConsolidator
) {
	// Generate VBO to store all vertex position data
	{
		glGenBuffers(1, &m_vbo_vertexPositions);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexPositions);

		glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexPositionBytes(),
				meshConsolidator.getVertexPositionDataPtr(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
	}

	// Generate VBO to store all vertex normal data
	{
		glGenBuffers(1, &m_vbo_vertexNormals);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexNormals);

		glBufferData(GL_ARRAY_BUFFER, meshConsolidator.getNumVertexNormalBytes(),
				meshConsolidator.getVertexNormalDataPtr(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
	}

	// Generate VBO to store the trackball circle.
	{
		glGenBuffers( 1, &m_vbo_arcCircle );
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo_arcCircle );

		glBufferData(GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
	}

	// Generate VBO to store the particle.
	{

		static const GLfloat particle_data[] = {
		-0.66f, 0.66f, -0.66f,
		0.66f, 0.66f, 0.66f,
		-0.66f, 0.66f, 0.66f,
		0.66f, 0.66f, -0.66f,
		};

		glGenBuffers( 1, &m_vbo_particle );
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo_particle );

		glBufferData(GL_ARRAY_BUFFER, sizeof(particle_data), particle_data, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
	}

	{
		 
		glGenBuffers(1, &m_vbo_textureUV);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_textureUV);

		glBufferData(GL_ARRAY_BUFFER, sizeof(platform_uv), platform_uv, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
  
	}

	// Generate VBO to for the bar
	{
		static const GLfloat bar_data2[] = {
		0.0f,  0.0f, 1.0f,
		0.5f,  0.0f,1.0f,
		0.5f,  0.5f,1.0f,
		0.0f,  0.5f,1.0f,
		0.0f,  0.0f,1.0f
		};

		glGenBuffers( 1, &m_vbo_bar_c1 );
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo_bar_c1 );

		glBufferData(GL_ARRAY_BUFFER, sizeof( bar_data2 ), bar_data2, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
	}

	// Generate VBO to for the bar
	{
		static const GLfloat bar_data2[] = {
		0.0f,  0.0f, 1.0f,
		0.5f,  0.0f,1.0f,
		0.5f,  0.5f,1.0f,
		0.0f,  0.5f,1.0f,
		0.0f,  0.0f,1.0f
		};

		glGenBuffers( 1, &m_vbo_bar_c2 );
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo_bar_c2 );

		glBufferData(GL_ARRAY_BUFFER, sizeof( bar_data2 ), bar_data2, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERRORS;
	}
}

//----------------------------------------------------------------------------------------
void A5::mapVboDataToVertexShaderInputLocations()
{
	// Bind VAO in order to record the data mapping.
	glBindVertexArray(m_vao_meshData);

	// Tell GL how to map data from the vertex buffer "m_vbo_vertexPositions" into the
	// "position" vertex attribute location for any bound vertex shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexPositions);
	glVertexAttribPointer(m_positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Tell GL how to map data from the vertex buffer "m_vbo_vertexNormals" into the
	// "normal" vertex attribute location for any bound vertex shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertexNormals);
	glVertexAttribPointer(m_normalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_textureUV);
   glVertexAttribPointer(m_textureCoordsAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;

	// Bind VAO in order to record the data mapping.
	glBindVertexArray(m_vao_arcCircle);

	// Tell GL how to map data from the vertex buffer "m_vbo_arcCircle" into the
	// "position" vertex attribute location for any bound vertex shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_arcCircle);
	glVertexAttribPointer(m_arc_positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;

	// Add paticle System
	glBindVertexArray(m_vao_particle);

	// Tell GL how to map data from the vertex buffer "m_vbo_particle" into the
	// "position" vertex attribute location for any bound vertex shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_particle);
	glVertexAttribPointer(m_particle_positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;

	glBindVertexArray(m_vao_c1);
	// Tell GL how to map data from the vertex buffer "m_vbo_bar_c1" into the
	// "position" vertex attribute location for any bound vertex shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_bar_c1);
	glVertexAttribPointer(m_bar_c1_positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;

	glBindVertexArray(m_vao_c2);
	// Tell GL how to map data from the vertex buffer "m_vbo_bar_c1" into the
	// "position" vertex attribute location for any bound vertex shader program.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_bar_c2);
	glVertexAttribPointer(m_bar_c2_positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//-- Unbind target, and restore default values:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
void A5::initPerspectiveMatrix()
{
	float aspect = ((float)m_windowWidth) / m_windowHeight;
	m_perpsective = glm::perspective(degreesToRadians(60.0f), aspect, 0.1f, 100.0f);
}


//----------------------------------------------------------------------------------------
void A5::initViewMatrix() {
	m_view = glm::lookAt(vec3(0.0f, 3.0f, 6.0f), vec3(0.0f, 0.0f, -2.0f),
			vec3(0.0f, 1.0f, 0.0f));
}

//----------------------------------------------------------------------------------------
void A5::initLightSources() {
	// World-space position
	m_light.position = vec3(0.0f, 12.0f, 8.0f);
	m_light.rgbIntensity = vec3(1.0f); // light
	lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.0f, 40.0f);
	lightView = glm::lookAt(m_light.position, vec3(0.0f, 0.0f, 0.0f),
      vec3(0.0f, 1.0f, 0.0f));
}

//----------------------------------------------------------------------------------------
void A5::uploadCommonSceneUniforms() {
	m_shader.enable();
	{
		//-- Set Perpsective matrix uniform for the scene:
		GLint location = m_shader.getUniformLocation("Perspective");
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
		CHECK_GL_ERRORS;


		location = m_shader.getUniformLocation("lightProjection");
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(lightProjection));
		CHECK_GL_ERRORS; 
		

		if(!need_reRender){
			//-- Set LightSource uniform for the scene:
			{
				location = m_shader.getUniformLocation("light.position");
				glUniform3fv(location, 1, value_ptr(m_light.position));
				location = m_shader.getUniformLocation("light.rgbIntensity");
				glUniform3fv(location, 1, value_ptr(m_light.rgbIntensity));
				CHECK_GL_ERRORS;
			}

			//-- Set background light ambient intensity
			{
				location = m_shader.getUniformLocation("ambientIntensity");
				vec3 ambientIntensity(0.05f);
				glUniform3fv(location, 1, value_ptr(ambientIntensity));
				CHECK_GL_ERRORS;
			}
		}

		
	}
	m_shader.disable();
}

void A5::uploadCommonSceneUniformsForDepthShader() {
	m_shader_depthMap.enable();
	{
		//-- Set Perpsective matrix uniform for the scene:
		GLint location = m_shader_depthMap.getUniformLocation("lightProjection");
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(lightProjection));
		CHECK_GL_ERRORS;
	}
	m_shader_depthMap.disable();
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A5::appLogic()
{
	// Place per frame, application logic here ...

	// update call animation
	animationModel.update();

	character_1.update();
	character_2.update();
	updateLifeValue();

	particleModel.update();

	uploadCommonSceneUniforms();

	uploadCommonSceneUniformsForDepthShader();
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A5::guiLogic()
{
	if( !show_gui ) {
		return;
	}

	static bool firstRun(true);
	if (firstRun) {
		ImGui::SetNextWindowPos(ImVec2(50, 50));
		firstRun = false;
	}
	ImGuiStyle * style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImGuiAlign_Center;
	static bool showDebugWindow(true);
	ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	float opacity(0.5f);
	if(gamestage == 0){// display menus for game start
		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiSetCond_Once);
		ImGui::OpenPopup("Welcome to The King of Cute Fighters!");
		if(ImGui::BeginPopupModal("Welcome to The King of Cute Fighters!", 0 , ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize )) {

			ImGui::Spacing ();
			ImGui::SameLine(100.0f);
			ImGui::SetWindowFontScale(2.0f);
			ImGui::Text("Difficulty Setting for Player 1");
			ImGui::Spacing ();
			ImGui::SameLine(120.0f);
			ImGui::RadioButton("Default", &hard_c1, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Medium", &hard_c1, 1);
			ImGui::SameLine();
			ImGui::RadioButton("Hard", &hard_c1, 2);
			ImGui::SliderFloat("Movement Speed", &speed_c1, 0.5f, 1.5f);

			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			ImGui::Spacing ();
			ImGui::SameLine(100.0f);
			ImGui::Text("Difficulty Setting for Player 2");
			ImGui::Spacing ();
			ImGui::SameLine(120.0f);
			ImGui::RadioButton("Default##P2", &hard_c2, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Medium##P2", &hard_c2, 1);
			ImGui::SameLine();
			ImGui::RadioButton("Hard##P2", &hard_c2, 2);
			ImGui::SliderFloat("Movement Speed##P2", &speed_c2, 0.5f, 1.5f);

			ImGui::Dummy(ImVec2(0.0f, 40.0f));
			ImGui::Spacing ();
			ImGui::SameLine((ImGui::GetWindowWidth() - 300) / 2);
			if(ImGui::Button("Start", ImVec2(300, 40))) {
				updateCharacterSetting();
				gamestage = 1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

	}
	if(gamestage == 1){
		if(ImGui::BeginMainMenuBar()){
			ImGui::SetWindowFontScale(2.0f);
			// Application Menu
			if(ImGui::BeginMenu("Pause")){
				gamestage = 3;
				ImGui::EndMenu();
			}

			// Edit Menu
			if(ImGui::BeginMenu("Restart")){
				resetAll();
				ImGui::EndMenu();
			}

			if(ImGui::BeginMenu("Instruction")){
				gamestage = 4;
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Settings", &showDebugWindow, ImVec2(100,100), opacity,
		windowFlags);
		if(ImGui::Checkbox("Display Texture", &display_texture)) {
		}

		if(ImGui::Checkbox("Display Shadow", &display_shadow)) {
                
        }

		ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );

		ImGui::End();

	}
	if(gamestage == 3){
		ImGui::SetNextWindowSize(ImVec2(600, 200), ImGuiSetCond_Once);
		ImGui::OpenPopup("Game Paused");
		if(ImGui::BeginPopupModal("Game Paused", 0 , ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize )) {
			ImGui::Spacing ();
			ImGui::SameLine(100.0f);
			ImGui::SetWindowFontScale(2.0f);
			ImGui::Text("You wanna take a break?");
			ImGui::Dummy(ImVec2(0.0f, 40.0f));
			ImGui::Spacing ();
			ImGui::SameLine((ImGui::GetWindowWidth() - 300) / 2);
			if(ImGui::Button("I'm ready", ImVec2(300, 40))) {
				gamestage = 1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();

		}
	}
	if(gamestage == 4){
		ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiSetCond_Once);

		ImGui::OpenPopup("Instruction");
		if(ImGui::BeginPopupModal("Instruction", 0 , ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize )) {
			

			GLuint my_opengl_texture;
			my_opengl_texture = instructionId;
			//ImGui::Image((void*)(intptr_t)my_opengl_texture, ImGui::GetContentRegionAvail());
			if(ImGui::ImageButton((void*)(intptr_t)my_opengl_texture,  ImVec2(800, 600), ImVec2(0,0),ImVec2(1,1),-1)){
				gamestage = 1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();

		}
	}
}

//----------------------------------------------------------------------------------------
// Update mesh specific shader uniforms:
void A5::updateShaderUniforms(
		const ShaderProgram & shader,
		const GeometryNode & node,
		const glm::mat4 & viewMatrix,
		int pass
) {

	shader.enable();
	{

		if(pass == 2){
			//-- Set ModelView matrix:
			GLint location = shader.getUniformLocation("ModelView");
			mat4 modelView = viewMatrix * node.trans;

			glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
			CHECK_GL_ERRORS;

			location = shader.getUniformLocation("lightView");
			mat4 lightViewN =    lightView * viewMatrix *  node.trans ;
			glUniformMatrix4fv( location, 1, GL_FALSE, value_ptr(lightViewN) );
			CHECK_GL_ERRORS;

			//-- Set NormMatrix:
			location = shader.getUniformLocation("NormalMatrix");
			mat3 normalMatrix = glm::transpose(glm::inverse(mat3(modelView)));
			glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(normalMatrix));
			CHECK_GL_ERRORS;


			if( need_reRender ) {
				int id = node.m_nodeId;
				float r = float(id&0xff) / 255.0f;
				float g = float((id>>8)&0xff) / 255.0f;
				float b = float((id>>16)&0xff) / 255.0f;

				location = m_shader.getUniformLocation("material.kd");
				glUniform3f( location, r, g, b );
				CHECK_GL_ERRORS;
			}
			else{
				if(display_shadow){
					location = shader.getUniformLocation("shadow_enabled");
					glUniform1i( location, 1 );
				}else{
					location = shader.getUniformLocation("shadow_enabled");
					glUniform1i( location, 0 );
				}
				//-- Set Material values:
				if(node.textureId == 0 || display_texture == 0){
					location = shader.getUniformLocation("texture_enabled");
					glUniform1i( location, 0 );
					location = shader.getUniformLocation("material.kd");
					vec3 kd = node.material.kd;
					if(node.isSelected){
						kd = vec3(0.19f, 0.82f, 0.55f);
					}
					if(node.isHit){
						if(node.hitTimeCount > 0){
							kd = vec3(1.0f, 0.0f, 0.0f) + (1 - (float)node.hitTimeCount/60) * (node.material.kd - vec3(1.0f, 0.0f, 0.0f));
						}
					}
					glUniform3fv(location, 1, value_ptr(kd));
					CHECK_GL_ERRORS;
					location = shader.getUniformLocation("material.ks");
					vec3 ks = node.material.ks;
					if(node.isSelected){
						ks = vec3(0.5f);
					}
					glUniform3fv(location, 1, value_ptr(ks));
					CHECK_GL_ERRORS;
					location = shader.getUniformLocation("material.shininess");
					glUniform1f(location, node.material.shininess);
					CHECK_GL_ERRORS;
				}else{
					location = shader.getUniformLocation("texture_enabled");
					glUniform1i( location, 1 );
					glActiveTexture( GL_TEXTURE1 );
					glBindTexture( GL_TEXTURE_2D, node.textureId );
				}
				
			}
		}else{
			GLint location = shader.getUniformLocation("lightView");
			mat4 lightViewN =  lightView * viewMatrix *  node.trans;
			glUniformMatrix4fv( location, 1, GL_FALSE, value_ptr(lightViewN) );
			CHECK_GL_ERRORS;
		}
		

	}
	shader.disable();

}


//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A5::draw() {


	if(z_buffer){
		glEnable( GL_DEPTH_TEST );
	}
	if(backface_culling || frontface_culling){
		glEnable(GL_CULL_FACE);
		if(backface_culling && frontface_culling){
			glCullFace(GL_FRONT_AND_BACK);
		}else if(backface_culling){
			glCullFace(GL_BACK);
		}else if(frontface_culling){
			glCullFace(GL_FRONT);
		}
	}
	renderSceneWithDepthMap(*m_rootNode);
	//renderSceneGraph(*m_rootNode, 2);

	if(z_buffer){
		glDisable( GL_DEPTH_TEST );
	}
	if(backface_culling || frontface_culling){
		glDisable( GL_CULL_FACE );
	}
		
	if(circle){
		//renderArcCircle();
	}

	renderParticles();
	renderBar_c1();
	renderBar_c2();

}

//----------------------------------------------------------------------------------------
void A5::renderSceneGraph(const SceneNode & root, int pass) {


	// Bind the VAO once here, and reuse for all GeometryNode rendering below.
	glBindVertexArray(m_vao_meshData);

	// This is emphatically *not* how you should be drawing the scene graph in
	// your final implementation.  This is a non-hierarchical demonstration
	// in which we assume that there is a list of GeometryNodes living directly
	// underneath the root node, and that we can draw them in a loop.  It's
	// just enough to demonstrate how to get geometry and materials out of
	// a GeometryNode and onto the screen.

	// You'll want to turn this into recursive code that walks over the tree.
	// You can do that by putting a method in SceneNode, overridden in its
	// subclasses, that renders the subtree rooted at every node.  Or you
	// could put a set of mutually recursive functions in this class, which
	// walk down the tree from nodes of different types.

	for (SceneNode * node : root.children) {

		if (node->m_nodeType != NodeType::GeometryNode)
			continue;
		if (node->m_name == "platform_front"){
			continue;
		}
		GeometryNode * geometryNode = static_cast<GeometryNode *>(node);
		

		

		// Get the BatchInfo corresponding to the GeometryNode's unique MeshId.
		BatchInfo batchInfo = m_batchInfoMap[geometryNode->meshId];

		//-- Now render the mesh:
		if(pass == 2){
			updateShaderUniforms(m_shader, *geometryNode, m_view, 2);
			m_shader.enable();
			glDrawArrays(GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices);
			m_shader.disable();
		}else{
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, depthMap_texture );
			updateShaderUniforms(m_shader_depthMap, *geometryNode, m_view, 1);
			m_shader_depthMap.enable();
			glDrawArrays(GL_TRIANGLES, batchInfo.startIndex, batchInfo.numIndices);
			m_shader_depthMap.disable();
		}
		

		if(geometryNode->isHit){
			//cout<<"find hit"<<endl;
			if(geometryNode->particleTriggered == false){
				particleModel.addParticle(  geometryNode->trans);
				geometryNode->particleTriggered = true;
			}
			
		}
	}

	glBindVertexArray(0);
	CHECK_GL_ERRORS;

	for(const SceneNode * node : root.children){
		renderSceneGraph(*node, pass);
	}
}

//----------------------------------------------------------------------------------------
// Draw the trackball circle.
void A5::renderArcCircle() {
	glBindVertexArray(m_vao_arcCircle);

	m_shader_arcCircle.enable();
		/* GLint m_location = m_shader_arcCircle.getUniformLocation( "M" );
		float aspect = float(m_framebufferWidth)/float(m_framebufferHeight);
 		glm::mat4 M;
		if( aspect > 1.0 ) {
			M = glm::scale( glm::mat4(), glm::vec3( 0.5/aspect, 0.5, 1.0 ) );
			//M = glm::translate(M,m_light.position);
			//cout<<M<<endl;
		} else {
			M = glm::scale( glm::mat4(), glm::vec3( 0.5, 0.5*aspect, 1.0 ) );
			//M = glm::translate(M,m_light.position);
			//cout<<M<<endl;
		} 

		glUniformMatrix4fv(m_location, 1, GL_FALSE, value_ptr(M)); */
		glDrawArrays( GL_LINE_LOOP, 0, 5 );
		CHECK_GL_ERRORS;
	m_shader_arcCircle.disable();

	glBindVertexArray(0);
	CHECK_GL_ERRORS;
}


//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A5::cleanup()
{

}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A5::cursorEnterWindowEvent (
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
bool A5::mouseMoveEvent (
		double xPos,
		double yPos
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	if (!ImGui::IsMouseHoveringAnyWindow()) {

		if(mouseReseted){
			mouseReseted = false;
			mouse_prev_x = xPos;
			mouse_prev_y = yPos;
		}
		if(mouse_left_pressed||mouse_mid_pressed||mouse_right_pressed){
			mouseMoveEventHandler(xPos, yPos);
			eventHandled = true;
		}
		mouse_prev_x = xPos;
		mouse_prev_y = yPos;
	}

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A5::mouseButtonInputEvent (
		int button,
		int actions,
		int mods
) {
	bool eventHandled(false);

	// Fill in with event handling code...
	if (!ImGui::IsMouseHoveringAnyWindow()) {
		
		if (button == GLFW_MOUSE_BUTTON_LEFT){
			if (actions == GLFW_PRESS) {
				if(i_mode == 1){ // when joint mode enbaled
					double xpos, ypos;
					
					glfwGetCursorPos( m_window, &xpos, &ypos );

					need_reRender = true;

					uploadCommonSceneUniforms();
					glClearColor(1.0, 1.0, 1.0, 1.0 );
					glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
					glClearColor(0.45, 0.45, 0.45, 1.0);

					draw();

					// I don't know if these are really necessary anymore.
					// glFlush();
					// glFinish();

					CHECK_GL_ERRORS;

					// Ugly -- FB coordinates might be different than Window coordinates
					// (e.g., on a retina display).  Must compensate.
					xpos *= double(m_framebufferWidth) / double(m_windowWidth);
					// WTF, don't know why I have to measure y relative to the bottom of
					// the window in this case.
					ypos = m_windowHeight - ypos;
					ypos *= double(m_framebufferHeight) / double(m_windowHeight);

					GLubyte buffer[ 4 ] = { 0, 0, 0, 0 };
					// A bit ugly -- don't want to swap the just-drawn false colours
					// to the screen, so read from the back buffer.
					glReadBuffer( GL_BACK );
					// Actually read the pixel at the mouse location.
					glReadPixels( int(xpos), int(ypos), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
					CHECK_GL_ERRORS;

					// Reassemble the object ID.
					unsigned int targetId = buffer[0] + (buffer[1] << 8) + (buffer[2] << 16);
					selectNodeById(*m_rootNode, targetId);

					need_reRender = false;

					CHECK_GL_ERRORS;
					


				}
				if(!mouse_left_pressed && !mouse_mid_pressed && !mouse_right_pressed){
					resetMouseLocation();
				}
				
				mouse_left_pressed = true;
				
			}
	
			if (actions == GLFW_RELEASE) {
				mouse_left_pressed = false;
			}
		}

		if (button == GLFW_MOUSE_BUTTON_MIDDLE){
			if (actions == GLFW_PRESS) {
				if(!mouse_left_pressed && !mouse_mid_pressed && !mouse_right_pressed){
					resetMouseLocation();
				}
				mouse_mid_pressed = true;
				
			}
	
			if (actions == GLFW_RELEASE) {
				if(i_mode == 1){ // for joint mode
					std::vector<GLfloat> cur_joint_angle;
					for(auto const& id: jointIndexVector) {
						SceneNode * node = findNodeById(*m_rootNode, id);
						JointNode * jointNode = static_cast<JointNode*>(node);
						cur_joint_angle.push_back(jointNode->m_joint_x.init);
					}
					cur_joint_angle.push_back(head_rotation);
					joint_rotation_undo.push(cur_joint_angle);

				}
				mouse_mid_pressed = false;
			}
		}

		if (button == GLFW_MOUSE_BUTTON_RIGHT){
			if (actions == GLFW_PRESS) {
				if(!mouse_left_pressed && !mouse_mid_pressed && !mouse_right_pressed){
					resetMouseLocation();
				}
				
				mouse_right_pressed = true;
				
			}
	
			if (actions == GLFW_RELEASE) {
				if(i_mode == 1){ // for joint mode
					std::vector<GLfloat> cur_joint_angle;
					for(auto const& id: jointIndexVector) {
						SceneNode * node = findNodeById(*m_rootNode, id);
						JointNode * jointNode = static_cast<JointNode*>(node);
						cur_joint_angle.push_back(jointNode->m_joint_x.init);
					}
					cur_joint_angle.push_back(head_rotation);
					joint_rotation_undo.push(cur_joint_angle);

				}
				mouse_right_pressed = false;
			}
		}
		

	}

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A5::mouseScrollEvent (
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
bool A5::windowResizeEvent (
		int width,
		int height
) {
	bool eventHandled(false);
	lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.0f, 40.0f);
	lightView = glm::lookAt(m_light.position, vec3(0.0f, 0.0f, 0.0f),
      vec3(0.0f, 1.0f, 0.0f));
	initPerspectiveMatrix();
	initDepthMap();
	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A5::keyInputEvent (
		int key,
		int action,
		int mods
) {
	bool eventHandled(false);
	if(gamestage == 1){
			if( action == GLFW_PRESS ) {
			// Respond to some key events.
			// game pause
			if(key == GLFW_KEY_P){
				gamestage = 3;
			}

			if(key == GLFW_KEY_R){
				resetAll();
			}

			// character control

			if(key == GLFW_KEY_V){
				character_1.hitwithLeftHand();
			}
			if(key == GLFW_KEY_B){
				character_1.hitwithLeftLeg();
			}
			if(key == GLFW_KEY_N){
				character_1.defend();
			}
			if(key == GLFW_KEY_PAGE_UP){
				character_2.hitwithLeftHand();
			}
			if(key == GLFW_KEY_PAGE_DOWN){
				character_2.hitwithLeftLeg();
			}
			if(key == GLFW_KEY_RIGHT){
				eventHandled = true;
				character_2.move(1, 0);
			}
			if(key == GLFW_KEY_D){
				eventHandled = true;
				character_1.move(1, 0);
			}

			if(key == GLFW_KEY_LEFT){
				eventHandled = true;
				character_2.move(0, 0);
			}

			if(key == GLFW_KEY_A){
				eventHandled = true;
				character_1.move(0, 0);
			}

			if(key == GLFW_KEY_UP){
				eventHandled = true;
				character_2.move(2, 0);
			}

			if (key == GLFW_KEY_W){
				eventHandled = true;
				character_1.move(2, 0);
			} 

			if(key == GLFW_KEY_DOWN){
				eventHandled = true;
				character_2.move(3, 0);
			}
			if(key == GLFW_KEY_S){
				eventHandled = true;
				character_1.move(3, 0);
			}

			if(key == GLFW_KEY_SPACE){
				eventHandled = true;
				character_1.move(4, 0);
			}

			if (key == GLFW_KEY_0){

				eventHandled = true;
				character_2.hitwithLeftHand();
			} 
			if (key == GLFW_KEY_MINUS){

				eventHandled = true;
				character_2.hitwithLeftLeg();
			} 
			if (key == GLFW_KEY_EQUAL){

				eventHandled = true;

				character_2.defend();
			}
			if(key == GLFW_KEY_9){
				eventHandled = true;
				character_2.move(4, 0);
			}
			
			
			
		}else if(action == GLFW_RELEASE){
			if(key == GLFW_KEY_RIGHT){
				character_2.move(1, 1);
			}

			if(key == GLFW_KEY_LEFT){
				character_2.move(0, 1);
			}

			if(key == GLFW_KEY_UP){
				character_2.move(2, 1);
			}

			if(key == GLFW_KEY_DOWN){
				character_2.move(3 ,1);
			}

			if(key == GLFW_KEY_D){
				character_1.move(1, 1);
			}

			if(key == GLFW_KEY_A){
				character_1.move(0, 1);
			}

			if(key == GLFW_KEY_W){
				character_1.move(2, 1);
			}

			if(key == GLFW_KEY_S){
				character_1.move(3 ,1);
			}
		}
	}
	
	// Fill in with event handling code...
	eventHandled = true;
	return eventHandled;
}

// reset helper functions
void A5::resetAll(){
	resetOrietation();
	resetPosition();
	//resetJoints();
	resetVariables();
	resetMouseLocation();
	character_1.resetCharacter();
	character_2.resetCharacter();
}

void A5::resetVariables(){
	show_gui = true;
	i_mode = 0; 
	z_buffer = true; 
	circle = true;
	backface_culling = false;
	frontface_culling = false;
	selection = false;
	need_reRender = false;
	undo_succeed = true;
	redo_succeed = true;
	mouseReseted = false;
	mouse_left_pressed = false;
	mouse_mid_pressed = false;
	mouse_right_pressed = false;
	lose = 0;
	loseSoundPlayed = 0;
	gamestage = 0;
	hard_c1 = 0; 
	hard_c2 = 0; 
	speed_c1 = 1.0f; 
	speed_c2 = 1.0f; 
	display_texture = true;
	display_shadow = true;
}

void A5::resetMouseLocation(){
	mouse_prev_x = 0.0f;
	mouse_prev_y = 0.0f;
	mouseReseted = true;
}


// mouse movement handler
void A5::mouseMoveEventHandler(double xPos, double yPos){
	double offsetX = xPos - mouse_prev_x;
	double offsetY = yPos - mouse_prev_y;
	switch (i_mode)
	{
	case 0: // rotate position/poientation
		if(mouse_left_pressed){
			rotateP_OHandler(offsetX, offsetY, 0);
		}
		if(mouse_mid_pressed){
			rotateP_OHandler(offsetX, offsetY, 1);
		}
		if(mouse_right_pressed){
			rotateP_OHandler(xPos, yPos, 2);
		}
		break;

	case 1: // rotate joint
		if(mouse_left_pressed){
			
		}
		if(mouse_mid_pressed){
			rotateJointHandler(offsetX, offsetY, 1);
		}
		if(mouse_right_pressed){
			rotateJointHandler(offsetX, offsetY, 2);
		}
		break;

	}
}

// position/orientation move handler
void A5::rotateP_OHandler(double offsetX, double offsetY, int axis){
	switch (axis){
		case 0: //left button move x/y
			m_rootNode->translate(vec3(offsetX/movementBase, -offsetY/movementBase, 0.0f));
			break;
		case 1:
			m_rootNode->translate(vec3(0.0f, 0.0f, offsetY/movementBase));
			break;
		case 2:
			trackballHandler(offsetX, offsetY);
			break;
			
	}
}

// joint move handler
void A5::rotateJointHandler(double offsetX, double offsetY, int type){
	GLfloat angleY = offsetY/angleBase;
	GLfloat angleX = offsetX/angleBase;
	switch (type){
		case 1:
			rotateJointHelper(angleY, *m_rootNode, type);
			break;
		case 2:
			rotateJointHelper(angleX, *m_rootNode, type);
			break;

	}
	

}

void A5::rotateJointHelper(GLfloat angle, SceneNode & root, int type){
	//cout<<"will ortate " << root.m_name << " for : "<<angle<<endl;
	for (SceneNode * node : root.children) {
		if(node->isSelected && node->m_name == "head" && type == 2){
			GLfloat newAngle = head_rotation + angle;
			if((newAngle < head_rotation_max) && (newAngle > head_rotation_min)){
				head_rotation = newAngle;
				glm::mat4 y_rotateMatrix = glm::rotate(mat4(), angle, vec3(0.0f, 1.0f, 0.0f));
				recursiveRotate(node->trans, *node, y_rotateMatrix);
				return;
			}
		}

		else if(node->isSelected && node->m_nodeType == NodeType::JointNode && type == 1 && node->m_name != "head" ){

			JointNode * jointNode = static_cast<JointNode*>(node);

			GLfloat newAngle = jointNode->m_joint_x.init + angle;

			if((newAngle < jointNode->m_joint_x.max) && (newAngle > jointNode->m_joint_x.min)){
				jointNode->m_joint_x.init = newAngle;
				glm::mat4 x_rotateMatrix = glm::rotate(mat4(), angle, vec3(1.0f, 0.0f, 0.0f));
				recursiveRotate(node->trans, *node->children.front(), x_rotateMatrix);
			}
		}
	}
	for( SceneNode * nextnode : root.children){
		rotateJointHelper(angle, *nextnode, type);
	}
	
}

void A5::selectNodeById(SceneNode &node, unsigned int id){
	if(node.m_nodeId == id){
		
		if(node.parent->m_nodeType == NodeType::JointNode){
			node.isSelected = !node.isSelected;
			node.parent->isSelected = !node.parent->isSelected;
		}
		return;
	}else{
		for(SceneNode * nextNode : node.children){
			selectNodeById(*nextNode, id);
		}
	}
}

void A5::recursiveRotate(glm::mat4 revserseTargetMatrix, SceneNode& root, glm::mat4 rotatematrix) {
	glm::mat4 revserseMatrix = glm::inverse(revserseTargetMatrix);
	root.trans = revserseTargetMatrix*rotatematrix*revserseMatrix*root.trans;
	for(SceneNode* node: root.children) {
		recursiveRotate(revserseTargetMatrix, *node, rotatematrix);
	}
}

void A5::resetUndoRedo(){
	while(joint_rotation_redo.size() > 0){
		joint_rotation_redo.pop();
	}
	while(joint_rotation_undo.size() > 0){
		joint_rotation_undo.pop();
	}
	joint_rotation_undo.push(ori_joint_angle);
}

SceneNode * A5::findNodeById(SceneNode& rootNode, unsigned int id){
	if(rootNode.m_nodeId == id){
		return &rootNode;
	}
	for(SceneNode * nextNode : rootNode.children){
		SceneNode * res = findNodeById(*nextNode, id);
		if(res!= NULL){
			return res;
		}
	}
	return NULL;
}

void A5::undo(){
	// check if any change has been made
	if(joint_rotation_undo.size() == 1){
		undo_succeed = false;
		return;
	}
	std::vector<GLfloat> lastAngleVector = joint_rotation_undo.top();
	
	if(joint_rotation_undo.size() > 1){
		joint_rotation_undo.pop();

		while(lastAngleVector == joint_rotation_undo.top() && joint_rotation_undo.size() > 1){
			joint_rotation_undo.pop();
		}
		joint_rotation_redo.push(lastAngleVector);
	}else{
		undo_succeed = false;
		return;
	}
	for(auto const& angle: joint_rotation_undo.top()){
			//cout<<angle<<endl;
	}

	for(int i = 0; i < jointIndexVector.size(); i++) {
		SceneNode * node = findNodeById(*m_rootNode, jointIndexVector[i]);
		JointNode * jointNode = static_cast<JointNode*>(node);
		std::vector<GLfloat> targetAngleVector = joint_rotation_undo.top();

		GLfloat reverseAngle = -(jointNode->m_joint_x.init - targetAngleVector[i]);

		//reverse
		jointNode->m_joint_x.init = targetAngleVector[i];
		glm::mat4 x_rotateMatrix = glm::rotate(mat4(), reverseAngle, vec3(1.0f, 0.0f, 0.0f));
		recursiveRotate(node->trans, *node->children.front(), x_rotateMatrix);
	}

	SceneNode * headnode = findNodeById(*m_rootNode, head_id);
	std::vector<GLfloat> targetAngleVector = joint_rotation_undo.top();
	GLfloat prev_head_rotation = targetAngleVector[jointIndexVector.size()];
	GLfloat reverseAngle = -(head_rotation - prev_head_rotation);

	head_rotation = prev_head_rotation;
	glm::mat4 y_rotateMatrix = glm::rotate(mat4(), reverseAngle, vec3(0.0f, 1.0f, 0.0f));
	recursiveRotate(headnode->trans, *headnode, y_rotateMatrix);

}

void A5::redo(){
	// check if any change has been made
	if(joint_rotation_redo.size() == 0){
		redo_succeed = false;
		return;
	}

	std::vector<GLfloat> lastAngleVector = joint_rotation_redo.top();
	if(joint_rotation_redo.size() > 0){
		joint_rotation_redo.pop();
		joint_rotation_undo.push(lastAngleVector);
	}
	for(auto const& angle: lastAngleVector){
			cout<<angle<<endl;
	}
	for(int i = 0; i < jointIndexVector.size(); i++) {
		SceneNode * node = findNodeById(*m_rootNode, jointIndexVector[i]);
		JointNode * jointNode = static_cast<JointNode*>(node);
		std::vector<GLfloat> targetAngleVector = lastAngleVector;
		GLfloat reverseAngle = -(jointNode->m_joint_x.init - targetAngleVector[i]);

		//reverse
		jointNode->m_joint_x.init = targetAngleVector[i];
		glm::mat4 x_rotateMatrix = glm::rotate(mat4(), reverseAngle, vec3(1.0f, 0.0f, 0.0f));
		recursiveRotate(node->trans, *node->children.front(), x_rotateMatrix);
	}

	SceneNode * headnode = findNodeById(*m_rootNode, head_id);
	std::vector<GLfloat> targetAngleVector = lastAngleVector;
	GLfloat prev_head_rotation = targetAngleVector[jointIndexVector.size()];
	GLfloat reverseAngle = -(head_rotation - prev_head_rotation);

	head_rotation = prev_head_rotation;
	glm::mat4 y_rotateMatrix = glm::rotate(mat4(), reverseAngle, vec3(0.0f, 1.0f, 0.0f));
	recursiveRotate(headnode->trans, *headnode, y_rotateMatrix);
}

void A5::trackballHandler(double xPos, double yPos){
	float fDiameter = (m_framebufferWidth < m_framebufferHeight) ? m_framebufferWidth * 0.5 : m_framebufferHeight * 0.5;
	float iCenterX = m_framebufferWidth / 2;
	float iCenterY = m_framebufferHeight / 2;
	float fOldModX = mouse_prev_x - iCenterX;
	float fOldModY = mouse_prev_y - iCenterY;
	float fNewModX = xPos - iCenterX;
	float fNewModY = yPos - iCenterY;
	float fRotVecX, fRotVecY, fRotVecZ;
	vCalcRotVec(fNewModX, fNewModY,
					fOldModX, fOldModY,
					fDiameter,
					&fRotVecX, &fRotVecY, &fRotVecZ);
	/* Negate Y component since Y axis increases downwards
		* in screen space and upwards in OpenGL.
		*/
	
	
	glm::mat4 rotationMatrix = vAxisRotMatrix(fRotVecX, -fRotVecY, fRotVecZ, rotationMatrix);
	rotationMatrix = glm::scale(glm::transpose(rotationMatrix),glm::vec3(1.0f,1.0f,1.0f));
	//cout<<"rotation is "<<rotationMatrix<<endl;
	trackBallRotationMatrix = m_rootNode->trans;
	glm::mat4 y_rotateMatrix = glm::rotate(mat4(), 1.5f, vec3(0.0f, 1.0f, 0.0f));
	character_1.trackBallRotationMatrix = trackBallRotationMatrix;
	character_2.trackBallRotationMatrix = trackBallRotationMatrix;
	recursiveRotate(m_rootNode->trans, *m_rootNode, rotationMatrix);
}

void A5::resetHandler(int type){
	switch(type){
		case 0: // reset position
			resetPosition();
			break;
		case 1:
			resetOrietation();
			break;
		case 2:
			resetJoints();
			break;
		case 3:
			resetAll();
			break;
	}
}


void A5::resetPosition(){
	glm::mat4 resetPMatrix = glm::translate(mat4(), vec3(root_ori - m_rootNode->trans*vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	recursiveRotate(glm::mat4(), *m_rootNode, resetPMatrix);
}

void A5::resetOrietation(){
	glm::mat4 resetPMatrix = glm::translate(mat4(), vec3(root_ori - m_rootNode->trans*vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	recursiveRotate(glm::mat4(), *m_rootNode, resetPMatrix);

	glm::mat4 resetOMatrix = glm::inverse(m_rootNode->trans*glm::translate(mat4(), -vec3(root_ori)));
	recursiveRotate(glm::mat4(), *m_rootNode, resetOMatrix);

	glm::mat4 revsersePMatrix = glm::inverse(resetPMatrix);
	recursiveRotate(glm::mat4(), *m_rootNode, revsersePMatrix);
}

void A5::resetJoints(){
	while(joint_rotation_undo.size() > 1){
		undo();
	}
	resetUndoRedo();
	unselectJoints();
}

void A5::unselectJoints(){
	for(int i = 0; i < jointIndexVector.size(); i++) {
		SceneNode * node = findNodeById(*m_rootNode, jointIndexVector[i]);
		JointNode * jointNode = static_cast<JointNode*>(node);
		if(jointNode->isSelected){
			jointNode->isSelected = !jointNode->isSelected;
			jointNode->children.front()->isSelected = !jointNode->children.front()->isSelected;
		}
	}
}



// functions for A5
void A5::initAnimationModel(){
	// first load all joint node pointer into animation model
	for(auto const& id: jointIndexVector_c1) {
		SceneNode * node = findNodeById(*m_rootNode, id);
		animationModel.JointPointers_v_c1.push_back(node);
		animationModel.durationCont_v_ani_c1.push_back(0);
		animationModel.durationCont_v_move_c1.push_back(0);
		string s = "dummy";
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		KeyFrame kf = KeyFrame(s, s, 0, 1, 1, rotation, glm::vec3(0.0f, 0.0f,0.0f));
		vector<KeyFrame> temp;
		temp.push_back(kf);
		animationModel.keyFrame_v_ani_c1.push_back(temp);
		animationModel.keyFrame_v_move_c1.push_back(temp);
		JointNode * jointNode = static_cast<JointNode*>(node);
		animationModel.ori_joint_angle_c1.push_back(glm::vec3(jointNode->m_joint_x.init,jointNode->m_joint_y.init,jointNode->m_joint_z.init));
		if(node->m_name == "leftAnkle"){
			cout<<"ori trans :"<<node->trans<<endl;
		}
		animationModel.ori_joint_trans_c1.push_back(node->trans);
	}
	

	for(auto const& id: jointIndexVector_c2) {
		SceneNode * node = findNodeById(*m_rootNode, id);
		animationModel.JointPointers_v_c2.push_back(node);
		animationModel.durationCont_v_ani_c2.push_back(0);
		animationModel.durationCont_v_move_c2.push_back(0);
		string s = "dummy";
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		KeyFrame kf = KeyFrame(s, s, 0, 1, 1, rotation, glm::vec3(0.0f, 0.0f,0.0f));
		vector<KeyFrame> temp;
		temp.push_back(kf);
		animationModel.keyFrame_v_ani_c2.push_back(temp);
		animationModel.keyFrame_v_move_c2.push_back(temp);
		JointNode * jointNode = static_cast<JointNode*>(node);
		animationModel.ori_joint_angle_c2.push_back(glm::vec3(jointNode->m_joint_x.init,jointNode->m_joint_y.init,jointNode->m_joint_z.init));
		animationModel.ori_joint_trans_c2.push_back(node->trans);
	}
}



void A5::renderParticles(){
	glBindVertexArray(m_vao_particle);
	m_shader_particle.enable();
	{
	 for(int i = 0 ; i < particleModel.particle_v.size(); i++){
		 	
        	particle& particle = particleModel.particle_v[i];
			
			//-- Set ModelView matrix:
			GLint location = m_shader_particle.getUniformLocation("ModelView");
			mat4 modelView = m_view * particle.trans;

			glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
			CHECK_GL_ERRORS;



			location = m_shader_particle.getUniformLocation("Perspective");
			glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
			CHECK_GL_ERRORS;
			
			location = m_shader_particle.getUniformLocation("color");
			//cout<<particleModel.particle_color<<endl;
			glUniform4fv(location, 1, value_ptr(particleModel.particle_color));
			CHECK_GL_ERRORS;
			//cout<<"will call draw"<<endl;
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			//cout<<"will call draw done"<<endl;


		}
	}
	//cout<<"bind done"<<endl;
	glBindVertexArray(0);
	CHECK_GL_ERRORS;
	//cout<<"exit 1 "<<endl;
	m_shader_particle.disable();
	CHECK_GL_ERRORS;
	//cout<<"exit 2"<<endl;
    
}


void A5::loadTexture(const char* path){
	// follow the process from learnopengl website
	// first create a new texture object
	unsigned int texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture);  
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	texture_count++;
	stbi_image_free(data);
}


void A5::initDepthMap(){
	glGenFramebuffers(1, &m_fbo_depthMap);  
	glGenTextures(1, &depthMap_texture);
	glBindTexture(GL_TEXTURE_2D, depthMap_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
				m_windowWidth, m_windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
 

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_depthMap);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap_texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

void A5::renderSceneWithDepthMap(const SceneNode &node){
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_depthMap);
    glClear(GL_DEPTH_BUFFER_BIT);
	renderSceneGraph(node, 1);
	glBindVertexArray(0);
  	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	renderSceneGraph(node, 2);
	glBindVertexArray(0);
}

void A5::initTexture(){
	GLuint shadowMap = m_shader.getUniformLocation("shadowMap");
	m_shader.enable();
	glUniform1i(shadowMap, 0);
	m_shader.disable();

	GLuint Texture = m_shader.getUniformLocation("Texture");
	m_shader.enable();
	glUniform1i(Texture, 1);
	m_shader.disable();
}


// render life value bar for c1
void A5::renderBar_c1(){
	glBindVertexArray(m_vao_c1);
	m_shader_bar_c1.enable();
	{

		
		//-- Set ModelView matrix:
 		GLint location = m_shader_bar_c1.getUniformLocation("translation");
		mat4 translation = glm::scale( glm::mat4(), glm::vec3( scale_x_c1, scale_y_c1, scale_z_c1 ));

		translation = glm::translate(translation,  glm::vec3( shift_x_c1, shift_y_c1, shift_z_c1 ));
		//mat4 translation = mat4();
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(translation));
		CHECK_GL_ERRORS; 

		
		location = m_shader_bar_c1.getUniformLocation("color");
		//cout<<particleModel.particle_color<<endl;
		glUniform4fv(location, 1, value_ptr( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		CHECK_GL_ERRORS;
		//cout<<"will call draw"<<endl;
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		CHECK_GL_ERRORS;
		//cout<<"draw done"<<endl;
		//cout<<"will call draw done"<<endl;



	}
	glBindVertexArray(0);
	CHECK_GL_ERRORS;
	//cout<<"exit 1 "<<endl;
	m_shader_bar_c1.disable();
	glBindVertexArray(m_vao_c1);
	m_shader_bar_c1.enable();
	{

		
		//-- Set ModelView matrix:
 		GLint location = m_shader_bar_c1.getUniformLocation("translation");
		mat4 translation = glm::scale( glm::mat4(), glm::vec3( scale_x_c1*life_c1, scale_y_c1, scale_z_c1 ));

		translation = glm::translate(translation,  glm::vec3( shift_x_c1/life_c1, shift_y_c1, shift_z_c1 ));

		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(translation));
		CHECK_GL_ERRORS; 

		
		location = m_shader_bar_c1.getUniformLocation("color");
		//cout<<particleModel.particle_color<<endl;
		glUniform4fv(location, 1, value_ptr( glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
		CHECK_GL_ERRORS;
		//cout<<"will call draw"<<endl;
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		
		CHECK_GL_ERRORS;
		//cout<<"draw done"<<endl;
		//cout<<"will call draw done"<<endl;



	}
	//cout<<"bind done"<<endl;
	glBindVertexArray(0);
	CHECK_GL_ERRORS;
	//cout<<"exit 1 "<<endl;
	m_shader_bar_c1.disable();
	CHECK_GL_ERRORS;
}

// render life value bar for c2
void A5::renderBar_c2(){
	glBindVertexArray(m_vao_c2);
	m_shader_bar_c2.enable();
	{

		
		//-- Set ModelView matrix:
 		GLint location = m_shader_bar_c2.getUniformLocation("translation");
		mat4 translation = glm::scale( glm::mat4(), glm::vec3( scale_x_c2, scale_y_c2, scale_z_c2 ));

		translation = glm::translate(translation,  glm::vec3( shift_x_c2, shift_y_c2, shift_z_c2 ));
		//mat4 translation = mat4();
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(translation));
		CHECK_GL_ERRORS; 

		
		location = m_shader_bar_c2.getUniformLocation("color");
		//cout<<particleModel.particle_color<<endl;
		glUniform4fv(location, 1, value_ptr( glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
		CHECK_GL_ERRORS;
		//cout<<"will call draw"<<endl;
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		
		
		CHECK_GL_ERRORS;
		//cout<<"draw done"<<endl;
		//cout<<"will call draw done"<<endl;



	}
	glBindVertexArray(0);
	CHECK_GL_ERRORS;
	//cout<<"exit 1 "<<endl;
	m_shader_bar_c2.disable();
	glBindVertexArray(m_vao_c2);
	m_shader_bar_c2.enable();
	{

		
		//-- Set ModelView matrix:
 		GLint location = m_shader_bar_c2.getUniformLocation("translation");
		mat4 translation = glm::scale( glm::mat4(), glm::vec3( scale_x_c2*life_c2, scale_y_c2, scale_z_c2 ));

		translation = glm::translate(translation,  glm::vec3( shift_x_c2/life_c2, shift_y_c2, shift_z_c2 ));

		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(translation));
		CHECK_GL_ERRORS; 

		
		location = m_shader_bar_c2.getUniformLocation("color");
		//cout<<particleModel.particle_color<<endl;
		glUniform4fv(location, 1, value_ptr( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		CHECK_GL_ERRORS;
		//cout<<"will call draw"<<endl;
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
		
		
		CHECK_GL_ERRORS;
		//cout<<"draw done"<<endl;
		//cout<<"will call draw done"<<endl;



	}
	//cout<<"bind done"<<endl;
	glBindVertexArray(0);
	CHECK_GL_ERRORS;
	//cout<<"exit 1 "<<endl;
	m_shader_bar_c2.disable();
	CHECK_GL_ERRORS;
}


void A5::updateLifeValue(){
	int c1_life = character_1.lifeValue;


	if(c1_life == 0 &&  (lose == 0 || lose == 1)){
		gamestage = 2;
		lose = 1;
		ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_Once);
		ImGui::OpenPopup("Player1 lost!");
		if(ImGui::BeginPopupModal("Player1 lost!", 0 , ImGuiWindowFlags_NoResize)) {
			ImGui::Spacing ();
			ImGui::SameLine(120.0f);
			ImGui::SetWindowFontScale(2.0f);
			ImGui::Text("Player1 lost!");
			ImGui::Spacing ();
			ImGui::SameLine(50.0f);
			if(ImGui::Button("Try Again", ImVec2(300, 40))) {
				resetAll();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
	int c2_life = character_2.lifeValue;
	if(c2_life == 0 &&  (lose == 0 || lose == 2)){
		gamestage = 2;
		lose = 2;
		ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_Once);
		ImGui::OpenPopup("Player2 lost!");
		if(ImGui::BeginPopupModal("Player2 lost!", 0 , ImGuiWindowFlags_NoResize)) {
			ImGui::Spacing ();
			ImGui::SameLine(120.0f);
			ImGui::SetWindowFontScale(2.0f);
			ImGui::Text("Player2 lost!");
			ImGui::Spacing ();
			ImGui::SameLine(50.0f);
			if(ImGui::Button("Try Again", ImVec2(300, 40))) {
				resetAll();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	if( lose != 0 && loseSoundPlayed == 0){
		loseSoundPlayed =1;
		loseSound = SoundEngine->play2D("Assets/lose.wav", GL_FALSE);
	}
	//cout<<" c2 life" << c2_life<<endl;
	int c1_time = (100 - c1_life)/10;
	int c2_time = (100 - c2_life)/10;
	float each_time_c1 = pow(18.0f, 1.0f/10.0f);
	float each_time_c2 = pow(1.0f/18.0f, 1.0f/10.0f);
	if( prev_life_c1 != c1_life){
		life_c1 = 1.0f - 0.1f * (100 - c1_life)/10;
		prev_life_c1 = c1_life;
		//cout<<"current c1 value : "<<life_c1<<endl;
	}
	if( prev_life_c2 != c2_life){
		life_c2 = 0.0f + 0.1f* (100 - c2_life)/10;
		prev_life_c2 = c2_life;
		//cout<<"each time is : "<<each_time<<"current c2 value : "<<life_c2<<endl;
	}
	
}





void A5::updateCharacterSetting(){
	character_1.lifeValue -= hard_c1 * 20;
	character_2.lifeValue -= hard_c2 * 20;
	character_1.startSpeed *= speed_c1;
	character_2.startSpeed *= speed_c2;
}


unsigned int A5::loadTexture2(const char* path){
	unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	return texture;
}





























// dropped -- replaced with directly call character move function
void A5::moveHandler(int target, int type){// target 0 for left 1 for right
	switch(type){
		case 0: // move left 
			moveLeft(target);
		break;
		case 1: // move right 
			moveRight(target);
		break;
		case 2: // move up 
			moveForward(target);
		break;
		case 3: // move down 
			moveBack(target);
		break;
			
	}
}

void A5::moveLeft(int target){
	// need to check collision
	if(target == 0){
		glm::vec4 temp = glm::vec4(-1.0f, 0.0f, 0.0f,0.0f);
		temp = trackBallRotationMatrix * temp;
		//cout<<"move left"<<temp<<endl;
		Left_rootNode->translate(vec3(temp));
	}else{
		Right_rootNode->translate(vec3(-1.0f, 0.0f, 0.0f));
	}
}
void A5::moveRight(int target){
	if(target == 0){
		glm::vec4 temp = glm::vec4(1.0f, 0.0f, 0.0f,0.0f);
		temp = trackBallRotationMatrix * temp;
		//cout<<"move right"<<temp<<endl;
		Left_rootNode->translate(vec3(temp));
	}else{
		Right_rootNode->translate(vec3(1.0f, 0.0f, 0.0f));
	}
}
void A5::moveForward(int target){
	if(target == 0){
		glm::vec4 temp = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		temp = trackBallRotationMatrix * temp;
		//cout<<"move forward"<<temp<<endl;
		Left_rootNode->translate(vec3(temp));
	}else{
		Right_rootNode->translate(vec3(0.0f, 0.0f, 1.0f));
	}
}
void A5::moveBack(int target){
	if(target == 0){
		glm::vec4 temp = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
		temp = trackBallRotationMatrix * temp;
		//cout<<"move back"<<temp<<endl;
		Left_rootNode->translate(vec3(temp));
	}else{
		Right_rootNode->translate(vec3(0.0f, 0.0f, -1.0f));
	}
}


/* 
// 0 for left arm attack
void A5::AddKeyFrame(int type){
	switch(type){
		case 0: // left arm attack
			keyFrameHandler.addKeyFrameforLeftHit(animationModel);
			break;
		case 1:
			keyFrameHandler.addKeyFrameforRunForward(animationModel);
			break;
	}
} */

// dropped till here

// test use
void A5::printAll(SceneNode & root){
	cout<<root.m_name<<root.trans<<endl;
	if(root.m_nodeType == NodeType::JointNode){
		JointNode * jointNode = static_cast<JointNode*>(&root);
		std::cout<<" trans: x "<<jointNode->m_joint_x.init<<" trans: y "<<jointNode->m_joint_y.init<<" trans: z "<<jointNode->m_joint_z.init<<std::endl;
		
	}
	for (SceneNode * node : root.children) {
			printAll(*node);
	}
};