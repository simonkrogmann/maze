#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 normal;
out vec3 worldPosition;
uniform mat4 viewProjection;

void main()
{
    vec3 triangleNormal = cross(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz,
                                gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz);
    for (int i = 0; i < 3; ++i)
    {
        gl_Position = viewProjection * gl_in[i].gl_Position;
        worldPosition = gl_in[i].gl_Position.xyz;
        normal = normalize(triangleNormal);
        EmitVertex();
    }
    EndPrimitive();
}
