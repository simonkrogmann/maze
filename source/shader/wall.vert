#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0)in vec3 vertex;

out vec3 position;

void main() {
    gl_Position = vec4(vertex, 1.0);
    position = vertex;
}
