#version 330

// Model-Space coordinates
in vec3 position;
in vec3 normal;
in vec3 textureUV;

struct LightSource {
    vec3 position;
    vec3 rgbIntensity;
};
uniform LightSource light;

uniform mat4 ModelView;
uniform mat4 Perspective;
uniform mat4 lightProjection;
uniform mat4 lightView;

// Remember, this is transpose(inverse(ModelView)).  Normals should be
// transformed using this matrix instead of the ModelView matrix.
uniform mat3 NormalMatrix;

out VsOutFsIn {
	vec3 position_ES; // Eye-space position
	vec3 normal_ES;   // Eye-space normal
	LightSource light;
	vec4 lightSpace;  // position for light space
	vec3 textureUV;
} vs_out;


void main() {
	vec4 pos4 = vec4(position, 1.0);

	//-- Convert position and normal to Eye-Space:
	vs_out.position_ES = (ModelView * pos4).xyz;
	vs_out.normal_ES = normalize(NormalMatrix * normal);

	vs_out.light = light;

	vs_out.lightSpace = lightProjection * lightView * pos4;

	gl_Position = Perspective * ModelView * vec4(position, 1.0);
	vs_out.textureUV = textureUV;
}
