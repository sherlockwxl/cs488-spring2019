// Spring 2019

#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include <glm/glm.hpp>

#include <vector>

// Set a global maximum number of vertices in order to pre-allocate VBO data
// in one shot, rather than reallocating each frame.
const GLsizei kMaxVertices = 1000;


// Convenience class for storing vertex data in CPU memory.
// Data should be copied over to GPU memory via VBO storage before rendering.
class VertexData {
public:
	VertexData();

	std::vector<glm::vec2> positions;
	std::vector<glm::vec3> colours;
	GLuint index;
	GLsizei numVertices;
};


class A2 : public CS488Window {
public:
	A2();
	virtual ~A2();

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

	void createShaderProgram();
	void enableVertexAttribIndices();
	void generateVertexBuffers();
	void mapVboDataToVertexAttributeLocation();
	void uploadVertexDataToVbos();

	void initLineData();

	void setLineColour(const glm::vec3 & colour);

	void drawLine (
			const glm::vec2 & v0,
			const glm::vec2 & v1
	);

	ShaderProgram m_shader;

	GLuint m_vao;            // Vertex Array Object
	GLuint m_vbo_positions;  // Vertex Buffer Object
	GLuint m_vbo_colours;    // Vertex Buffer Object

	VertexData m_vertexData;

	glm::vec3 m_currentLineColour;

	// A2 variables:
	glm::mat4 modelTransfer;
	glm::mat4 viewTransfer;
	// plane info
	GLfloat nearPlane, farPlane, fov;
	// viewport info
	glm::vec2 vp1, vp2;
	// base v
	glm::vec4 base_x = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 base_y = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec4 base_z = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 base_0 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// view info
	glm::vec3 m_view_origin = glm::vec3(0.2f, 0.2f, 10.0f);
	glm::vec3 m_view_x = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 m_view_y = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_view_z = glm::vec3(0.0f, 0.0f, -1.0f);

	// A2 functions:
	
	void pieplineHandler(); // helper functin that process the cube data and draw the cube
	void FrameHandler(glm::vec4 new_base_0, glm::vec4 new_base_x, glm::vec4 new_base_y, glm::vec4 new_base_z); // helper function that process model frame info and draw the axis
	void worldFrameHandler(); // helper function that process world frame info and draw the axis

	bool clipAndTtoViewPoint(std::pair<glm::vec2, glm::vec2 > &displayPair);
	void sortTwoPoints(glm::vec2 &P1, glm::vec2 &P2, int base);
	int easyClipping(glm::vec4 *cube_vec4_VCS, std::pair<int, int> *indexPair, int index);
	void reset();
	void resetFOV();
	void resetVP();

};
