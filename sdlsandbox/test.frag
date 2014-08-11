#version 330 core
in vec2 UV;
out vec4 color;

uniform sampler2D texSampler;
 
void main(){
    //color = vec3(1, 0, 0);
	color = texture(texSampler, UV).rgba;
}