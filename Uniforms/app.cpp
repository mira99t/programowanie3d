//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Application/utils.h"

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

    float strength = 1.0;
    std::vector<GLfloat> color = {0.2, 0.2, 0.3};

    //Uniforms | Moving house - Zadanie 3.4

    float theta = 1.0*glm::pi<float>()/6.0f;
    auto cs = std::cos(theta);
    auto ss = std::sin(theta);
    glm::mat2 rot{cs,ss,-ss,cs};
    glm::vec2 trans{0.0,  -0.25};
    glm::vec2 scale{0.5, 0.5};

    // Generating the buffer and loading the vertex data into it.
    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //Zadanie Indices - 3.2
    //Generating the buffer and loading the Indices data into it.
    GLuint i_buffer_handle;
    glGenBuffers(1, &i_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Uniforms | Modifying pixel color - Zadanie 2
    GLuint uniform_buffer;
    glGenBuffers(1, &uniform_buffer);
    OGL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0,  uniform_buffer));
    glBufferData(GL_UNIFORM_BUFFER, 8* sizeof(float), nullptr, GL_STATIC_DRAW);
    //Unifroms | Modifying pixel color - Zadanie 3
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), 3 * sizeof(float), color.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    //Uniforms | Moving houses - Zadanie 1.1
    GLuint transformation_buffer;
    glGenBuffers(1, &transformation_buffer);
//    OGL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, transformation_buffer));

    OGL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, 1,  transformation_buffer));
    glBufferData(GL_UNIFORM_BUFFER, 12*sizeof(float), nullptr, GL_STATIC_DRAW);

    //GLintptr index = 0;
    //glBufferSubData(GL_UNIFORM_BUFFER, index, 2 * sizeof(float), &scale);
    //index += 2 * sizeof(float);
    //glBufferSubData(GL_UNIFORM_BUFFER, index, 2 * sizeof(float), &translation);
    //index += 2 * sizeof(float);
    //glBufferSubData(GL_UNIFORM_BUFFER, index, 4 * sizeof(float), &rotation[0]);
    //index += 4 * sizeof(float);
    //glBufferSubData(GL_UNIFORM_BUFFER, index, 4 * sizeof(float), &rotation[1]);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);



    // This setups a Vertex Array Object (VAO) that  encapsulates
    // the state of all vertex buffers needed for rendering
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    //Zadanie 3
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);

    //Zadanie Uniforms - 4.3
//    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniform_buffer);

    //Uniforms | Moving houses - Zadanie 1.2
//    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformation_buffer);


    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(0);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //end of vao "recording"

    //Clear window
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Setup Viewport size
    auto[w, h] = frame_buffer_size();
    glViewport(0, 0, w, h);

    glUseProgram(program);
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
