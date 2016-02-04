#version 330
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec3 position;
in vec3 normal;

void main() {
    vec3 light =  vec3(-2.0, 2.0, 3.0) - position;
    float ambient = 1.0;
    float diffuse = dot(normal, normalize(light));
    color = vec4(vec3(0.5 * ambient + 0.6 * diffuse) * 10 / pow(length(light), 2.0), 1.0);
}
