#version 450 core
out vec4 Color;

in vec2 v_TextureCoords;
in float v_TextureIndex;
in vec4 v_Color;

layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    Color = texture(u_Textures[int(v_TextureIndex)], v_TextureCoords) * v_Color;
}