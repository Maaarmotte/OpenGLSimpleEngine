#version 330 core
layout(location = 0) in vec3 position;
uniform mat4 MVP;

void main() {
	gl_Position.xyz = position;
    gl_Position.w = 1.0;

    vec4 pos = vec4(position, 1.0f);
    gl_Position = MVP * pos;
 }
