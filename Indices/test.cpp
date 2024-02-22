//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>

#include "Application/utils.h"

GLuint vao, uniformXMove;

void SimpleShapeApplication::init() {
    // A utility function that reads the shader sources, compiles them and creates the program object
    // As everything in OpenGL we reference program by an integer "handle".
    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    // A vector containing the x,y,z vertex coordinates for the triangle.
    std::vector<GLfloat> vertices = {
            -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            //-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            //0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    std::vector<GLushort> indices ={0, 1, 2, 3, 4, 5, 4, 6, 5};

    GLuint verticesBuffer = generate_v_buffer_handle(vertices);
    GLuint i_buffer_handle = generate_i_buffer_handle(indices);

    // Setup Vertex Array Object (VAO) - calling function to graphics card to create a vertex array
    // defining a space in memory for one vertex array
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

        /*
        glGenBuffers(1, &vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vao_);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
        */




    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //end of vao "recording"

    // Clear window
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Setup Viewport size
    auto[w, h] = frame_buffer_size();
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

void SimpleShapeApplication::setVerticesData(){
    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(0);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
}

void SimpleShapeApplication::setColorToVertices() {
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
}

        unsigned int SimpleShapeApplication::generate_v_buffer_handle(
                std::vector<GLfloat> vertices){
            // Generating the buffer and loading the vertex data into it.
            GLuint v_buffer_handle;
            glGenBuffers(1, &v_buffer_handle);
            OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            return v_buffer_handle;
        }

        unsigned int SimpleShapeApplication::generate_i_buffer_handle(
                std::vector<GLushort> indices){

            //Zadanie 2
            //Generating the buffer and loading the Indices data into it.
            GLuint i_buffer_handle;
            glGenBuffers(1, &i_buffer_handle);
            OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle));
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            return i_buffer_handle;
        }

void SimpleShapeApplication::setDataToVertexBuffer(GLuint verticesBuffer){
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
}

void SimpleShapeApplication::setDataToIndicesBuffer(GLuint i_buffer_handle) {
    //Zadanie 3
                 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle););
}


//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {
    // Binding the VAO will setup all the required vertex buffers.
    glBindVertexArray(vao_);
    //glDrawArrays(GL_TRIANGLES, 0, 9);

    //4. Teraz w funkcji frame podmieniamy funkcję rysującą na
    // glDrawElements oczywiście zmieniając odpowiednio argumenty.

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT,
                   reinterpret_cast<GLvoid *>(0));
    glBindVertexArray(0);
}
