#version 330 core
out vec4 FragColor;
in vec3 colourValue;

void main() {
    FragColor = vec4(colourValue, 1.0);
}
