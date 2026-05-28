#type vertex
#version 450

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_LocalSpaceCoord;

layout(std140, binding = 0) uniform Camera {
	mat4 ProjView;
} u_Camera;

uniform mat4 u_Model;

out vec2 v_LocalSpaceCoord;

void main()
{
    v_LocalSpaceCoord = a_LocalSpaceCoord;
    gl_Position = u_Camera.ProjView * u_Model * vec4(a_Pos, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;
layout(location = 1) out int entityId;

in vec2 v_LocalSpaceCoord;

uniform vec4 u_Color;
uniform float u_Thickness;
uniform float u_Fade;

uniform int u_EntityID;

void main()
{
    float distance = 1.0 - length(v_LocalSpaceCoord);

    float circle = smoothstep(0.0, u_Fade, distance);
    circle *= smoothstep(u_Thickness + u_Fade, u_Thickness, distance);

    if(circle == 0.0)
        discard;

    color = u_Color * circle;
    entityId = u_EntityID;
}