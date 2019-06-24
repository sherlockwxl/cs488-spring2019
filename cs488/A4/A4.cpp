// Spring 2019

#include <glm/ext.hpp>

#include "A4.hpp"


glm::vec3 rayTrace(Ray &ray, int maxHit, SceneNode *rootNode, const glm::vec3 & ambient,
				const std::list<Light *> & lights){
					
};

void A4_Render(
		// What to render  
		SceneNode * root,

		// Image to write to, set to a given width and height  
		Image & image,

		// Viewing parameters  
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters  
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  // Fill in raytracing code here...  

  std::cout << "Calling A4_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	size_t imageh = image.height();
	size_t imagew = image.width();
	double d = distance(eye, view);
	// wh is the windows height
	float windowh = 2 * d * glm::tan(glm::radians(fovy/2));
	// ww is the windows width
	float windoww = imagew/imageh*windowh; 
	

	// first step do coordinate transfermation

	// Step1. make z  = 0
	glm::mat4 T1 = glm::translate(glm::mat4(), glm::vec3(-imagew/2, -imageh/2, d));

	// Step2. persve aspect ratio
	glm::mat4 T2 = glm::scale(glm::mat4(), glm::vec3(-windoww/imagew, -windowh/imageh, 1));
	
	// Step3. 
	// Step3.1  Calculate w u v
	glm::vec3 w_v = glm::normalize(view - eye);
	glm::vec3 u_v = glm::normalize(glm::cross(up, w_v));
	glm::vec3 v_v = glm::cross(w_v, u_v);

	// Step3.2 build matrix
	glm::mat4 R = glm::mat4{
		glm::vec4(u_v, 0.0f),
		glm::vec4(v_v, 0.0f),
		glm::vec4(w_v, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	};


	// Step 4 translation
	glm::mat4 T4 = glm::mat4{
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(eye, 1.0f)
	};

	// final view to world matrix
	glm::mat4 t_matrix = T4 * R * T2 * T1;

	int perc = ceil(((double)imageh/10));
	glm::vec4 eye_v4 = glm::vec4(eye, 1.0f);

	for (uint y = 0; y < imageh; ++y) {
		if(y% perc == 0){
			std::cout<< "Current render percentage : " << y/perc * 10<<std::endl;
		}
		for (uint x = 0; x < imagew; ++x) {
			
			glm::vec4 target = t_matrix * glm::vec4(x, y, 0, 1);
			Ray curRay = Ray(eye_v4, target);

			// Red: 
			image(x, y, 0) = (double)1.0;
			// Green: 
			image(x, y, 1) = (double)1.0;
			// Blue: 
			image(x, y, 2) = (double)1.0;
		}
	}

};