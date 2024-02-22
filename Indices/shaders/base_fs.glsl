#version 460
//vec4 - vector consisting of four values.
layout(location=0) out vec4 vFragColor;
in vec4 Color;

void main() {
    //vFragColor = vec4(1.0, 0.0, 0.0, 1.0);
    vFragColor = Color;
}
