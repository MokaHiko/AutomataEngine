#version 330 core

layout (location = 0) in vec4 vertex; // vec2 position, vec2 texCoords
layout (location = 1) in vec2 coordinates; // instanced per pixel
layout (location = 2) in vec3 colors; // instanced per pixel

uniform mat4 projection;

out vec3 cellColor;
void main()
{
	cellColor = colors;
	gl_Position = projection * vec4(vertex.x + coordinates.x, vertex.y + coordinates.y, 0.0, 1.0f);
}