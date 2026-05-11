#type vertex
#version 450

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TextureCoord;

uniform mat4 u_ProjView;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TextureCoord;
    gl_Position = u_ProjView * u_Model * vec4(a_Pos, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_TintColor;
uniform int u_TilingFactor;
uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_TintColor;
}