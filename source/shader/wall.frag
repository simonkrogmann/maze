#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec3 position;
in vec3 normal;

void main() {
    vec3 light =  normalize(vec3(-20.0, 2.0, 20.0));
    float ambient = 1.0;
    float diffuse = dot(normal, light);
    color = vec4(vec3(0.5 * ambient + 0.6 * diffuse), 1.0);
}
