#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Application/utils.h"

void SimpleShapeApplication::init() {

    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    std::vector<GLfloat> vertices = {
            -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.f, 1.f, 0.f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.f, -0.5f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.f, -0.5f, 0.0f, 0.0f, 1.0f,
            0.f, 1.f, 0.f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.f, 0.5f, 1.0f, 1.0f, 0.0f,
            0.f, 1.f, 0.f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.f, 0.5f, 1.0f, 1.0f, 0.0f,

            -0.5f, 0.f, 0.5f, 1.0f, 0.0f, 1.0f,
            0.f, 1.f, 0.f, 1.0f, 0.0f, 1.0f,
            -0.5f, 0.f, -0.5f, 1.0f, 0.0f, 1.0f,
    };

    indices = {
            0, 2, 1,
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
            11, 10, 12,
            13, 14, 15,
    };

    float strength = 1.0;
    std::vector<GLfloat> color = {0.9, 0.8, 0.7};

    auto[w, h] = frame_buffer_size();
    aspect = (float) w / h;
    fov = glm::pi<float>() / 4.0;
    near = 0.1f;
    far = 100.0f;

    viewMat = glm::lookAt(
            glm::vec3(-2.0f, -1.f, -5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );
    perMat = glm::perspective(fov, aspect, near, far);
    modelMat = glm::mat4(1.0f);
    modelMat = glm::rotate(modelMat, glm::radians(115.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    GLuint indicesBuffer = generateIndicesBuffer(indices);
    GLuint verticesBuffer = generateVertexBuffer(vertices);
    GLuint uniformBuffer = generateUniformBuffer(strength, color);
    transformationBuffer = generateTransformationBuffer();

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    bindDataToUniformBuffer(uniformBuffer, transformationBuffer);
    setDataToVertexBuffer(verticesBuffer);
    setDataToIndicesBuffer(indicesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    glViewport(0, 0, w, h);

    glUseProgram(program);
}

unsigned int SimpleShapeApplication::generateVertexBuffer(std::vector<GLfloat> vertices) {
    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return v_buffer_handle;
}

unsigned int SimpleShapeApplication::generateIndicesBuffer(std::vector<GLushort> indices) {
    GLuint indicesBuffer;
    glGenBuffers(1, &indicesBuffer);
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return indicesBuffer;
}

unsigned int SimpleShapeApplication::generateUniformBuffer(float strength, std::vector<GLfloat> color) {
    GLuint uniformBuffer;
    glGenBuffers(1, &uniformBuffer);
    OGL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer));
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), 3 * sizeof(float), color.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    return uniformBuffer;
}


unsigned int SimpleShapeApplication::generateTransformationBuffer() {
    GLuint transformationBuffer;
    glGenBuffers(1, &transformationBuffer);
    OGL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer));
    glBufferData(GL_UNIFORM_BUFFER, 16 * sizeof(float), nullptr, GL_STATIC_DRAW);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    return transformationBuffer;
}

void SimpleShapeApplication::setDataToVertexBuffer(GLuint verticesBuffer) {
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    setVerticesData();
    setColorToVertices();
}

void SimpleShapeApplication::setVerticesData() {
    int arrayId = 0;
    int dataInArrayOffset = 0;
    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(arrayId);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(arrayId, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(dataInArrayOffset));
}

void SimpleShapeApplication::setColorToVertices() {
    int arrayId = 1;
    int dataInArrayOffset = 3 * sizeof(GLfloat);

    glEnableVertexAttribArray(arrayId);
    glVertexAttribPointer(arrayId, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(dataInArrayOffset));
}

void SimpleShapeApplication::setDataToIndicesBuffer(GLuint indicesBuffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
}

void SimpleShapeApplication::bindDataToUniformBuffer(GLuint uniformBuffer, GLuint transformationBuffer) {
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformationBuffer);
}

void SimpleShapeApplication::frame() {
    auto pvm = perMat * viewMat * modelMat;
    glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &pvm[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Binding the VAO will setup all the required vertex buffers.
    glBindVertexArray(vao_);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid *>(0));
    glBindVertexArray(0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0, 0, w, h);
    aspect = (float) w / h;
    perMat = glm::perspective(fov, aspect, near, far);
}