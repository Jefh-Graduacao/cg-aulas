#version 330 core
layout (location = 0) in vec3 trianglePosition;
layout (location = 1) in vec3 color;

uniform mat4 model;

out vec3 ourColor;

void main()
{
    gl_Position = model * vec4(trianglePosition.x, trianglePosition.y, trianglePosition.z, 1.0f);    
    ourColor = color;
}