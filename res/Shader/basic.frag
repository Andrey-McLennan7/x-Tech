#ifdef GL_ES
	precision highp float;
#endif

uniform vec3 u_Colour;

void main()
{
	gl_FragColor = vec4(u_Colour, 1.0);
}