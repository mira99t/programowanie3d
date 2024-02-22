#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec4 vertex_color;
layout(location=1) out  vec4 color;

layout(std140, binding=1) uniform Transformations {
    vec2 scale;
    vec2 translation;
    mat2 rotation;
};

void main() {
    gl_Position.xy = rotation*(scale*a_vertex_position.xy)+translation;
    gl_Position.zw = a_vertex_position.zw;
    color = vertex_color;
}
//#version 480
//
//layout(location=0) in  vec4 a_vertex_position;
//layout(location=1) in  vec4 b_vertex_color;
//layout(location=1) out vec4 color;
////out vec4 color;
//
////Uniforms | Moving houses - Zadanie 1
////Interface block
//layout(std140, binding=1) uniform Transformations {
//    vec2 scale;
//    vec2 translation;
//    mat2 rotation;
//};
//
//void main() {
//    //gl_Position = a_vertex_position;
//
//    //Uniforms | Moving houses - Zadanie 6
//    gl_Position.xy = rotation*(scale*a_vertex_position.xy)+translation;
//    gl_Position.zw = a_vertex_position.zw;
//    color = b_vertex_color;
//}