#ifdef GL_ES
	precision highp float;
#endif

in vec2 TexCoords;

uniform sampler2D u_Text;
uniform vec3 u_TextColour;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Text, TexCoords).r);
	gl_FragColor = vec4(u_TextColour, 1.0) * sampled;
}