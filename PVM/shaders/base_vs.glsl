#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec4 VectorColor;
out vec4 Color;

uniform mat4 PVM;

void main() {
    gl_Position = PVM * a_vertex_position;
    Color = VectorColor;
}
