#version 330 core

layout (location = 0) in vec4 vertex; // vec2 position, vec2 texCoords
layout (location = 1) in mat4 instanceMatrix;

uniform mat4 projection;

void main()
{
	gl_Position = projection * instanceMatrix * vec4(vertex.xy, 0.0, 1.0f);
}