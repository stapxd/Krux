#type vertex
#version 450

layout(location = 0) in vec3  a_Pos;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_LocalSpaceCoord;
layout(location = 3) in float a_Thickness;
layout(location = 4) in float a_Fade;

layout(std140, binding = 0) uniform Camera {
	mat4 ProjView;
} u_Camera;

out vec4  v_Color;
out vec2  v_LocalSpaceCoord;
out float v_Thickness;
out float v_Fade;

void main()
{
    v_Color = a_Color;
    v_LocalSpaceCoord = a_LocalSpaceCoord;
    v_Thickness = a_Thickness;
    v_Fade = a_Fade;

    gl_Position = u_Camera.ProjView * vec4(a_Pos, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

in vec4  v_Color;
in vec2  v_LocalSpaceCoord;
in float v_Thickness;
in float v_Fade;

void main()
{
    float distance = 1.0 - length(v_LocalSpaceCoord);

    float circle = smoothstep(0.0, v_Fade, distance);
    circle *= smoothstep(v_Thickness + v_Fade, v_Thickness, distance);

    if(circle == 0.0)
        discard;

    color = v_Color * circle;
}