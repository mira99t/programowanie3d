#version 410

layout(location=0) out vec4 vFragColor;
layout(location=1) in  vec4 vertex_color;

layout(std140, binding = 0) uniform Modifier {
    float strength;
    vec3 color;
};

void main() {
    vFragColor.a = vertex_color.a;
    vFragColor.rgb = strength*color*vertex_color.rgb;
}
//#version 480
//
//layout(location=0) out vec4 vFragColor;
//layout(location=1) in vec4 b_vertex_color;
////in vec4 b_vertex_color;
//
////Uniforms - Zadanie 1.1
////Interface block
//layout(std140, binding=0) uniform Modifier{
//    float strength;
//    vec3  color;
//    //float color[3];
//};
//
//void main() {
//    //vFragColor = vec4(1.0, 0.0, 0.0, 1.0);
//    vFragColor.a = b_vertex_color.a;
//    vFragColor.rgb = strength*color*b_vertex_color.rgb;
//}
