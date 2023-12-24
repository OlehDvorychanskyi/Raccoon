#version 450 core
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoords;
layout(location = 3) in float a_TextureIndex;

uniform mat3 u_ViewProjection;

out vec2 v_TextureCoords;
out float v_TextureIndex;
out vec4 v_Color;

void main()
{
    v_TextureCoords = a_TextureCoords;
    v_TextureIndex = a_TextureIndex;
    v_Color = a_Color;

    gl_Position = vec4(u_ViewProjection * vec3(a_Position, 1.f), 1.f);
}