#version 420

layout(location=0) out vec4 vFragColor;
in vec4 Color;

void main() {
    //vFragColor = vec4(1.0, 0.0, 0.0, 1.0);
    vFragColor = Color;
}
