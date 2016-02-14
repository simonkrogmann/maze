#version 330
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec3 worldPosition;
in vec3 normal;
uniform sampler2D shadowmap;
uniform mat4 lightViewProjection;
const float bias = 0.00001;

void main() {
    vec4 lightPos = lightViewProjection * vec4(worldPosition, 1.0);
    lightPos /= lightPos.w;
    lightPos = lightPos * 0.5 + 0.5;

    float shadowed = step(lightPos.z, texture(shadowmap, lightPos.xy).r +  bias);
    shadowed = shadowed * 0.5 + 0.5;

    vec3 light =  vec3(-2.0, 2.0, 3.0) - worldPosition;
    float ambient = 1.0;
    float diffuse = dot(normal, normalize(light));
    float attenuation = 10 / pow(length(light), 2.0);
    color = vec4(shadowed * vec3(0.5 * ambient + 0.6 * diffuse) * attenuation, 1.0);
}
