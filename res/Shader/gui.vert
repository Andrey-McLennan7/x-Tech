#ifdef GL_ES
	attribute vec3 a_Vertex;
#else
	layout (location = 0) in vec4 a_Vertex;
#endif

out vec2 TexCoords;

uniform mat4 u_Projection;

void main()
{
	TexCoords = a_Vertex.zw;
	gl_Position = u_Projection * vec4(a_Vertex.xy, 0.0, 1.0);
}