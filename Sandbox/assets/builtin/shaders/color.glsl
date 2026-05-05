#type vertex
#version 450

layout(location = 0) in vec3 aPos;

uniform mat4 u_Model;

void main()
{
    gl_Position = u_Model * vec4(aPos, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
}