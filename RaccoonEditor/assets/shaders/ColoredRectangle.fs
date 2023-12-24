#version 450 core
out vec4 Color;

in vec4 v_Color;

void main()
{
    Color = v_Color;
}