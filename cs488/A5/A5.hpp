// Spring 2019

#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/MeshConsolidator.hpp"

#include "SceneNode.hpp"
#include "GeometryNode.hpp"
#include "AnimationModel.hpp"


#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
struct LightSource {
	glm::vec3 position;
	glm::vec3 rgbIntensity;
};


class A5 : public CS488Window {
public:
	A5(const std::string & luaSceneFile);
	virtual ~A5();

protected:
	virtual void init() override;
	virtual void appLogic() override;
	virtual void guiLogic() override;
	virtual void draw() override;
	virtual void cleanup() override;

	//-- Virtual callback methods
	virtual bool cursorEnterWindowEvent(int entered) override;
	virtual bool mouseMoveEvent(double xPos, double yPos) override;
	virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
	virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
	virtual bool windowResizeEvent(int width, int height) override;
	virtual bool keyInputEvent(int key, int action, int mods) override;

	//-- One time initialization methods:
	void processLuaSceneFile(const std::string & filename);
	void createShaderProgram();
	void enableVertexShaderInputSlots();
	void uploadVertexDataToVbos(const MeshConsolidator & meshConsolidator);
	void mapVboDataToVertexShaderInputLocations();
	void initViewMatrix();
	void initLightSources();

	void initPerspectiveMatrix();
	void uploadCommonSceneUniforms();
	void renderSceneGraph(const SceneNode &node);
	void renderArcCircle();

	glm::mat4 m_perpsective;
	glm::mat4 m_view;

	LightSource m_light;

	//-- GL resources for mesh geometry data:
	GLuint m_vao_meshData;
	GLuint m_vbo_vertexPositions;
	GLuint m_vbo_vertexNormals;
	GLint m_positionAttribLocation;
	GLint m_normalAttribLocation;
	ShaderProgram m_shader;

	//-- GL resources for trackball circle geometry:
	GLuint m_vbo_arcCircle;
	GLuint m_vao_arcCircle;
	GLint m_arc_positionAttribLocation;
	ShaderProgram m_shader_arcCircle;

	// BatchInfoMap is an associative container that maps a unique MeshId to a BatchInfo
	// object. Each BatchInfo object contains an index offset and the number of indices
	// required to render the mesh with identifier MeshId.
	BatchInfoMap m_batchInfoMap;

	std::string m_luaSceneFile;

	std::shared_ptr<SceneNode> m_rootNode;

	// model variable
	int i_mode; // 0 for position 1 for joint 
	bool z_buffer = true; 
	bool circle = true;
	bool backface_culling = false;
	bool frontface_culling = false;
	bool need_reRender = false;
	bool selection = false;
	bool undo_succeed = true;
	bool redo_succeed = true;


	// variables for mouse data
	double mouse_prev_x;
	double mouse_prev_y;
	bool mouseReseted = false;
	bool mouse_left_pressed = false;
	bool mouse_mid_pressed = false;
	bool mouse_right_pressed = false;

	int movementBase = 50; // deivder for mouse movement
	int angleBase = 20; // deivder for mouse movement

	GLfloat head_rotation = 0.0f;
	GLfloat head_rotation_min = -3.14/2;
	GLfloat head_rotation_max = 3.14/2;
	int head_id= 0;

	glm::vec4 root_ori;
	glm::mat4 root_ori_m;

	// variable for ini location and transformtaion
	glm::mat4 ini_translation;

	// variable for redo/undo
	int totalNode;
	std::priority_queue<int, vector<int>, greater<int> > jointIndex;
	std::vector<int> jointIndexVector;
	std::vector<GLfloat> ori_joint_angle;
	std::stack<std::vector<GLfloat>> joint_rotation_undo;
	std::stack<std::vector<GLfloat>> joint_rotation_redo;
	
	

	// trackball hander
	void trackballHandler(double xPos, double yPos);

	// reset helper functions
	void resetAll();
	void resetMouseLocation();
	void resetVariables();
	void resetUndoRedo();
	void resetHandler(int type);
	void resetPosition();
	void resetOrietation();
	void resetJoints();
	void unselectJoints();

	// mouse movement handler
	void mouseMoveEventHandler(double xPos, double yPos);
	void rotateP_OHandler(double offsetX, double offsetY, int axis);
	void rotateJointHandler(double offsetX, double offsetY,  int type);
	

	// update helper function
	void selectNodeById(SceneNode &node, unsigned int id);
	void updateShaderUniforms(const ShaderProgram & shader, const GeometryNode & node, const glm::mat4 & viewMatrix);
	void rotateJointHelper(GLfloat angle, SceneNode & node, int type);
	
	void recursiveRotate(glm::mat4 revserseTargetMatrix, SceneNode& root, glm::mat4 rotatematrix);
	SceneNode * findNodeById(SceneNode& rootNode, unsigned int id);

	// helper function for undo and redo
	void undo();
	void redo();


	// change for project

	AnimationModel animationModel;
	void initAnimationModel();
	void AddKeyFrame(int type);
};

