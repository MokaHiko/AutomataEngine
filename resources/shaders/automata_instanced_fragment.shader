#version 330 core

out vec4 FragColor;

in vec3 cellColor;

void main()
{
	FragColor = vec4(cellColor, 1.0);
}