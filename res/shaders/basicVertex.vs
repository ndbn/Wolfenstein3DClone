#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 transform;

void main()
{
    texCoord0 = texCoord;
	gl_Position = transform * vec4(position, 1.0);
}
