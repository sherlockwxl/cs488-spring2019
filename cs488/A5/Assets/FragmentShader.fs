#version 330

uniform bool texture_enabled;
uniform bool picking;
uniform sampler2D Texture;
uniform sampler2D shadowMap;

struct LightSource {
    vec3 position;
    vec3 rgbIntensity;
};

in VsOutFsIn {
	vec3 position_ES; // Eye-space position
	vec3 normal_ES;   // Eye-space normal
	LightSource light;
    vec4 lightSpace;
} fs_in;


out vec4 fragColour;

struct Material {
    vec3 kd;
    vec3 ks;
    float shininess;
};
uniform Material material;

// Ambient light intensity for each RGB component.
uniform vec3 ambientIntensity;


// follow tutrial from https://learnopengl.com/Lighting/Basic-Lighting
vec3 PhongModelWithTextureAndShadow(vec3 fragPosition, vec3 fragNormal, float shadow, vec3 textureColor){
    LightSource light = fs_in.light;
    //ambient
    vec3 ambientIntensityWithTexture = 0.3 * textureColor;

    // diffuse
    // Direction from fragment to light source.
    vec3 norm = normalize(fragNormal);
    vec3 l = normalize(light.position - fragPosition);
    float diff = max(dot(norm, l), 0.0);
    vec3 diffuse = diff * light.rgbIntensity;

    // specular
    float strength = 0.4;
    // Direction from fragment to viewer (origin - fragPosition) -> the opposite
    vec3 v = normalize(-fragPosition.xyz);
    vec3 reflectV = reflect(-l,norm);

    vec3 specular = vec3(0.0);

    vec3 h = normalize(l + v);
    if (diff > 0.0) {
		// Halfway vector.
		vec3 h = normalize(v + l);
        float n_dot_h = max(dot(fragNormal, h), 0.0);

        //specular = material.ks * pow(n_dot_h, material.shininess);
        float spec = pow(max(dot(v, reflectV), 0.0), 32);
        vec3 specular = strength * spec * light.rgbIntensity;
    }

    

    return (ambientIntensityWithTexture + (diffuse + specular) * (1.0 - shadow)) * textureColor;
}


vec3 phongModel(vec3 fragPosition, vec3 fragNormal, float shadow) {
	LightSource light = fs_in.light;

    // Direction from fragment to light source.
    vec3 l = normalize(light.position - fragPosition);

    // Direction from fragment to viewer (origin - fragPosition).
    vec3 v = normalize(-fragPosition.xyz);

    float n_dot_l = max(dot(fragNormal, l), 0.0);

	vec3 diffuse;
	diffuse = material.kd * n_dot_l;

    vec3 specular = vec3(0.0);

    if (n_dot_l > 0.0) {
		// Halfway vector.
		vec3 h = normalize(v + l);
        float n_dot_h = max(dot(fragNormal, h), 0.0);

        specular = material.ks * pow(n_dot_h, material.shininess);
    }

    return ambientIntensity + (1.0 - shadow)*light.rgbIntensity * (diffuse + specular);
}
// follow tutrial from https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping

float shadowCalculation(vec4 fragPosition, vec3 fragNormal){

    vec3 projCoords = fragPosition.xyz;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    vec3  lightDir = normalize(fs_in.light.position - fragPosition.xyz);
    float bias = max(0.05 * (1.0 - dot(fragNormal, lightDir)), 0.005);  
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;  

    return shadow;

}
void main() {
    float shadow = shadowCalculation(fs_in.lightSpace, fs_in.normal_ES);

	if( texture_enabled ) {
		vec4 colour = texture(Texture, vec2(fs_in.position_ES.x/20, fs_in.position_ES.y/20));
        fragColour = vec4(PhongModelWithTextureAndShadow(fs_in.position_ES, fs_in.normal_ES, shadow, colour.rgb), 1.0);
	} else {
		fragColour = vec4(phongModel(fs_in.position_ES, fs_in.normal_ES, shadow), 1.0);
	}
}

