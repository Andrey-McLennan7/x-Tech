#ifdef GL_ES
	precision highp float;
#endif

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material
{
	sampler2D texture_diffuse;
	sampler2D texture_specular;
};

struct Light
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

float constant = 1.0;
float linear = 0.0092;
float quadratic = 0.032;

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_ViewPos;

void main()
{
	// Ambient
	vec3 ambient = u_Light.ambient * vec3(texture(u_Material.texture_diffuse, TexCoords));

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_Light.direction);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.texture_diffuse, TexCoords));

	// Specular
	vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
	vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.texture_specular, TexCoords));

	// Attenuation
	float Distance = length(u_Light.position - FragPos);
	float attenuation = 1.0 / (constant + linear * Distance + quadratic * pow(Distance, 2));

	diffuse *= attenuation;
	ambient *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;

	gl_FragColor = vec4(result, 1.0);
	//gl_FragColor = texture(u_Material.texture_diffuse, TexCoords);
}