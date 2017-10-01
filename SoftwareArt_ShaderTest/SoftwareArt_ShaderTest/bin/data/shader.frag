#version 150

out vec4 color;


void main() {
	float width = 1024.0;
	float height = 768.0;

	color = vec4(gl_FragCoord.x/width, gl_FragCoord.y/height, 1, 1);

}