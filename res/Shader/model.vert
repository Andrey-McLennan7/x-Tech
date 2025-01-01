#ifdef GL_ES
	attribute vec3 a_Positions;
	attribute vec3 a_Normals;
	attribute vec2 a_TexCoords;
#else
	layout (location = 0) in vec3 a_Positions;
	layout (location = 1) in vec3 a_Normals;
	layout (location = 2) in vec2 a_TexCoords;
#endif

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

void main()
{
	Normal = mat3(transpose(inverse(u_Model))) * a_Normals;
	FragPos = vec3(u_Model * vec4(a_Positions, 1.0f));
	TexCoords = a_TexCoords;

	gl_Position = u_Projection * u_View * u_Model * vec4(a_Positions, 1.0f);
}