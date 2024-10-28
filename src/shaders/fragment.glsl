#version 330 core

out vec4 FragColor;

in vec3 colourValue;
in vec2 textureCoords;

uniform sampler2D wallTexture;
uniform sampler2D smileyTexture;

void main() {
    FragColor = mix(
        texture(wallTexture, textureCoords),
        texture(smileyTexture, textureCoords),
        .2f
    );
}
