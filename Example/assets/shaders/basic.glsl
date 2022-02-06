#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_UV;

out vec2 UV;

void main()
{
	UV = a_UV;
	gl_Position = vec4(a_Position, 1.0);
}

#shader-type fragment
#version 450 core

layout(location = 0) out vec4 FragColour;

in vec2 UV;

void main()
{
	FragColour = vec4(UV, 1.0, 1.0);
}
