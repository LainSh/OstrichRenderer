#version 450

in vec3 WorldPosV;
in vec3 NormalV;
in vec2 TexCoordV;

layout (location = 0) out vec3 PositionOut;
layout (location = 1) out vec3 NormalOut;

void main()
{
	PositionOut = WorldPosV;
	NormalOut = normalize(NormalV);
}
