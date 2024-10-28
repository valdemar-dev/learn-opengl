#version 330 core 

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colourInput;
layout (location = 2) in vec2 textureCoordsInput;

out vec3 colourValue;
out vec2 textureCoords;

void main() {
    gl_Position = vec4(position, 1.0);
    colourValue = colourInput;
    textureCoords = textureCoordsInput;
}
