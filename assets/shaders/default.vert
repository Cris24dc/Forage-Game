#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 uModel;
uniform mat4 uProjection;

uniform vec2 uUvOffset;
uniform vec2 uUvScale;

void main() {
    gl_Position = uProjection * uModel * vec4(aPos, 1.0);
    vTexCoord = aTexCoord * uUvScale + uUvOffset;
}
