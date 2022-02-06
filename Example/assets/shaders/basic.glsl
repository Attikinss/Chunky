#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_UV;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

out vec2 UV;

void main()
{
	UV = a_UV;
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}

#shader-type fragment
#version 450 core

layout(location = 0) out vec4 FragColour;

in vec2 UV;

void main()
{
	FragColour = vec4(UV, 1.0, 1.0);
}
