#version 330
#extension GL_ARB_shading_language_include : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec2 position;
uniform sampler2D shadowmap;
uniform mat4 lightViewProjection;

#include "/shader/shadowmap_lookup.frag"

void main() {
    vec3 normal = vec3(0.0, 0.0, 1.0);
    vec3 worldPosition = vec3(position, 0.0);
    vec3 light =  vec3(-2.0, 2.0, 3.0) - worldPosition;

    float shadowed = shadowmapLookup(
        shadowmap, lightViewProjection, worldPosition, normal);
    shadowed = shadowed * 0.5 + 0.5;

    float ambient = 1.0;
    float diffuse = dot(normal, normalize(light));
    float attenuation = 10 / pow(length(light), 2.0);
    color = vec4(shadowed * vec3(0.5 * ambient + 0.6 * diffuse) * attenuation, 1.0);
}
