#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec2 position;

void main() {
    color = vec4(1.0);
}
