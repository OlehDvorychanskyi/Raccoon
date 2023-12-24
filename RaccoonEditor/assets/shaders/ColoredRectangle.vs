#version 450 core
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat3 u_ViewProjection;

out vec4 v_Color;

void main()
{
    gl_Position = vec4(u_ViewProjection * vec3(a_Position, 1.f), 1.f);
    v_Color = a_Color;
}