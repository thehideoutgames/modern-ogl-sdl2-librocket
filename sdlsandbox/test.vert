#version 330 core
in vec3 vertexPosition_modelspace;
in vec2 vertexUV;

uniform mat4 MVP;

out vec2 UV;

void main(){
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	UV = vertexUV;
 }