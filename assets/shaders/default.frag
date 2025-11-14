#version 330 core
out vec4 FragColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec3 uColorTint;

void main() {
    vec4 texColor = texture(uTexture, vTexCoord);
    FragColor = texColor * vec4(uColorTint, 1.0);
}
