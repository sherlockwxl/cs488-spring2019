// Spring 2019

#pragma once

#include <glm/glm.hpp>

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include "maze.hpp"

class A1 : public CS488Window {
public:
	A1();
	virtual ~A1();

protected:
	virtual void init() override;
	virtual void appLogic() override;
	virtual void guiLogic() override;
	virtual void draw() override;
	virtual void cleanup() override;

	virtual bool cursorEnterWindowEvent(int entered) override;
	virtual bool mouseMoveEvent(double xPos, double yPos) override;
	virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
	virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
	virtual bool windowResizeEvent(int width, int height) override;
	virtual bool keyInputEvent(int key, int action, int mods) override;

private:
	Maze *minfo;
	void initGrid();
	// private functions
	void updateCubes();
	void initCubes();
	void drawCubes(glm::mat4 W);
	void initAvator();
	void drawAvatar(glm::mat4 W);
	void drawFloor();
	void moveAvator(int direction);
	void reset();
	void resetAttributes();
	

	

	// Fields related to the shader and uniforms.
	ShaderProgram m_shader;
	GLint P_uni; // Uniform location for Projection matrix.
	GLint V_uni; // Uniform location for View matrix.
	GLint M_uni; // Uniform location for Model matrix.
	GLint col_uni;   // Uniform location for cube colour.

	// Fields related to grid geometry.
	GLuint m_grid_vao; // Vertex Array Object
	GLuint m_grid_vbo; // Vertex Buffer Object

	// Fields related to cubes geometry.
	GLuint m_cube_vao; // Vertex Array Object
	GLuint m_cube_vbo; // Vertex Buffer Object
	GLuint m_cube_ibo; // Indices Buffer Object

	// Fields related to avatar geometry.
	GLuint m_avator_vao; // Vertex Array Object
	GLuint m_avator_vbo; // Vertex Buffer Object

	// Fields related to floor geometry.
	GLuint m_floor_vao; // Vertex Array Object
	GLuint m_floor_vbo; // Vertex Buffer Object

	// Matrices controlling the camera and projection.
	glm::mat4 proj;
	glm::mat4 view;

	float colour[3];
	int current_col;
	int cube_height;
	float avatar_X;
	float avatar_Y;
	bool shiftheld = false;
	float rotation;
	float scale;
	bool m_mouseButtonActive = false;
	float prev_m_x;
	float prev_movement;
	int persistence;

	glm::vec3 color_cube;
	glm::vec3 color_floor;
	glm::vec3 color_avatar;
};
