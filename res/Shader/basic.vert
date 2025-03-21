#ifdef GL_ES
	attribute vec3 a_Positions;
#else
	layout (location = 0) in vec3 a_Positions;
#endif

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Positions, 1.0);
}