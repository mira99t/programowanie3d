#version 460

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec4 VectorColor;
out vec4 Color;

void main() {
    gl_Position = a_vertex_position; // gl_Position requires a vector that consist of 4 values - vec4
    Color = VectorColor;
}
