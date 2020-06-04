
#version 330 core
out vec4 FragColor;
uniform float r;
uniform float g;
uniform float b;

void main()
{
    FragColor = vec4(r, g, b, 1.0f);
}