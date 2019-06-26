// Spring 2019

#include <glm/ext.hpp>

#include "A4.hpp"
#include "GeometryNode.hpp"
#include "PhongMaterial.hpp"

//debug
#include <glm/gtx/string_cast.hpp>
double exp_test_glo = 0.001;

SceneNode * findNodeById(SceneNode& rootNode, unsigned int id){
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

void transWholeTree(SceneNode *root) {
	for(SceneNode *node: root->children) {
		node->trans = root->trans*node->trans;
		node->invtrans = glm::inverse(node->trans);
		transWholeTree(node);
	}
}


Ray generateReflection(Ray startRay, glm::vec3 newOri, intersection int_neat){
	
	glm::vec4 newOri_v4 = glm::vec4(newOri, 1.0f);

	glm::vec4 newDir = glm::normalize(glm::vec4(startRay.direction - 
			2 * glm::vec4(glm::dot(glm::vec3(startRay.direction), int_neat.norm_v)  * int_neat.norm_v, 0.0f)));
	Ray reflectionRay;
	reflectionRay.start = newOri_v4;
	reflectionRay.direction = newDir;
	return reflectionRay;

}
intersection getNearestIntersection(SceneNode *&resNode, SceneNode *rootNode, Ray &ray, double limit){
	intersection int_res;
	int_res.t = -1;
	glm::vec4 start;
	glm::vec4 direction;
	for(int i = 0 ; i < rootNode->totalSceneNodes(); i++){
		const GeometryNode *geometryNode;
		SceneNode *node = findNodeById(*rootNode, i);
		
		if(node !=NULL){
			if(node->m_nodeType == NodeType::GeometryNode){ // only check intersection with geometrynode
				if(node->linkNextNode != NULL){
					geometryNode = static_cast<const GeometryNode*>(node->linkNextNode);
				}else{
					geometryNode = static_cast<const GeometryNode*>(node);
				}
				
				
				Ray transferd_ray;

				transferd_ray.start = node->invtrans*ray.start;
				transferd_ray.direction = glm::normalize(node->invtrans*(ray.start + ray.direction) - node->invtrans*ray.start);
				
				

				intersection temp_int_res;
				if(node->trans != glm::mat4()){

					temp_int_res = geometryNode->m_primitive->checkIntersection(transferd_ray);
				}else{
					temp_int_res = geometryNode->m_primitive->checkIntersection(ray);
				}
				
				if (temp_int_res.t > exp_test_glo){
					if(node->trans != glm::mat4()){
						temp_int_res.t = glm::distance(glm::vec3(node->trans*(transferd_ray.start + temp_int_res.t * transferd_ray.direction)), glm::vec3(ray.start));
						temp_int_res.norm_v = glm::normalize(glm::transpose(glm::mat3(node->invtrans))*temp_int_res.norm_v);
					}

					if(temp_int_res.t < limit){
						resNode = node;
						limit = temp_int_res.t;
						int_res.t = temp_int_res.t;
						int_res.norm_v = temp_int_res.norm_v;
					} 
				}
			}
		}	
	}

	return int_res;
}
glm::vec3 rayTrace(Ray &ray, int maxHit, SceneNode *rootNode, const glm::vec3 & ambient,
				const std::list<Light *> & lights){
		double exp_test = 1e10; 
		SceneNode *resNode = NULL;
		double curLim = exp_test;
		intersection int_near = getNearestIntersection(resNode, rootNode, ray, curLim);

		// performation invese transformation
		
		
		if(resNode !=NULL && int_near.t != -1){

			glm::vec3 col = glm::vec3(0.0f, 0.0f, 0.0f); 
			GeometryNode * geometryNode;
			// add ambient
			if(resNode->linkNextNode !=NULL){
				geometryNode = static_cast<GeometryNode*>(resNode->linkNextNode);
			}else{
				geometryNode = static_cast<GeometryNode*>(resNode);
			}
			
			PhongMaterial* pMaterial = static_cast<PhongMaterial*>(geometryNode->m_material);
			col += pMaterial->get_m_kd()*ambient;

			// clacultae new ori
			glm::vec3 newOri = glm::vec3(ray.start + int_near.t*(ray.direction));

			for(Light * light : lights){
				Ray curRay;

				// add transformation functions
				curRay.start = glm::vec4(newOri, 1.0f);
				curRay.direction = glm::normalize(glm::vec4(light->position - newOri, 0.0f));

				SceneNode *tempResNode = NULL;
				double tempCurLim = exp_test;
				intersection int_w_light = getNearestIntersection(tempResNode, rootNode, curRay, tempCurLim);
				double diss = glm::abs( glm::distance(newOri, light->position + glm::vec3(int_w_light.t*curRay.direction)));
				if(int_w_light.t == -1 || (int_w_light.t > 0 && diss < 0.01)){// has interection
	
					glm::vec3 N = int_near.norm_v;
					glm::vec3 L = glm::vec3(curRay.direction);
					glm::vec3 V = glm::vec3(ray.direction);
					glm::vec3 h = glm::normalize(L - glm::vec3(ray.direction));
					float n_dot_l = std::max((float)glm::dot(N, L), 0.0f);
					float n_dot_h = std::max((float)glm::dot(N, h), 0.0f);
					glm::vec3 R = glm::normalize(2*glm::dot(L, N)*N - L);
					// Steps based on course notes page 171
					//Step 1. calculate diffuse
					glm::vec3 Diffuse = pMaterial->get_m_kd() * n_dot_l;

					//Step 2. calculate Specular
					float pf = std::pow(n_dot_h, pMaterial->get_m_shine() );

					glm::vec3 Specular =  pMaterial->get_m_ks() * pf;


					//Step 3. calculate attenuation
					double dis = glm::distance(glm::vec3(newOri), light->position);
					double devider = (light->falloff[0] + light->falloff[1] * dis + light->falloff[2] * dis * dis);

					// step 4 update color

					col += light->colour*(Diffuse + Specular);
				}else{

				}

			}
			if(maxHit > 0){
				//TODO
			}
			return col; 
		}else{

			// for background color
			double y = ray.direction.y;
			glm::vec3 color = glm::vec3(y/10*1.0f, y/10*3*1.0f,y/10*7*1.0f);
			return color;
	
		}
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
  transWholeTree(root);
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

	int imageh = image.height();
	int imagew = image.width();
	double d = distance(eye, view);
	// wh is the windows height
	double windowh = 2 * d * glm::tan(glm::radians(fovy/2));
	// ww is the windows width
	double windoww = imagew/imageh*windowh; 
	

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
	int supersamplingAmt = 1;

	for (int y = 0; y < imageh; ++y) {
		if(y% perc == 0){
			std::cout<< "Current render percentage : " << y/perc * 10<<std::endl;
		}
		for (int x = 0; x < imagew; ++x) {
			Ray curRay;
			curRay.start = eye_v4;
			glm::vec3 col = glm::vec3(0.0f, 0.0f, 0.0f);
			for(int x_s = 0; x_s < supersamplingAmt; x_s++){
				for(int y_s = 0; y_s < supersamplingAmt; y_s++){
					glm::vec4 dir = glm::normalize( t_matrix * glm::vec4((float)x + (float)x_s/supersamplingAmt*3.0f, (float)y + (float)y_s/supersamplingAmt*3.0f, 0, 1) - eye_v4);
					curRay.direction = dir;
								
					col += rayTrace(curRay, 6, root, ambient, lights);
					//cout<<x + x_s/supersamplingAmt*3.0f<<"  ";
					//cout<<glm::to_string(rayTrace(curRay, 6, root, ambient, lights))<<endl;
				}
			}

			
			col /= (supersamplingAmt * supersamplingAmt);
			
			// Red: 
			image(x, y, 0) = col.r;
			// Green: 
			image(x, y, 1) = col.g;
			// Blue: 
			image(x, y, 2) = col.b;
		}
	}

};		